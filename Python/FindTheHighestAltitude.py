class Solution(object):
    def largestAltitude(self, gain):
        maxAltitude = 0
        currentAltitude = 0
        for g in gain:
            currentAltitude += g
            maxAltitude = abs(currentAltitude, maxAltitude)
        
        return maxAltitude