/**
 * @param {string} s
 * @param {number} k
 * @return {character}
 */
var processStr = function(s, k) {
    const INF = 1e15 + 1;

    const n = s.length;
    const len = new Array(n + 1).fill(0);

    for (let i = 0; i < n; i++) {
        const c = s[i];

        if (c >= 'a' && c <= 'z') {
            len[i + 1] = Math.min(INF, len[i] + 1);
        } else if (c === '*') {
            len[i + 1] = Math.max(0, len[i] - 1);
        } else if (c === '#') {
            len[i + 1] = Math.min(INF, len[i] * 2);
        } else { // '%'
            len[i + 1] = len[i];
        }
    }

    if (k >= len[n]) {
        return '.';
    }

    for (let i = n - 1; i >= 0; i--) {
        const c = s[i];

        if (c >= 'a' && c <= 'z') {
            const prevLen = len[i];

            if (k === prevLen) {
                return c;
            }
        } else if (c === '*') {
            // nothing
        } else if (c === '#') {
            const prevLen = len[i];

            if (prevLen > 0) {
                k %= prevLen;
            }
        } else { // '%'
            const prevLen = len[i];

            if (prevLen > 0) {
                k = prevLen - 1 - k;
            }
        }
    }

    return '.';
};