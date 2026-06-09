# Partition Array According to Given Pivot

## Intuition

The problem requires partitioning the array into three groups while **preserving the relative order** of elements:

1. Elements smaller than `pivot`
2. Elements equal to `pivot`
3. Elements greater than `pivot`

A straightforward observation is that the final array is simply the concatenation of these three groups in the above order. Since the relative order inside each group must remain unchanged, we can process the array sequentially and place elements into their respective sections.

---

## Approach

### Method 1 (C++, Python)

We can build the answer directly by:

- First collecting all elements `< pivot`
- Then collecting all elements `== pivot`
- Finally collecting all elements `> pivot`

Since we traverse the array in order during each pass, the relative ordering is preserved automatically.

### Method 2 (Java, JavaScript, C)

To avoid maintaining multiple temporary containers:

1. Count how many elements are:
   - Less than `pivot`
   - Equal to `pivot`
2. These counts determine the starting positions of all three partitions.
3. Create the result array of size `n`.
4. Traverse the array once more and place each element directly into its corresponding partition.

This approach is memory-efficient and performs very well in practice.

---

## Example

### Input

```text
nums = [9,12,5,10,14,3,10]
pivot = 10
```

### Step 1: Count partitions

```text
< 10  → [9,5,3]
= 10  → [10,10]
> 10  → [12,14]
```

### Step 2: Combine partitions

```text
[9,5,3] + [10,10] + [12,14]
```

### Output

```text
[9,5,3,10,10,12,14]
```

---

## Why This Works

The algorithm explicitly constructs the final ordering required by the problem:

```text
All values < pivot
        ↓
All values = pivot
        ↓
All values > pivot
```

Since elements are processed in their original order within each group, the relative ordering remains unchanged.

---

## Complexity Analysis

### C++, Python

- **Time Complexity:** `O(n)`
- **Space Complexity:** `O(n)`

### Java, JavaScript, C

- **Time Complexity:** `O(n)`
- **Space Complexity:** `O(n)`

Both approaches are optimal since every element must be inspected at least once.

---

# C++

```cpp
class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> ans;
        ans.reserve(nums.size());

        for (int x : nums)
            if (x < pivot)
                ans.push_back(x);

        for (int x : nums)
            if (x == pivot)
                ans.push_back(x);

        for (int x : nums)
            if (x > pivot)
                ans.push_back(x);

        return ans;
    }
};
```

# Java

```java
class Solution {
    public int[] pivotArray(int[] nums, int pivot) {
        int n = nums.length;
        int less = 0, equal = 0;

        for (int x : nums) {
            if (x < pivot) {
                less++;
            } else if (x == pivot) {
                equal++;
            }
        }

        int[] ans = new int[n];

        int i = 0;
        int j = less;
        int k = less + equal;

        for (int x : nums) {
            if (x < pivot) {
                ans[i++] = x;
            } else if (x == pivot) {
                ans[j++] = x;
            } else {
                ans[k++] = x;
            }
        }

        return ans;
    }
}
```

# Python

```python
class Solution(object):
    def pivotArray(self, nums, pivot):
        return (
            [x for x in nums if x < pivot] +
            [x for x in nums if x == pivot] +
            [x for x in nums if x > pivot]
        )
```

# JavaScript

```javascript
var pivotArray = function(nums, pivot) {
    const n = nums.length;
    let less = 0, equal = 0;

    for (let i = 0; i < n; i++) {
        if (nums[i] < pivot) less++;
        else if (nums[i] === pivot) equal++;
    }

    const ans = new Array(n);

    let i = 0;
    let j = less;
    let k = less + equal;

    for (let p = 0; p < n; p++) {
        const x = nums[p];

        if (x < pivot) {
            ans[i++] = x;
        } else if (x === pivot) {
            ans[j++] = x;
        } else {
            ans[k++] = x;
        }
    }

    return ans;
};
```

# C

```c
int* pivotArray(int* nums, int numsSize, int pivot, int* returnSize) {
    int less = 0, equal = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < pivot)
            less++;
        else if (nums[i] == pivot)
            equal++;
    }

    int* ans = (int*)malloc(numsSize * sizeof(int));

    int i = 0;
    int j = less;
    int k = less + equal;

    for (int p = 0; p < numsSize; p++) {
        int x = nums[p];

        if (x < pivot)
            ans[i++] = x;
        else if (x == pivot)
            ans[j++] = x;
        else
            ans[k++] = x;
    }

    *returnSize = numsSize;
    return ans;
}
```

---

### Key Takeaway

The core idea is to **preserve order while partitioning**. By either:
- collecting elements in three ordered passes, or
- precomputing partition boundaries and placing elements directly,

we obtain an optimal `O(n)` solution that satisfies all constraints efficiently.