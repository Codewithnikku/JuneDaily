class EarliestFinishTimeForLandAndWaterRides_II(object):
    def earliestFinishTime(self, landStartTime, landDuration, waterStartTime, waterDuration):
        def solve(s1, d1, s2, d2):
            rides = sorted(zip(s2, d2))
            m = len(rides)

            starts = [0] * m
            prefMinDur = [0] * m
            suffMinFinish = [0] * m

            for i in range(m):
                starts[i] = rides[i][0]

            for i in range(m):
                prefMinDur[i] = rides[i][1]
                if i > 0:
                    prefMinDur[i] = min(prefMinDur[i], prefMinDur[i - 1])

            for i in range(m - 1, -1, -1):
                suffMinFinish[i] = rides[i][0] + rides[i][1]
                if i + 1 < m:
                    suffMinFinish[i] = min(suffMinFinish[i], suffMinFinish[i + 1])

            ans = float('inf')

            for i in range(len(s1)):
                t = s1[i] + d1[i]

                l, r = 0, m
                while l < r:
                    mid = (l + r) // 2
                    if starts[mid] <= t:
                        l = mid + 1
                    else:
                        r = mid
                pos = l

                if pos > 0:
                    ans = min(ans, t + prefMinDur[pos - 1])

                if pos < m:
                    ans = min(ans, suffMinFinish[pos])

            return ans

        return min(
            solve(landStartTime, landDuration, waterStartTime, waterDuration),
            solve(waterStartTime, waterDuration, landStartTime, landDuration)
        )
        
eftrlwr_II = EarliestFinishTimeForLandAndWaterRides_II()
Data = {
    "landStartTime": [2, 8],
    "landDuration": [4, 1],
    "waterStartTime": [6],
    "waterDuration": [3]
}

print(f"Output: {eftrlwr_II.earliestFinishTime(Data['landStartTime'], Data['landDuration'], Data['waterStartTime'], Data['waterDuration'])}")