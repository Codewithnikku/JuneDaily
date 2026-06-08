class MinimumCostOfBuyingCanddatesWithDiscount(object):
    def minimumCost(self, cost):
        cost.sort(reverse=True)
        ans = 0

        for i in range(len(cost)):
            if i % 3 != 2:
                ans += cost[i]

        return ans
    
    
mcbcwd = MinimumCostOfBuyingCanddatesWithDiscount()
print(mcbcwd.minimumCost([1, 2, 3]))  