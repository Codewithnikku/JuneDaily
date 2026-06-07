# Left & Right Sum Differences

# Intuition
<!-- Describe your first thoughts on how to solve this problem. -->

# Approach
<!-- Describe your approach to solving the problem. -->

# Complexity
- Time complexity:
<!-- Add your time complexity here, e.g. $$O(n)$$ -->

- Space complexity:
<!-- Add your space complexity here, e.g. $$O(n)$$ -->

# Code
## C++
```cpp []
class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int n = nums.size();
        int rightSum = 0;
        int leftSum = 0;
        vector<int> ans(n);
        for(int x : nums) rightSum += x;
        for(int i=0; i<n; i++) {
            rightSum -= nums[i];
            ans[i] = abs(leftSum - rightSum);
            leftSum += nums[i];
        }
    return ans;
    }
};
```
```java []
class LeftRightSumDifferences {
    public int[] leftRightDifference(int[] nums) {
        int n = nums.length;
        int[] ans = new int[n];

        int rightSum = 0;
        for (int num : nums) {
            rightSum += num;
        }

        int leftSum = 0;
        for (int i = 0; i < n; i++) {
            rightSum -= nums[i];
            ans[i] = Math.abs(leftSum - rightSum);
            leftSum += nums[i];
        }

        return ans;
    }
}
```
```python []
class LeftRightSUmDifferences(object):
    def leftRightDifference(self, nums):
        n = len(nums)
        ans = [0] * n

        right_sum = sum(nums)
        left_sum = 0

        for i in range(n):
            right_sum -= nums[i]
            ans[i] = abs(left_sum - right_sum)
            left_sum += nums[i]

        return ans
```
```javascript []
var leftRightDifference = function(nums) {
    const n = nums.length;
    const ans = new Array(n);

    let rightSum = 0;
    for (const num of nums) {
        rightSum += num;
    }

    let leftSum = 0;
    for (let i = 0; i < n; i++) {
        rightSum -= nums[i];
        ans[i] = Math.abs(leftSum - rightSum);
        leftSum += nums[i];
    }

    return ans;
};
```
```c []
int* leftRightDifference(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    
    int* ans = (int*)malloc(numsSize * sizeof(int));
    
    int rightSum = 0;
    for (int i = 0; i < numsSize; i++) {
        rightSum += nums[i];
    }
    
    int leftSum = 0;
    for (int i = 0; i < numsSize; i++) {
        rightSum -= nums[i];
        
        int diff = leftSum - rightSum;
        ans[i] = diff < 0 ? -diff : diff;
        
        leftSum += nums[i];
    }
    
    return ans;
}
```