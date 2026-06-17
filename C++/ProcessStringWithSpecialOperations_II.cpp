#include<vector>
#include<string>
using namespace std;

class ProcessStringWithSpecialOperations_II {
public:
    char processStr(string s, long long k) {
        const long long INF = (long long)1e15 + 1;

        int n = s.size();
        vector<long long> len(n + 1, 0);

        for (int i = 0; i < n; i++) {
            char c = s[i];

            if ('a' <= c && c <= 'z') {
                len[i + 1] = min(INF, len[i] + 1);
            }
            else if (c == '*') {
                len[i + 1] = max(0LL, len[i] - 1);
            }
            else if (c == '#') {
                len[i + 1] = min(INF, len[i] * 2);
            }
            else { // '%'
                len[i + 1] = len[i];
            }
        }

        if (k >= len[n])
            return '.';

        for (int i = n - 1; i >= 0; i--) {
            char c = s[i];

            if ('a' <= c && c <= 'z') {
                long long prevLen = len[i];

                if (k == prevLen)
                    return c;
            }
            else if (c == '*') {
                // nothing
            }
            else if (c == '#') {
                long long prevLen = len[i];
                if (prevLen > 0)
                    k %= prevLen;
            }
            else { // '%'
                long long prevLen = len[i];
                if (prevLen > 0)
                    k = prevLen - 1 - k;
            }
        }

        return '.';
    }
};