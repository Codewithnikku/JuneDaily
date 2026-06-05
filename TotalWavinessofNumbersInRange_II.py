class TotalWavinessofNumbersInRange_II(object):
    def totalWaviness(self, num1, num2):
        def solve(n):
            if n < 0:
                return 0

            s = str(n)
            memo = {}

            def dfs(pos, started, length, a, b, tight):
                if pos == len(s):
                    return (1, 0)

                if not tight:
                    key = (pos, started, length, a, b)
                    if key in memo:
                        return memo[key]

                limit = int(s[pos]) if tight else 9
                total_cnt = 0
                total_wav = 0

                for d in range(limit + 1):
                    ntight = tight and (d == limit)

                    if not started and d == 0:
                        cnt, wav = dfs(pos + 1, False, 0, 10, 10, ntight)
                        total_cnt += cnt
                        total_wav += wav
                    else:
                        if not started:
                            cnt, wav = dfs(pos + 1, True, 1, 10, d, ntight)
                            total_cnt += cnt
                            total_wav += wav
                        elif length == 1:
                            cnt, wav = dfs(pos + 1, True, 2, b, d, ntight)
                            total_cnt += cnt
                            total_wav += wav
                        else:
                            add = 1 if ((b > a and b > d) or (b < a and b < d)) else 0
                            cnt, wav = dfs(pos + 1, True, 2, b, d, ntight)
                            total_cnt += cnt
                            total_wav += wav + cnt * add

                res = (total_cnt, total_wav)

                if not tight:
                    memo[(pos, started, length, a, b)] = res

                return res

            return dfs(0, False, 0, 10, 10, True)[1]

        return solve(num2) - solve(num1 - 1)
    
# Example usage:
solver = TotalWavinessofNumbersInRange_II()
num1 = 120
num2 = 130
print(solver.totalWaviness(num1, num2))