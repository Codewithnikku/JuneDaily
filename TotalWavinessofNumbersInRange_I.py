class TotalWavinessofNumbersInRange_I(object):
    def totalWaviness(self, num1, num2):
        total = 0
        for n in range(num1, num2 + 1):
            s = str(n)
            for i in range(1, len(s) - 1):
                if (s[i] > s[i-1] and s[i] > s[i+1]) or \
                   (s[i] < s[i-1] and s[i] < s[i+1]):
                    total += 1
        return total
    

twnir = TotalWavinessofNumbersInRange_I()
num1 = 120
num2 = 130
result = twnir.totalWaviness(num1, num2)
print("Total Waviness:", result)
