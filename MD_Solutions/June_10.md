#  Intuition

The value of a subarray is defined as:

\[
\text{value} = \max(subarray) - \min(subarray)
\]

A straightforward brute-force approach would generate all possible subarrays and compute their minimum and maximum values individually. However, with \(O(n^2)\) subarrays, such a solution quickly becomes infeasible.

The crucial observation is that for every interval we only care about two numbers:

- The minimum element.
- The maximum element.

If we can answer range minimum and maximum queries efficiently, then computing the value of any interval becomes trivial.

This naturally leads us to a **Sparse Table**, which allows:

- Range Minimum Query in \(O(1)\)
- Range Maximum Query in \(O(1)\)

after an \(O(n\log n)\) preprocessing phase.

Once interval values can be obtained instantly, we use a **Max Heap** to greedily extract the best available interval at every operation.

---

# Key Observation

For a fixed starting position `i`, all possible intervals are:

```text
[i, n)
[i, n-1)
[i, n-2)
...
[i, i+1)
```

Instead of generating all of them upfront, we generate them lazily.

Initially, only the largest interval `[i, n)` is inserted into the heap.

Whenever an interval is selected:

```text
[l, r)
```

the next candidate from the same chain becomes:

```text
[l, r-1)
```

This avoids constructing all \(O(n^2)\) intervals while still ensuring every useful candidate is eventually considered.

---

#  Greedy Insight

At any moment, the heap contains the best currently available interval from each starting position.

The interval on top of the heap is globally the maximum-valued interval available.

Therefore:

1. Select the interval with the largest value.
2. Add its contribution to the answer.
3. Generate the next interval from the same starting position.

Since every chain is explored in descending order of interval length and the heap always keeps the global maximum at the top, we never miss a better choice.

---

# 🏗️ Data Structures Used

## Sparse Table

Two tables are maintained:

### Minimum Table

```text
minTable[k][i]
```

stores the minimum value in a segment of length \(2^k\).

### Maximum Table

```text
maxTable[k][i]
```

stores the maximum value in a segment of length \(2^k\).

Using overlapping blocks, any interval can be queried in constant time.

---

## Max Heap

Each heap node contains:

```text
(value, left, right)
```

where:

- value = max - min of interval
- left = starting index
- right = ending index

The heap always returns the interval with the largest value.

---

#  Approach

### Step 1: Build Sparse Tables

Precompute:

```text
Range Minimum Queries
Range Maximum Queries
```

for every power-of-two segment.

---

### Step 2: Initialize Heap

For every index:

```cpp
i = 0 ... n-1
```

insert:

```text
[i, n)
```

along with its value.

---

### Step 3: Perform Greedy Selection

Repeat while:

```text
heap not empty
k > 0
top value > 0
```

1. Extract maximum interval.
2. Add its value to answer.
3. Decrease `k`.
4. Shrink interval:

```text
[l, r)
→
[l, r-1)
```

5. Push the shortened interval back if it remains valid.

---

### Step 4: Return Answer

The accumulated sum represents the maximum total value obtainable after at most `k` operations.

---

# Sparse Table Query Explanation

Suppose we want the value of:

```text
[l, r)
```

Let:

```text
len = r - l
k = floor(log2(len))
```

The interval can be covered by two overlapping segments:

```text
[l, l + 2^k)

[r - 2^k, r)
```

Maximum:

```cpp
max(
    maxTable[k][l],
    maxTable[k][r - (1 << k)]
)
```

Minimum:

```cpp
min(
    minTable[k][l],
    minTable[k][r - (1 << k)]
)
```

Therefore:

```cpp
value = maximum - minimum
```

is obtained in \(O(1)\).

---

#  Dry Run

### Example

```text
nums = [4, 1, 7]
k = 2
```

Initial intervals:

```text
[0,3] -> 6
[1,3] -> 6
[2,3] -> 0
```

Heap:

```text
6, 6, 0
```

### Operation 1

Take:

```text
[0,3]
```

Contribution:

```text
6
```

Answer:

```text
6
```

Push:

```text
[0,2] -> 3
```

Heap:

```text
6, 3, 0
```

---

### Operation 2

Take:

```text
[1,3]
```

Contribution:

```text
6
```

Answer:

```text
12
```

Stop because `k = 0`.

Final Answer:

```text
12
```

---

#  Correctness Proof

We prove that the algorithm always produces the maximum possible total value.

### Lemma 1

For every starting position `i`, the algorithm eventually generates every valid interval beginning at `i`.

**Proof.**

The algorithm starts with the largest interval:

```text
[i, n)
```

Whenever an interval:

```text
[i, r)
```

is removed from the heap, the interval:

```text
[i, r-1)
```

is inserted.

Repeating this process eventually generates all intervals beginning at `i`.

∎

---

### Lemma 2

The heap always contains the highest-priority unexplored interval from every starting position.

**Proof.**

Initially the largest interval from each starting index is inserted.

Whenever an interval is processed, only its immediate successor is inserted.

Thus the heap continuously stores the next unexplored interval for each chain.

∎

---

### Lemma 3

The interval extracted from the heap always has the maximum value among all currently available intervals.

**Proof.**

The heap is a max heap ordered by interval value.

Therefore its top element is always the interval with greatest value among all candidates currently stored.

∎

---

### Theorem

The algorithm returns the maximum possible total value after at most `k` operations.

**Proof.**

By Lemma 1, every valid interval eventually becomes available.

By Lemma 2, no chain loses any candidate.

By Lemma 3, each operation selects the globally largest available value.

Therefore every step is optimally greedy, producing the maximum possible total contribution after `k` selections.

∎

---

#  Complexity Analysis

### Sparse Table Construction

There are:

```text
log n
```

levels.

Each level processes:

```text
n
```

elements.

Time:

\[
O(n\log n)
\]

Space:

\[
O(n\log n)
\]

---

### Heap Operations

Initial insertions:

\[
O(n)
\]

For every operation:

- One pop
- One push

Both cost:

\[
O(\log n)
\]

Repeated at most `k` times.

Time:

\[
O(k\log n)
\]

---

# Complexity

### Time Complexity

\[
O(n\log n + k\log n)
\]

### Space Complexity

\[
O(n\log n)
\]

---

# Code

```c []
#include <stdlib.h>

typedef struct {
    int **mn;
    int **mx;
    int levels;
    int n;
} SparseTable;

static int minInt(int a, int b) {
    return a < b ? a : b;
}

static int maxInt(int a, int b) {
    return a > b ? a : b;
}

static int log2Floor(int x) {
    int res = 0;
    while ((1 << (res + 1)) <= x) res++;
    return res;
}

SparseTable* createSparseTable(int* nums, int n) {
    SparseTable* st = (SparseTable*)malloc(sizeof(SparseTable));

    st->n = n;
    st->levels = 0;
    while ((1 << st->levels) <= n) st->levels++;

    st->mn = (int**)malloc(st->levels * sizeof(int*));
    st->mx = (int**)malloc(st->levels * sizeof(int*));

    for (int i = 0; i < st->levels; i++) {
        st->mn[i] = (int*)calloc(n, sizeof(int));
        st->mx[i] = (int*)calloc(n, sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        st->mn[0][i] = nums[i];
        st->mx[0][i] = nums[i];
    }

    for (int k = 1; k < st->levels; k++) {
        int half = 1 << (k - 1);
        int len = 1 << k;

        for (int j = 0; j + len <= n; j++) {
            st->mn[k][j] = minInt(
                st->mn[k - 1][j],
                st->mn[k - 1][j + half]
            );

            st->mx[k][j] = maxInt(
                st->mx[k - 1][j],
                st->mx[k - 1][j + half]
            );
        }
    }

    return st;
}

int query(SparseTable* st, int left, int right) {
    int len = right - left;
    if (len <= 0) return 0;

    int k = log2Floor(len);

    int mx = maxInt(
        st->mx[k][left],
        st->mx[k][right - (1 << k)]
    );

    int mn = minInt(
        st->mn[k][left],
        st->mn[k][right - (1 << k)]
    );

    return mx - mn;
}

void freeSparseTable(SparseTable* st) {
    for (int i = 0; i < st->levels; i++) {
        free(st->mn[i]);
        free(st->mx[i]);
    }
    free(st->mn);
    free(st->mx);
    free(st);
}

typedef struct {
    int val;
    int l;
    int r;
} Node;

typedef struct {
    Node* heap;
    int size;
    int cap;
} MaxHeap;

void heapInit(MaxHeap* h, int cap) {
    h->heap = (Node*)malloc(cap * sizeof(Node));
    h->size = 0;
    h->cap = cap;
}

void heapPush(MaxHeap* h, Node x) {
    if (h->size == h->cap) {
        h->cap *= 2;
        h->heap = (Node*)realloc(h->heap, h->cap * sizeof(Node));
    }

    int i = h->size++;
    h->heap[i] = x;

    while (i > 0) {
        int p = (i - 1) / 2;

        if (h->heap[p].val >= h->heap[i].val)
            break;

        Node tmp = h->heap[p];
        h->heap[p] = h->heap[i];
        h->heap[i] = tmp;

        i = p;
    }
}

Node heapPop(MaxHeap* h) {
    Node top = h->heap[0];

    h->heap[0] = h->heap[--h->size];

    int i = 0;

    while (1) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < h->size &&
            h->heap[left].val > h->heap[largest].val)
            largest = left;

        if (right < h->size &&
            h->heap[right].val > h->heap[largest].val)
            largest = right;

        if (largest == i)
            break;

        Node tmp = h->heap[i];
        h->heap[i] = h->heap[largest];
        h->heap[largest] = tmp;

        i = largest;
    }

    return top;
}

Node heapTop(MaxHeap* h) {
    return h->heap[0];
}

long long maxTotalValue(int* nums, int numsSize, int k) {
    int n = numsSize;
    long long res = 0;

    SparseTable* st = createSparseTable(nums, n);

    MaxHeap pq;
    heapInit(&pq, n + k + 5);

    for (int i = 0; i < n; i++) {
        Node cur = {query(st, i, n), i, n};
        heapPush(&pq, cur);
    }

    while (pq.size > 0 && heapTop(&pq).val > 0 && k > 0) {
        Node cur = heapPop(&pq);

        res += cur.val;
        k--;

        if (cur.r - cur.l > 1) {
            Node nxt = {
                query(st, cur.l, cur.r - 1),
                cur.l,
                cur.r - 1
            };
            heapPush(&pq, nxt);
        }
    }

    freeSparseTable(st);
    free(pq.heap);

    return res;
}
```

```java []
class SparseTable {
    private int[][] minTable;
    private int[][] maxTable;

    public SparseTable(int[] nums) {
        int n = nums.length;
        int w = 32 - Integer.numberOfLeadingZeros(n);

        minTable = new int[w][n];
        maxTable = new int[w][n];

        for (int i = 0; i < n; i++) {
            minTable[0][i] = nums[i];
            maxTable[0][i] = nums[i];
        }

        for (int i = 1; i < w; i++) {
            int len = 1 << i;
            int half = 1 << (i - 1);

            for (int j = 0; j + len <= n; j++) {
                minTable[i][j] = Math.min(
                    minTable[i - 1][j],
                    minTable[i - 1][j + half]
                );

                maxTable[i][j] = Math.max(
                    maxTable[i - 1][j],
                    maxTable[i - 1][j + half]
                );
            }
        }
    }

    public int query(int left, int right) {
        // range is [left, right)
        int len = right - left;
        int k = 31 - Integer.numberOfLeadingZeros(len);

        int mx = Math.max(
            maxTable[k][left],
            maxTable[k][right - (1 << k)]
        );

        int mn = Math.min(
            minTable[k][left],
            minTable[k][right - (1 << k)]
        );

        return mx - mn;
    }
}

class Solution {
    static class Node {
        int value;
        int left;
        int right;

        Node(int value, int left, int right) {
            this.value = value;
            this.left = left;
            this.right = right;
        }
    }

    public long maxTotalValue(int[] nums, int k) {
        int n = nums.length;
        long res = 0;

        SparseTable lut = new SparseTable(nums);

        PriorityQueue<Node> pq = new PriorityQueue<>(
            (a, b) -> Integer.compare(b.value, a.value)
        );

        for (int i = 0; i < n; i++) {
            pq.offer(new Node(lut.query(i, n), i, n));
        }

        while (!pq.isEmpty() && pq.peek().value > 0 && k-- > 0) {
            Node cur = pq.poll();

            res += cur.value;

            pq.offer(
                new Node(
                    lut.query(cur.left, cur.right - 1),
                    cur.left,
                    cur.right - 1
                )
            );
        }

        return res;
    }
}
```

```python []
from heapq import heappush, heappop

class SparseTable:
    def __init__(self, nums):
        n = len(nums)
        w = n.bit_length()

        self.min_table = [[0] * n for _ in range(w)]
        self.max_table = [[0] * n for _ in range(w)]

        for i in range(n):
            self.min_table[0][i] = nums[i]
            self.max_table[0][i] = nums[i]

        for k in range(1, w):
            half = 1 << (k - 1)
            length = 1 << k

            for j in range(n - length + 1):
                self.min_table[k][j] = min(
                    self.min_table[k - 1][j],
                    self.min_table[k - 1][j + half]
                )

                self.max_table[k][j] = max(
                    self.max_table[k - 1][j],
                    self.max_table[k - 1][j + half]
                )

    def query(self, left, right):
        # range [left, right)
        length = right - left
        if length <= 0:
            return 0

        k = length.bit_length() - 1

        mx = max(
            self.max_table[k][left],
            self.max_table[k][right - (1 << k)]
        )

        mn = min(
            self.min_table[k][left],
            self.min_table[k][right - (1 << k)]
        )

        return mx - mn


class Solution:
    def maxTotalValue(self, nums, k):
        n = len(nums)
        res = 0

        lut = SparseTable(nums)

        # max heap using negative values
        pq = []

        for i in range(n):
            heappush(pq, (-lut.query(i, n), i, n))

        while pq and k > 0:
            neg_val, l, r = heappop(pq)
            val = -neg_val

            if val == 0:
                break

            res += val
            k -= 1

            if r - l > 1:
                heappush(
                    pq,
                    (-lut.query(l, r - 1), l, r - 1)
                )

        return res

```

```javascript []
/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */

class SparseTable {
  constructor(nums) {
    const n = nums.length;
    const w = Math.floor(Math.log2(n)) + 1;

    this.minTable = Array.from({ length: w }, () => Array(n).fill(0));
    this.maxTable = Array.from({ length: w }, () => Array(n).fill(0));

    for (let i = 0; i < n; i++) {
      this.minTable[0][i] = nums[i];
      this.maxTable[0][i] = nums[i];
    }

    for (let k = 1; k < w; k++) {
      const half = 1 << (k - 1);
      const len = 1 << k;

      for (let j = 0; j + len <= n; j++) {
        this.minTable[k][j] = Math.min(
          this.minTable[k - 1][j],
          this.minTable[k - 1][j + half],
        );

        this.maxTable[k][j] = Math.max(
          this.maxTable[k - 1][j],
          this.maxTable[k - 1][j + half],
        );
      }
    }
  }

  query(left, right) {
    const len = right - left;
    if (len <= 0) return 0;

    const k = Math.floor(Math.log2(len));

    const mx = Math.max(
      this.maxTable[k][left],
      this.maxTable[k][right - (1 << k)],
    );

    const mn = Math.min(
      this.minTable[k][left],
      this.minTable[k][right - (1 << k)],
    );

    return mx - mn;
  }
}

class MyMaxHeap {
  constructor() {
    this.heap = [];
  }

  push(item) {
    this.heap.push(item);
    let i = this.heap.length - 1;

    while (i > 0) {
      const p = (i - 1) >> 1;
      if (this.heap[p][0] >= this.heap[i][0]) break;

      [this.heap[p], this.heap[i]] = [this.heap[i], this.heap[p]];
      i = p;
    }
  }

  pop() {
    if (this.heap.length === 1) return this.heap.pop();

    const top = this.heap[0];
    this.heap[0] = this.heap.pop();

    let i = 0;

    while (true) {
      let largest = i;
      const l = i * 2 + 1;
      const r = i * 2 + 2;

      if (l < this.heap.length && this.heap[l][0] > this.heap[largest][0]) {
        largest = l;
      }

      if (r < this.heap.length && this.heap[r][0] > this.heap[largest][0]) {
        largest = r;
      }

      if (largest === i) break;

      [this.heap[i], this.heap[largest]] = [this.heap[largest], this.heap[i]];

      i = largest;
    }

    return top;
  }

  peek() {
    return this.heap[0];
  }

  size() {
    return this.heap.length;
  }
}

var maxTotalValue = function (nums, k) {
  const n = nums.length;
  let res = 0;

  const lut = new SparseTable(nums);
  const pq = new MyMaxHeap();

  for (let i = 0; i < n; i++) {
    pq.push([lut.query(i, n), i, n]);
  }

  while (pq.size() > 0 && pq.peek()[0] > 0 && k > 0) {
    const [val, l, r] = pq.pop();

    res += val;
    k--;

    if (r - l > 1) {
      pq.push([lut.query(l, r - 1), l, r - 1]);
    }
  }

  return res;
};
```

```c []
typedef struct {
    int **mn;
    int **mx;
    int levels;
    int n;
} SparseTable;

static int minInt(int a, int b) {
    return a < b ? a : b;
}

static int maxInt(int a, int b) {
    return a > b ? a : b;
}

static int log2Floor(int x) {
    int res = 0;
    while ((1 << (res + 1)) <= x) res++;
    return res;
}

SparseTable* createSparseTable(int* nums, int n) {
    SparseTable* st = (SparseTable*)malloc(sizeof(SparseTable));

    st->n = n;
    st->levels = 0;
    while ((1 << st->levels) <= n) st->levels++;

    st->mn = (int**)malloc(st->levels * sizeof(int*));
    st->mx = (int**)malloc(st->levels * sizeof(int*));

    for (int i = 0; i < st->levels; i++) {
        st->mn[i] = (int*)calloc(n, sizeof(int));
        st->mx[i] = (int*)calloc(n, sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        st->mn[0][i] = nums[i];
        st->mx[0][i] = nums[i];
    }

    for (int k = 1; k < st->levels; k++) {
        int half = 1 << (k - 1);
        int len = 1 << k;

        for (int j = 0; j + len <= n; j++) {
            st->mn[k][j] = minInt(
                st->mn[k - 1][j],
                st->mn[k - 1][j + half]
            );

            st->mx[k][j] = maxInt(
                st->mx[k - 1][j],
                st->mx[k - 1][j + half]
            );
        }
    }

    return st;
}

int query(SparseTable* st, int left, int right) {
    int len = right - left;
    if (len <= 0) return 0;

    int k = log2Floor(len);

    int mx = maxInt(
        st->mx[k][left],
        st->mx[k][right - (1 << k)]
    );

    int mn = minInt(
        st->mn[k][left],
        st->mn[k][right - (1 << k)]
    );

    return mx - mn;
}

void freeSparseTable(SparseTable* st) {
    for (int i = 0; i < st->levels; i++) {
        free(st->mn[i]);
        free(st->mx[i]);
    }
    free(st->mn);
    free(st->mx);
    free(st);
}

typedef struct {
    int val;
    int l;
    int r;
} Node;

typedef struct {
    Node* heap;
    int size;
    int cap;
} MaxHeap;

void heapInit(MaxHeap* h, int cap) {
    h->heap = (Node*)malloc(cap * sizeof(Node));
    h->size = 0;
    h->cap = cap;
}

void heapPush(MaxHeap* h, Node x) {
    if (h->size == h->cap) {
        h->cap *= 2;
        h->heap = (Node*)realloc(h->heap, h->cap * sizeof(Node));
    }

    int i = h->size++;
    h->heap[i] = x;

    while (i > 0) {
        int p = (i - 1) / 2;

        if (h->heap[p].val >= h->heap[i].val)
            break;

        Node tmp = h->heap[p];
        h->heap[p] = h->heap[i];
        h->heap[i] = tmp;

        i = p;
    }
}

Node heapPop(MaxHeap* h) {
    Node top = h->heap[0];

    h->heap[0] = h->heap[--h->size];

    int i = 0;

    while (1) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < h->size &&
            h->heap[left].val > h->heap[largest].val)
            largest = left;

        if (right < h->size &&
            h->heap[right].val > h->heap[largest].val)
            largest = right;

        if (largest == i)
            break;

        Node tmp = h->heap[i];
        h->heap[i] = h->heap[largest];
        h->heap[largest] = tmp;

        i = largest;
    }

    return top;
}

Node heapTop(MaxHeap* h) {
    return h->heap[0];
}

long long maxTotalValue(int* nums, int numsSize, int k) {
    int n = numsSize;
    long long res = 0;

    SparseTable* st = createSparseTable(nums, n);

    MaxHeap pq;
    heapInit(&pq, n + k + 5);

    for (int i = 0; i < n; i++) {
        Node cur = {query(st, i, n), i, n};
        heapPush(&pq, cur);
    }

    while (pq.size > 0 && heapTop(&pq).val > 0 && k > 0) {
        Node cur = heapPop(&pq);

        res += cur.val;
        k--;

        if (cur.r - cur.l > 1) {
            Node nxt = {
                query(st, cur.l, cur.r - 1),
                cur.l,
                cur.r - 1
            };
            heapPush(&pq, nxt);
        }
    }

    freeSparseTable(st);
    free(pq.heap);

    return res;
}
```
