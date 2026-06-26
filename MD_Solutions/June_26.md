# 🚀 Count Subarrays With Majority Element II

## Intuition

A subarray is valid if `target` appears **strictly more than half** of its length.

Instead of counting occurrences directly, we can transform the array into a balance array:

- If `nums[i] == target`, contribute **+1**
- Otherwise, contribute **-1**

Now consider any subarray.

Let:

- `T` = number of target elements
- `O` = number of non-target elements

The majority condition is

```
T > O
```

which is equivalent to

```
T - O > 0
```

After our transformation, every target contributes `+1` and every other element contributes `-1`, so the subarray sum becomes

```
(+1 × T) + (-1 × O)
= T - O
```

Therefore,

> **A subarray has `target` as the majority element if and only if its transformed sum is positive.**

So the original problem becomes:

> **Count the number of subarrays whose transformed sum is greater than 0.**

---

# Example

Suppose

```
nums = [1,2,2,3]
target = 2
```

Transform the array

```
[-1, +1, +1, -1]
```

Prefix balances become

```
0
-1
0
1
0
```

Every pair of prefix sums where

```
previousPrefix < currentPrefix
```

forms a valid subarray because

```
currentPrefix - previousPrefix > 0
```

which means the subarray sum is positive.

---

# Key Observation

For every prefix balance:

```
balance += 1    if nums[i] == target
balance -= 1    otherwise
```

Suppose current balance is

```
currentBalance
```

A previous prefix contributes a valid subarray when

```
previousBalance < currentBalance
```

So while scanning the array, we only need to know

> **How many previous balances are strictly smaller than the current balance?**

That value is added directly to the answer.

---

# Approach

### Step 1

Convert the problem into a prefix balance problem.

```
target      -> +1
others      -> -1
```

---

### Step 2

Maintain a running prefix balance.

```
balance += 1
balance -= 1
```

Instead of storing negative indices, shift the balance by

```
offset = n + 1
```

so every balance maps to a valid array index.

---

### Step 3

Maintain two arrays.

### countAtSum

```
countAtSum[i]
```

stores

> Number of times this exact balance has appeared.

---

### comulativeCount

```
comulativeCount[i]
```

stores

> Total number of balances ≤ i.

This allows answering

```
How many balances are smaller than me?
```

in **O(1)** time.

---

### Step 4

For every element

Update the balance.

```
if target
    balance++
else
    balance--
```

Increase its frequency.

```
countAtSum[balance]++
```

All previous balances smaller than current contribute valid subarrays.

```
answer += comulativeCount[balance-1]
```

Finally update cumulative counts.

```
comulativeCount[balance]
=
comulativeCount[balance-1]
+
countAtSum[balance]
```

---

# Dry Run

```
nums = [1,2,2]
target = 2
```

Transformation

```
[-1,+1,+1]
```

Initial

```
balance = 4
```

(after offset)

```
count[4]=1
cum[4]=1
```

---

### Element = 1

```
balance = 3
```

```
answer += cum[2] = 0
```

Update

```
count[3]=1
cum[3]=1
```

---

### Element = 2

```
balance = 4
```

```
answer += cum[3]=1
```

Valid subarray

```
[2]
```

Update

```
count[4]=2
cum[4]=3
```

---

### Element = 2

```
balance = 5
```

```
answer += cum[4]=3
```

Three more valid subarrays are counted.

Final answer

```
4
```

---

# Why This Works

Suppose

```
prefix[j] > prefix[i]
```

Then

```
prefix[j]-prefix[i] > 0
```

which means

```
target count
>
non-target count
```

Therefore every such pair represents one valid subarray.

Our algorithm efficiently counts these pairs in one traversal.

---

# Complexity Analysis

### Time Complexity

```
O(n)
```

Every element is processed exactly once.

---

### Space Complexity

```
O(n)
```

Two arrays of size roughly `2n` are maintained.

```cpp []
class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        int len = 2 * n + 2;

        vector<long long> countAtSum(len, 0);
        vector<long long> comulativeCount(len, 0);

        int idx = n + 1;
        countAtSum[idx] = 1;
        comulativeCount[idx] = 1;

        long long ans = 0;

        for (int num : nums) {
            if (num == target)
                idx++;
            else
                idx--;

            countAtSum[idx]++;
            ans += comulativeCount[idx - 1];
            comulativeCount[idx] = comulativeCount[idx - 1] + countAtSum[idx];
        }

        return ans;
    }
};
```
```java []
class Solution {
    public long countMajoritySubarrays(int[] nums, int target) {
        int n = nums.length;
        int len = 2 * n + 2;

        long[] countAtSum = new long[len];
        long[] comulativeCount = new long[len];

        int idx = n + 1;
        countAtSum[idx] = 1;
        comulativeCount[idx] = 1;

        long ans = 0;

        for (int num : nums) {
            if (num == target)
                idx++;
            else
                idx--;

            countAtSum[idx]++;
            ans += comulativeCount[idx - 1];
            comulativeCount[idx] = comulativeCount[idx - 1] + countAtSum[idx];
        }

        return ans;
    }
}
```
```python []
class Solution(object):
    def countMajoritySubarrays(self, nums, target):
        n = len(nums)
        length = 2 * n + 2

        countAtSum = [0] * length
        comulativeCount = [0] * length

        idx = n + 1
        countAtSum[idx] = 1
        comulativeCount[idx] = 1

        ans = 0

        for num in nums:
            if num == target:
                idx += 1
            else:
                idx -= 1

            countAtSum[idx] += 1
            ans += comulativeCount[idx - 1]
            comulativeCount[idx] = comulativeCount[idx - 1] + countAtSum[idx]

        return ans
```
```javascript []
var countMajoritySubarrays = function(nums, target) {
    const n = nums.length;
    const len = 2 * n + 2;

    const countAtSum = new Array(len).fill(0);
    const comulativeCount = new Array(len).fill(0);

    let idx = n + 1;
    countAtSum[idx] = 1;
    comulativeCount[idx] = 1;

    let ans = 0;

    for (const num of nums) {
        if (num === target)
            idx++;
        else
            idx--;

        countAtSum[idx]++;
        ans += comulativeCount[idx - 1];
        comulativeCount[idx] = comulativeCount[idx - 1] + countAtSum[idx];
    }

    return ans;
};
```

---

# Summary

✅ Convert the array into `+1/-1`.

✅ Majority becomes **positive subarray sum**.

✅ Maintain prefix balances.

✅ Count how many previous balances are smaller than the current balance.

✅ Use frequency and cumulative frequency arrays for **O(1)** queries.

✅ Scan the array once.

Overall Complexity

| Metric | Complexity |
|--------|------------|
| Time | **O(n)** |
| Space | **O(n)** |

---

## Key Takeaways

- Prefix sums can convert majority problems into balance problems.
- Replacing values with `+1` and `-1` is a common competitive programming trick.
- Counting prefix pairs often transforms seemingly quadratic problems into linear solutions.
- Using an offset avoids handling negative indices while keeping the implementation simple and efficient.