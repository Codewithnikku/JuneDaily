class NumberOfZigzagArrays_II(object):
    def zigZagArrays(self, n, l, r):
        mod = 10**9 + 7
        m = r - l + 1

        T = [[1 if i >= m - j else 0 for j in range(m)] for i in range(m)]

        def mul(A, B):
            return [[sum(A[i][k] * B[k][j] for k in range(m)) % mod
                     for j in range(m)] for i in range(m)]

        def mpow(base, e):
            res = [[int(i == j) for j in range(m)] for i in range(m)]
            while e:
                if e & 1:
                    res = mul(res, base)
                base = mul(base, base)
                e >>= 1
            return res

        P = mpow(T, n - 1)
        return 2 * sum(sum(row) for row in P) % mod