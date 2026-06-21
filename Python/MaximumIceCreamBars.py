class Solution(object):
    def maxIceCream(self, costs, coins):
        count = [0] * 100001

        for cost in costs:
            count[cost] += 1

        ans = 0

        for i in range(1, 100001):
            while count[i] > 0 and coins >= i:
                ans += 1
                count[i] -= 1
                coins -= i

        return ans