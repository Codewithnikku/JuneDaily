#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class TotalWavinessofNumbersInRange_II {
public:
    struct Node {
        long long cnt;
        long long wav;
    };

    string s;
    Node dp[20][2][3][11][11];
    bool vis[20][2][3][11][11];

    Node dfs(int pos, bool started, int len, int a, int b, bool tight) {
        if (pos == (int)s.size()) return {1, 0};

        if (vis[pos][started][len][a][b] && !tight)
            return dp[pos][started][len][a][b];

        int lim = tight ? s[pos] - '0' : 9;
        Node res{0, 0};

        for (int d = 0; d <= lim; d++) {
            bool ntight = tight && (d == lim);

            if (!started && d == 0) {
                Node nxt = dfs(pos + 1, false, 0, 10, 10, ntight);
                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            } else {
                if (!started) {
                    Node nxt = dfs(pos + 1, true, 1, 10, d, ntight);
                    res.cnt += nxt.cnt;
                    res.wav += nxt.wav;
                } else if (len == 1) {
                    Node nxt = dfs(pos + 1, true, 2, b, d, ntight);
                    res.cnt += nxt.cnt;
                    res.wav += nxt.wav;
                } else {
                    int add = ((b > a && b > d) || (b < a && b < d)) ? 1 : 0;
                    Node nxt = dfs(pos + 1, true, 2, b, d, ntight);
                    res.cnt += nxt.cnt;
                    res.wav += nxt.wav + nxt.cnt * add;
                }
            }
        }

        if (!tight) {
            vis[pos][started][len][a][b] = true;
            dp[pos][started][len][a][b] = res;
        }

        return res;
    }

    long long solve(long long n) {
        if (n < 0) return 0;
        memset(vis, 0, sizeof(vis));
        s = to_string(n);
        return dfs(0, false, 0, 10, 10, true).wav;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};

int main(){
    TotalWavinessofNumbersInRange_II solver;
    long long num1 = 120;
    long long num2 = 130;
    std::cout << solver.totalWaviness(num1, num2) << std::endl;
    return 0;
}