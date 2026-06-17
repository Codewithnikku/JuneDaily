class Solution {
    public char processStr(String s, long k) {
        final long INF = (long)1e15 + 1;

        int n = s.length();
        long[] len = new long[n + 1];

        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);

            if (c >= 'a' && c <= 'z') {
                len[i + 1] = Math.min(INF, len[i] + 1);
            } else if (c == '*') {
                len[i + 1] = Math.max(0L, len[i] - 1);
            } else if (c == '#') {
                len[i + 1] = Math.min(INF, len[i] * 2);
            } else { // '%'
                len[i + 1] = len[i];
            }
        }

        if (k >= len[n]) {
            return '.';
        }

        for (int i = n - 1; i >= 0; i--) {
            char c = s.charAt(i);

            if (c >= 'a' && c <= 'z') {
                long prevLen = len[i];

                if (k == prevLen) {
                    return c;
                }
            } else if (c == '*') {
                // no change to k
            } else if (c == '#') {
                long prevLen = len[i];

                if (prevLen > 0) {
                    k %= prevLen;
                }
            } else { // '%'
                long prevLen = len[i];

                if (prevLen > 0) {
                    k = prevLen - 1 - k;
                }
            }
        }

        return '.';
    }
}

public class ProcessStringWithSpecialOperations_II {
    public static void main(String[] args) {
        
    }
}