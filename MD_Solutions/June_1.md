
# Minimum Cost Of Buying Canddates With Discount

# Intuition
To minimize the total amount we pay, we should maximize the value of the candies that become free.

The offer allows us to get **one candy for free for every three candies purchased**, where the free candy must have a cost less than or equal to the other two candies in that group.

A greedy observation is that if we sort the costs in descending order, then for every group of three candies:

- The first two candies are paid for.
- The third candy (the cheapest within that group) can be taken for free.

By always making the third most expensive candy in each group free, we maximize the discount and obtain the minimum possible total cost.

# Approach

1. Sort the candy costs in descending order.
2. Traverse the sorted array from left to right.
3. Treat every consecutive group of three candies as one purchase group.
4. Add the cost of the first two candies to the answer.
5. Skip every third candy since it can be obtained for free.
6. Return the accumulated total cost.

This greedy strategy ensures that the highest possible valued candies contribute to the discount while satisfying the offer's conditions.

# Algorithm

1. Sort the `cost` array in decreasing order.
2. Initialize `ans = 0`.
3. Iterate through the sorted array:
   - If the current index is not the third element of a group (`i % 3 != 2`), add its cost to `ans`.
   - Otherwise, skip it because it is free.
4. Return `ans`.

# Why This Works

After sorting in descending order:

```text
[c1, c2, c3, c4, c5, c6, ...]
```

where:

```text
c1 >= c2 >= c3 >= c4 >= c5 >= c6 ...
```

The optimal grouping becomes:

```text
(c1, c2, c3)
(c4, c5, c6)
...
```

For each group:

- Pay for the first two candies.
- Get the third candy free.

Since the free candy is always the smallest within its group and the array is sorted, this arrangement maximizes the total discount and guarantees the minimum payment.

# Complexity

- **Time Complexity:** `O(n log n)`
  - Sorting the array dominates the running time.

- **Space Complexity:**
  - **C++:** `O(1)` (excluding sorting implementation space)
  - **Java:** `O(log n)` to `O(n)` depending on sorting implementation
  - **Python:** `O(n)` due to Timsort
  - **JavaScript:** Depends on the engine's sorting implementation
  - **C:** `O(log n)` on average for recursion stack used by `qsort`

# Code

```cpp []
class Solution {
public:
    int minimumCost(vector<int>& cost) {
        sort(cost.begin(), cost.end(), greater<int>());
        int ans = 0;
        for (int i = 0; i < cost.size(); i++) {
            if (i % 3 != 2) ans += cost[i];
        }
        return ans;
    }
};
```

```java []
class Solution {
    public int minimumCost(int[] cost) {
        Arrays.sort(cost);
        int ans = 0;
        
        for (int i = cost.length - 1, cnt = 0; i >= 0; i--, cnt++) {
            if (cnt % 3 != 2) {
                ans += cost[i];
            }
        }
        
        return ans;
    }
}
```

```python []
class Solution(object):
    def minimumCost(self, cost):
        cost.sort(reverse=True)
        ans = 0

        for i in range(len(cost)):
            if i % 3 != 2:
                ans += cost[i]

        return ans
```

```javascript []
/**
 * @param {number[]} cost
 * @return {number}
 */
var minimumCost = function(cost) {
    cost.sort((a, b) => b - a);

    let ans = 0;

    for (let i = 0; i < cost.length; i++) {
        if (i % 3 !== 2) {
            ans += cost[i];
        }
    }

    return ans;
};
```

```c []
int compare(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int minimumCost(int* cost, int costSize) {
    qsort(cost, costSize, sizeof(int), compare);

    int ans = 0;

    for (int i = 0; i < costSize; i++) {
        if (i % 3 != 2) {
            ans += cost[i];
        }
    }

    return ans;
}
```
