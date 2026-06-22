class MaximumNumbersOfBalloons(object):
    def maxNumberOfBalloons(self, text):
        """
        :type text: str
        :rtype: int
        """
        freq = [0] * 26

        for ch in text:
            freq[ord(ch) - ord('a')] += 1

        mn = freq[ord('b') - ord('a')]
        mn = min(mn, freq[ord('a') - ord('a')])
        mn = min(mn, freq[ord('n') - ord('a')])
        mn = min(mn, freq[ord('l') - ord('a')] // 2)
        mn = min(mn, freq[ord('o') - ord('a')] // 2)

        return mn