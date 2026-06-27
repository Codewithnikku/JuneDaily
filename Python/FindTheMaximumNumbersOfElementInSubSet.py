class FindTheMaximumNumbersOfElementInSubSet(object):
    def maximumLength(self, nums):
        freq = {}
        for num in nums:
            freq[num] = freq.get(num, 0) + 1

        ans = 0
        if 1 in freq:
            ones = freq[1]
            ans = ones - 1 if ones % 2 == 0 else ones
            del freq[1]

        memo = {}
        def dfs(num):
            if num not in freq:
                return 0
            if num in memo:
                return memo[num]
            if freq[num] >= 2:
                count = 2 + dfs(num * num)
            else:
                count = 1
            if count % 2 == 0:
                count -= 1
            memo[num] = count
            return count

        for num in freq:
            ans = max(ans, dfs(num))
        return ans
