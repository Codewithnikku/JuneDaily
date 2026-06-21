class Solution(object):
    def maxBuilding(self, n, restrictions):
        restrictions.sort()
        l = len(restrictions)
        if not l:
            return n - 1

        is_last = restrictions[-1][0] == n
        m = l + 1 + (0 if is_last else 1)
        h = [[0, 0] for _ in range(m)]
        h[0] = [1, 0]
        ans = 0

        for i, (idx, mx) in enumerate(restrictions):
            h[i + 1] = [idx, min(h[i][1] + idx - h[i][0], mx)]

        if not is_last:
            h[l + 1] = [n, min(h[l][1] + n - h[l][0], n - 1)]

        for i in range(m - 2, -1, -1):
            h[i][1] = min(h[i][1], h[i + 1][1] + h[i + 1][0] - h[i][0])

        for i in range(1, m):
            d = h[i][0] - h[i - 1][0]
            ans = max(ans, (d + h[i][1] + h[i - 1][1]) // 2)

        return ans