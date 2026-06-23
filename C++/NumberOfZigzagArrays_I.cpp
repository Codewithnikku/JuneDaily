#include<vector>
using namespace std;

class NumberOfZigzagArrays_I {
public:
    static constexpr int MOD = 1000000007;

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        vector<long long> up(m, 1), down(m, 1);
        vector<long long> pre(m + 1), suf(m + 1);
        vector<long long> newUp(m), newDown(m);

        for (int len = 2; len <= n; len++) {
            pre[0] = 0;
            for (int i = 0; i < m; i++) {
                pre[i + 1] = (pre[i] + down[i]) % MOD;
            }

            suf[m] = 0;
            for (int i = m - 1; i >= 0; i--) {
                suf[i] = (suf[i + 1] + up[i]) % MOD;
            }

            for (int i = 0; i < m; i++) {
                newUp[i] = pre[i];
                newDown[i] = suf[i + 1];
            }

            up.swap(newUp);
            down.swap(newDown);
        }

        long long ans = 0;
        for (int i = 0; i < m; i++) {
            ans = (ans + up[i] + down[i]) % MOD;
        }

        return (int)ans;
    }
};