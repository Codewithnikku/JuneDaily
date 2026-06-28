class MaximumElementAfterDescendingAndRearranging(object):
    def maximumElementAfterDecrementingAndRearranging(self, arr):
        n = len(arr)
        ans = 1
        count = [0] * (n + 1)

        for a in arr:
            idx = min(a, n)
            count[idx] += 1

        for i in range(2, n + 1):
            curr = ans + count[i]
            ans = min(i, curr)

        return ans