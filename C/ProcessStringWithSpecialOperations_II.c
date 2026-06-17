char processStr(char* s, long long k) {
    const long long INF = 1000000000000001LL;

    int n = strlen(s);

    long long* len = (long long*)calloc(n + 1, sizeof(long long));

    for (int i = 0; i < n; i++) {
        char c = s[i];

        if (c >= 'a' && c <= 'z') {
            len[i + 1] = (len[i] + 1 < INF) ? len[i] + 1 : INF;
        }
        else if (c == '*') {
            len[i + 1] = (len[i] > 0) ? len[i] - 1 : 0;
        }
        else if (c == '#') {
            if (len[i] >= INF / 2)
                len[i + 1] = INF;
            else
                len[i + 1] = len[i] * 2;
        }
        else { // '%'
            len[i + 1] = len[i];
        }
    }

    if (k >= len[n]) {
        free(len);
        return '.';
    }

    for (int i = n - 1; i >= 0; i--) {
        char c = s[i];

        if (c >= 'a' && c <= 'z') {
            long long prevLen = len[i];

            if (k == prevLen) {
                free(len);
                return c;
            }
        }
        else if (c == '*') {
            // no change
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

    free(len);
    return '.';
}