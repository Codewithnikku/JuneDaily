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

nums = [10, 4, 8, 3]

lrsd = LeftRightSUmDifferences()
print(lrsd.leftRightDifference(nums))