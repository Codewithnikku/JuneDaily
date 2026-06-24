#include <vector>
using namespace std;

class NumberOfZigzagArrays_II{
public:
    static const int mod = 1000000007;

    vector<vector<long long>> mul(const vector<vector<long long>>& A,
                                  const vector<vector<long long>>& B) {
        int m = A.size();
        vector<vector<long long>> C(m, vector<long long>(m, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                long long sum = 0;
                for (int k = 0; k < m; k++) {
                    sum = (sum + A[i][k] * B[k][j]) % mod;
                }
                C[i][j] = sum;
            }
        }
        return C;
    }

    vector<vector<long long>> matrixPower(vector<vector<long long>> base,
                                          long long e, int m) {
        vector<vector<long long>> res(m, vector<long long>(m, 0));

        for (int i = 0; i < m; i++)
            res[i][i] = 1;

        while (e > 0) {
            if (e & 1)
                res = mul(res, base);

            base = mul(base, base);
            e >>= 1;
        }

        return res;
    }

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        vector<vector<long long>> T(m, vector<long long>(m, 0));

        for (int j = 0; j < m; j++) {
            for (int i = m - j; i < m; i++) {
                T[i][j] = 1;
            }
        }

        vector<vector<long long>> powT = matrixPower(T, n - 1, m);

        long long total = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                total = (total + powT[i][j]) % mod;
            }
        }

        return (int)((total * 2LL) % mod);
    }
};