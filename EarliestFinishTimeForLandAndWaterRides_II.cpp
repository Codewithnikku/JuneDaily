#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class EarliestFinishTimeForLandAndWaterRides_II {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        auto solve = [&](vector<int>& s1, vector<int>& d1,
                         vector<int>& s2, vector<int>& d2) {
            int m = s2.size();
            vector<pair<int,int>> rides(m);
            for (int i = 0; i < m; i++) rides[i] = {s2[i], d2[i]};
            sort(rides.begin(), rides.end());

            vector<int> starts(m);
            vector<long long> prefMinDur(m), suffMinFinish(m);

            for (int i = 0; i < m; i++) starts[i] = rides[i].first;

            for (int i = 0; i < m; i++) {
                prefMinDur[i] = rides[i].second;
                if (i) prefMinDur[i] = min(prefMinDur[i], prefMinDur[i - 1]);
            }

            for (int i = m - 1; i >= 0; i--) {
                suffMinFinish[i] = 1LL * rides[i].first + rides[i].second;
                if (i + 1 < m) suffMinFinish[i] = min(suffMinFinish[i], suffMinFinish[i + 1]);
            }

            long long ans = LLONG_MAX;

            for (int i = 0; i < (int)s1.size(); i++) {
                long long t = 1LL * s1[i] + d1[i];
                int pos = upper_bound(starts.begin(), starts.end(), t) - starts.begin();

                if (pos > 0)
                    ans = min(ans, t + prefMinDur[pos - 1]);

                if (pos < m)
                    ans = min(ans, suffMinFinish[pos]);
            }

            return ans;
        };

        long long ans = min(
            solve(landStartTime, landDuration, waterStartTime, waterDuration),
            solve(waterStartTime, waterDuration, landStartTime, landDuration)
        );

        return (int)ans;
    }
};

int main() {
    EarliestFinishTimeForLandAndWaterRides_II eftlwr;
    vector<int> landStartTime = {1, 3, 5};
    vector<int> landDuration = {2, 2, 2};
    vector<int> waterStartTime = {2, 4, 6};
    vector<int> waterDuration = {1, 1, 1};
    cout << eftlwr.earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration) << endl;
    return 0;
}