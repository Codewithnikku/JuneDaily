# Intuition

The key observation is that the answer depends **only on the maximum depth of the tree**.

Every edge can be assigned either:

- Weight `1` (odd)
- Weight `2` (even)

Suppose the deepest node is at depth `d`. The path from the root (`1`) to that node contains exactly `d` edges.

For each edge on that path, there are two choices (`1` or `2`), so:

```text
Total assignments = 2^d
```

A path sum becomes **odd** if the number of edges assigned weight `1` is odd.

Among all possible assignments:

```text
Half produce an odd sum
Half produce an even sum
```

Therefore:

```text
Valid assignments = 2^(d-1)
```

So the problem reduces to finding the **maximum depth** of the tree rooted at node `1`.

---

# Approach

### Step 1: Build the Tree

Convert the given edge list into an adjacency list representation.

This allows efficient traversal of all connected nodes.

### Step 2: Find the Maximum Depth

Perform a BFS starting from node `1`.

For every visited node:

- Store its depth.
- Update the maximum depth encountered so far.

At the end of traversal:

```text
maxDepth = deepest node depth from root
```

### Step 3: Apply the Mathematical Observation

If:

```text
maxDepth = d
```

Then:

```text
Answer = 2^(d-1) mod (1e9 + 7)
```

Use fast binary exponentiation to compute the result efficiently.

---

# Example

### Input

```text
edges = [[1,2],[1,3],[3,4]]
```

### Tree Structure

```text
      1
     / \
    2   3
         \
          4
```

### Depth Calculation

```text
Node 1 -> Depth 0
Node 2 -> Depth 1
Node 3 -> Depth 1
Node 4 -> Depth 2
```

Therefore:

```text
maxDepth = 2
```

### Possible Assignments on the Deepest Path

Path:

```text
1 -> 3 -> 4
```

Contains:

```text
2 edges
```

Assignments:

```text
(1,1) -> Sum = 2  -> Even
(1,2) -> Sum = 3  -> Odd
(2,1) -> Sum = 3  -> Odd
(2,2) -> Sum = 4  -> Even
```

Valid assignments:

```text
2
```

Formula:

```text
2^(2-1) = 2
```

Answer:

```text
2
```

---

# Proof of Correctness

Let the maximum depth be `d`.

The path from the root to a deepest node contains exactly `d` edges.

Each edge independently contributes:

```text
1 (odd)
or
2 (even)
```

The parity of the total path cost depends only on how many edges receive weight `1`.

For a path of length `d`:

```text
Total assignments = 2^d
```

For every assignment producing an even sum, flipping the first edge's weight creates a unique assignment producing an odd sum.

Thus:

```text
Odd assignments = Even assignments = 2^(d-1)
```

Therefore, the number of valid assignments is:

```text
2^(d-1)
```

Since the answer depends only on the deepest path length, finding the maximum depth is sufficient.

---

# Algorithm

1. Build an adjacency list.
2. Run BFS from node `1`.
3. Compute the maximum depth.
4. Return:

```text
2^(maxDepth - 1) mod (1e9 + 7)
```

using fast modular exponentiation.

---

# Key Techniques Used

### Graph Traversal

- Breadth First Search (BFS)
- Depth tracking

### Mathematical Observation

- Parity of sums
- Equal distribution of odd/even assignments

### Fast Exponentiation

- Binary Exponentiation
- Modular Arithmetic

---

# Complexity Analysis

### Time Complexity

Building the graph:

```text
O(n)
```

BFS traversal:

```text
O(n)
```

Binary exponentiation:

```text
O(log n)
```

Overall:

```text
O(n)
```

### Space Complexity

Adjacency list:

```text
O(n)
```

Depth array and queue:

```text
O(n)
```

Overall:

```text
O(n)
```

---

# Code

```cpp []
class Solution {
public:
    static constexpr long long MOD = 1000000007LL;

    long long modPow(long long base, long long exp) {
        long long res = 1;
        while (exp) {
            if (exp & 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return res;
    }

    int assignEdgeWeights(vector<vector<int>>& edges) {
        int n = edges.size() + 1;

        vector<vector<int>> g(n + 1);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];

            g[u].push_back(v);
            g[v].push_back(u);
        }

        queue<int> q;
        vector<int> depth(n + 1, -1);

        q.push(1);
        depth[1] = 0;

        int maxDepth = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            maxDepth = max(maxDepth, depth[u]);

            for (int v : g[u]) {
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    q.push(v);
                }
            }
        }

        if (maxDepth == 0) return 0;

        return (int)modPow(2, maxDepth - 1);
    }
};
```
```java []
class Solution {
    private static final long MOD = 1_000_000_007L;

    public int assignEdgeWeights(int[][] edges) {
        int n = edges.length + 1;

        List<Integer>[] graph = new ArrayList[n + 1];
        for (int i = 1; i <= n; i++) {
            graph[i] = new ArrayList<>();
        }

        for (int[] e : edges) {
            int u = e[0];
            int v = e[1];
            graph[u].add(v);
            graph[v].add(u);
        }

        Queue<Integer> q = new LinkedList<>();
        int[] depth = new int[n + 1];
        Arrays.fill(depth, -1);

        q.offer(1);
        depth[1] = 0;

        int maxDepth = 0;

        while (!q.isEmpty()) {
            int u = q.poll();
            maxDepth = Math.max(maxDepth, depth[u]);

            for (int v : graph[u]) {
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    q.offer(v);
                }
            }
        }

        if (maxDepth == 0) return 0;

        return (int) modPow(2, maxDepth - 1);
    }

    private long modPow(long base, long exp) {
        long res = 1;

        while (exp > 0) {
            if ((exp & 1) == 1) {
                res = (res * base) % MOD;
            }
            base = (base * base) % MOD;
            exp >>= 1;
        }

        return res;
    }
}

```
```python []
class Solution(object):
    MOD = 1000000007

    def assignEdgeWeights(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: int
        """
        n = len(edges) + 1

        graph = [[] for _ in range(n + 1)]
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        depth = [-1] * (n + 1)
        depth[1] = 0

        q = [1]
        front = 0
        max_depth = 0

        while front < len(q):
            u = q[front]
            front += 1

            max_depth = max(max_depth, depth[u])

            for v in graph[u]:
                if depth[v] == -1:
                    depth[v] = depth[u] + 1
                    q.append(v)

        if max_depth == 0:
            return 0

        return pow(2, max_depth - 1, self.MOD)

```
```Javascript []
/**
 * @param {number[][]} edges
 * @return {number}
 */
var assignEdgeWeights = function(edges) {
    const MOD = 1000000007n;
    const n = edges.length + 1;

    const graph = Array.from({ length: n + 1 }, () => []);

    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }

    let maxDepth = 0;
    const stack = [[1, 0, 0]]; // node, parent, depth

    while (stack.length) {
        const [u, parent, depth] = stack.pop();
        maxDepth = Math.max(maxDepth, depth);

        for (const v of graph[u]) {
            if (v !== parent) {
                stack.push([v, u, depth + 1]);
            }
        }
    }

    if (maxDepth === 0) return 0;

    let base = 2n;
    let exp = BigInt(maxDepth - 1);
    let result = 1n;

    while (exp > 0n) {
        if (exp & 1n) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1n;
    }

    return Number(result);
};

```
```C []
#define MOD 1000000007LL

long long modPow(long long base, long long exp) {
    long long res = 1;

    while (exp > 0) {
        if (exp & 1)
            res = (res * base) % MOD;

        base = (base * base) % MOD;
        exp >>= 1;
    }

    return res;
}

int assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize) {
    int n = edgesSize + 1;

    int *deg = (int *)calloc(n + 1, sizeof(int));

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        deg[u]++;
        deg[v]++;
    }

    int **graph = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 1; i <= n; i++) {
        graph[i] = (int *)malloc(deg[i] * sizeof(int));
        deg[i] = 0;
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        graph[u][deg[u]++] = v;
        graph[v][deg[v]++] = u;
    }

    int *stackNode = (int *)malloc((n + 1) * sizeof(int));
    int *stackParent = (int *)malloc((n + 1) * sizeof(int));
    int *stackDepth = (int *)malloc((n + 1) * sizeof(int));

    int top = 0;
    stackNode[top] = 1;
    stackParent[top] = 0;
    stackDepth[top] = 0;
    top++;

    int maxDepth = 0;

    while (top) {
        top--;

        int u = stackNode[top];
        int parent = stackParent[top];
        int depth = stackDepth[top];

        if (depth > maxDepth)
            maxDepth = depth;

        for (int i = 0; i < deg[u]; i++) {
            int v = graph[u][i];

            if (v != parent) {
                stackNode[top] = v;
                stackParent[top] = u;
                stackDepth[top] = depth + 1;
                top++;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        free(graph[i]);

    free(graph);
    free(deg);
    free(stackNode);
    free(stackParent);
    free(stackDepth);

    if (maxDepth == 0)
        return 0;

    return (int)modPow(2, maxDepth - 1);
}
```
