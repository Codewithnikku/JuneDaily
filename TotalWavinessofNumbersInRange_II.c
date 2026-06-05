#include <stdio.h>

typedef struct {
    long long cnt;
    long long wav;
} Node;

char s[25];
Node dp[20][2][3][11][11];
char vis[20][2][3][11][11];

Node dfs(int pos, int started, int len, int a, int b, int tight) {
    if (s[pos] == '\0') {
        Node res = {1, 0};
        return res;
    }

    if (!tight && vis[pos][started][len][a][b]) {
        return dp[pos][started][len][a][b];
    }

    int limit = tight ? (s[pos] - '0') : 9;

    Node res = {0, 0};

    for (int d = 0; d <= limit; d++) {
        int ntight = tight && (d == limit);

        if (!started && d == 0) {
            Node nxt = dfs(pos + 1, 0, 0, 10, 10, ntight);
            res.cnt += nxt.cnt;
            res.wav += nxt.wav;
        } else {
            if (!started) {
                Node nxt = dfs(pos + 1, 1, 1, 10, d, ntight);
                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            } else if (len == 1) {
                Node nxt = dfs(pos + 1, 1, 2, b, d, ntight);
                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            } else {
                int add = ((b > a && b > d) || (b < a && b < d));

                Node nxt = dfs(pos + 1, 1, 2, b, d, ntight);

                res.cnt += nxt.cnt;
                res.wav += nxt.wav + nxt.cnt * add;
            }
        }
    }

    if (!tight) {
        vis[pos][started][len][a][b] = 1;
        dp[pos][started][len][a][b] = res;
    }

    return res;
}

long long solve(long long n) {
    if (n < 0) return 0;

    memset(vis, 0, sizeof(vis));
    sprintf(s, "%lld", n);

    return dfs(0, 0, 0, 10, 10, 1).wav;
}

long long totalWaviness(long long num1, long long num2) {
    return solve(num2) - solve(num1 - 1);
}

int main(){
    int num1 = 120;
    int num2 = 130;
    printf("%lld\n", totalWaviness(num1, num2));
    return 0;
}