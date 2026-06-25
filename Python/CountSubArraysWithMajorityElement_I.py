class CountSubArraysWithMajorityElement_I(object):
    def countMajoritySubarrays(self, nums, target):
        n = len(nums)
        ans = 0

        for i in range(n):
            count = 0
            for j in range(i, n):
                if nums[j] == target:
                    count += 1

                if count > (j - i + 1) // 2:
                    ans += 1

        return ans