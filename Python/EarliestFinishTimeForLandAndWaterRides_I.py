from bisect import bisect_right

class EarliestFinishTimeForLandAndWaterRides_I(object):
    def earliestFinishTime(self, landStartTime, landDuration, waterStartTime, waterDuration):
        ans = float('inf')

        water = sorted(zip(waterStartTime, waterDuration))
        m = len(water)

        wStart = [0] * m
        wPref = [0] * m
        wSuff = [0] * m

        for i in range(m):
            wStart[i] = water[i][0]
            wPref[i] = water[i][1]
            if i:
                wPref[i] = min(wPref[i], wPref[i - 1])

        for i in range(m - 1, -1, -1):
            wSuff[i] = water[i][0] + water[i][1]
            if i + 1 < m:
                wSuff[i] = min(wSuff[i], wSuff[i + 1])

        for s, d in zip(landStartTime, landDuration):
            x = s + d
            p = bisect_right(wStart, x) - 1

            cur = float('inf')
            if p >= 0:
                cur = min(cur, x + wPref[p])
            if p + 1 < m:
                cur = min(cur, wSuff[p + 1])

            ans = min(ans, cur)

        land = sorted(zip(landStartTime, landDuration))
        n = len(land)

        lStart = [0] * n
        lPref = [0] * n
        lSuff = [0] * n

        for i in range(n):
            lStart[i] = land[i][0]
            lPref[i] = land[i][1]
            if i:
                lPref[i] = min(lPref[i], lPref[i - 1])

        for i in range(n - 1, -1, -1):
            lSuff[i] = land[i][0] + land[i][1]
            if i + 1 < n:
                lSuff[i] = min(lSuff[i], lSuff[i + 1])

        for s, d in zip(waterStartTime, waterDuration):
            x = s + d
            p = bisect_right(lStart, x) - 1

            cur = float('inf')
            if p >= 0:
                cur = min(cur, x + lPref[p])
            if p + 1 < n:
                cur = min(cur, lSuff[p + 1])

            ans = min(ans, cur)

        return int(ans)
    
eftflwr = EarliestFinishTimeForLandAndWaterRides_I()
Data = {
    "landStartTime": [1, 4, 6],
    "landDuration": [2, 3, 1],
    "waterStartTime": [2, 5],
    "waterDuration": [3, 2]
}

print(f"{eftflwr.earliestFinishTime(Data['landStartTime'], Data['landDuration'], Data['waterStartTime'], Data['waterDuration'])}")