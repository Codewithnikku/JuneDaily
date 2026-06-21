#include <vector>
#include <algorithm>
using namespace std;

class MaximumBuildingHeight {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        sort(restrictions.begin(), restrictions.end());

        int len = restrictions.size();

        if (len == 0) {
            return n - 1;
        }

        bool isLast = restrictions[len - 1][0] == n;

        int m = len + 1 + (isLast ? 0 : 1);

        vector<vector<int>> h(m, vector<int>(2));

        h[0][0] = 1;
        h[0][1] = 0;

        for (int i = 0; i < len; i++) {
            int diff = restrictions[i][0] - h[i][0];
            int ht = h[i][1] + diff;

            h[i + 1][0] = restrictions[i][0];
            h[i + 1][1] = min(ht, restrictions[i][1]);
        }

        if (!isLast) {
            int diff = n - h[len][0];
            int ht = h[len][1] + diff;

            h[len + 1][0] = n;
            h[len + 1][1] = min(ht, n - 1);
        }

        for (int i = m - 2; i >= 0; i--) {
            int diff = h[i + 1][0] - h[i][0];
            int ht = h[i + 1][1] + diff;

            h[i][1] = min(h[i][1], ht);
        }

        int ans = 0;

        for (int i = 1; i < m; i++) {
            int left = h[i - 1][0];
            int right = h[i][0];

            int h1 = h[i - 1][1];
            int h2 = h[i][1];

            int dist = right - left;

            int peak = (dist + h1 + h2) / 2;

            ans = max(ans, peak);
        }

        return ans;
    }
};