from heapq import heappush, heappop

class SparseTable:
    def __init__(self, nums):
        n = len(nums)
        w = n.bit_length()

        self.min_table = [[0] * n for _ in range(w)]
        self.max_table = [[0] * n for _ in range(w)]

        for i in range(n):
            self.min_table[0][i] = nums[i]
            self.max_table[0][i] = nums[i]

        for k in range(1, w):
            half = 1 << (k - 1)
            length = 1 << k

            for j in range(n - length + 1):
                self.min_table[k][j] = min(
                    self.min_table[k - 1][j],
                    self.min_table[k - 1][j + half]
                )

                self.max_table[k][j] = max(
                    self.max_table[k - 1][j],
                    self.max_table[k - 1][j + half]
                )

    def query(self, left, right):
        # range [left, right)
        length = right - left
        if length <= 0:
            return 0

        k = length.bit_length() - 1

        mx = max(
            self.max_table[k][left],
            self.max_table[k][right - (1 << k)]
        )

        mn = min(
            self.min_table[k][left],
            self.min_table[k][right - (1 << k)]
        )

        return mx - mn


class Solution:
    def maxTotalValue(self, nums, k):
        n = len(nums)
        res = 0

        lut = SparseTable(nums)

        # max heap using negative values
        pq = []

        for i in range(n):
            heappush(pq, (-lut.query(i, n), i, n))

        while pq and k > 0:
            neg_val, l, r = heappop(pq)
            val = -neg_val

            if val == 0:
                break

            res += val
            k -= 1

            if r - l > 1:
                heappush(
                    pq,
                    (-lut.query(l, r - 1), l, r - 1)
                )

        return res