class Solution(object):
    def zigZagArrays(self, n, l, r):
        MOD = 1000000007
        m = r - l + 1

        up = [1] * m
        down = [1] * m

        for _ in range(2, n + 1):
            pre = [0] * (m + 1)
            suf = [0] * (m + 1)

            for i in range(m):
                pre[i + 1] = (pre[i] + down[i]) % MOD

            for i in range(m - 1, -1, -1):
                suf[i] = (suf[i + 1] + up[i]) % MOD

            newUp = [0] * m
            newDown = [0] * m

            for i in range(m):
                newUp[i] = pre[i]
                newDown[i] = suf[i + 1]

            up = newUp
            down = newDown

        ans = 0
        for i in range(m):
            ans = (ans + up[i] + down[i]) % MOD

        return ans