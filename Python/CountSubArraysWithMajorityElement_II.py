class CountSubArraysWithMajorityElement_II(object):
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