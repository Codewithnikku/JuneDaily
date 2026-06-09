class Solution(object):
    def maxTotalValue(self, nums, k):
        mn = min(nums)
        mx = max(nums)
        return k * (mx - mn)