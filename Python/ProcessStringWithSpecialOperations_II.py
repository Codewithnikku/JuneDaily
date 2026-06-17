class ProcessStringWithSpecialOperations_II(object):
    def processStr(self, s, k):
        INF = 10**15 + 1
        n = len(s)

        L = [0] * (n + 1)

        for i, ch in enumerate(s):
            if ch.isalpha():
                L[i + 1] = min(INF, L[i] + 1)
            elif ch == '*':
                L[i + 1] = max(0, L[i] - 1)
            elif ch == '#':
                L[i + 1] = min(INF, L[i] * 2)
            else:
                L[i + 1] = L[i]

        if k >= L[n]:
            return '.'

        for i in range(n - 1, -1, -1):
            ch = s[i]

            if ch.isalpha():
                if k == L[i]:
                    return ch
            elif ch == '#':
                if L[i]:
                    k %= L[i]
            elif ch == '%':
                if L[i]:
                    k = L[i] - 1 - k

        return '.'