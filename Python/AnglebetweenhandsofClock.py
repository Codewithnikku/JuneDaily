class Solution(object):
    def angleClock(self, hour, minutes):
        hourDegree = (hour % 12) * 30 + 0.5 * minutes
        minuteDegree = minutes * 6

        diff = abs(hourDegree - minuteDegree)
        return min(diff, 360 - diff)

if __name__ == "__main__":
    hour = int(input("Enter hour: "))
    minutes = int(input("Enter minutes: "))

    sol = Solution()
    print("Angle:", sol.angleClock(hour, minutes))