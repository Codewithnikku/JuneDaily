#include<vector>
using namespace std;

class MaximumElementAfterDescendingAndRearranging {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int n = arr.size(); int ans = 1;
        vector<int> count(n + 1, 0);
        for (int a : arr) { int idx = min(a, n); count[idx]++; }
        for (int i = 2; i <= n; i++) { int curr = ans + count[i]; ans = min(i, curr); }
        return ans;
    }
};