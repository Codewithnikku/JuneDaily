#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class EarliestFinishTimeForLandAndWaterRides_I {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        long long ans = LLONG_MAX;

        int m = waterStartTime.size();
        vector<pair<int, int>> water(m);
        for (int i = 0; i < m; i++) water[i] = {waterStartTime[i], waterDuration[i]};
        sort(water.begin(), water.end());

        vector<int> wStart(m);
        vector<long long> wPref(m), wSuff(m);

        for (int i = 0; i < m; i++) {
            wStart[i] = water[i].first;
            wPref[i] = water[i].second;
            if (i) wPref[i] = min(wPref[i], wPref[i - 1]);
        }

        for (int i = m - 1; i >= 0; i--) {
            wSuff[i] = 1LL * water[i].first + water[i].second;
            if (i + 1 < m) wSuff[i] = min(wSuff[i], wSuff[i + 1]);
        }

        for (int i = 0; i < (int)landStartTime.size(); i++) {
            long long x = 1LL * landStartTime[i] + landDuration[i];
            int p = upper_bound(wStart.begin(), wStart.end(), x) - wStart.begin() - 1;

            long long cur = LLONG_MAX;
            if (p >= 0) cur = min(cur, x + wPref[p]);
            if (p + 1 < m) cur = min(cur, wSuff[p + 1]);

            ans = min(ans, cur);
        }

        int n = landStartTime.size();
        vector<pair<int, int>> land(n);
        for (int i = 0; i < n; i++) land[i] = {landStartTime[i], landDuration[i]};
        sort(land.begin(), land.end());

        vector<int> lStart(n);
        vector<long long> lPref(n), lSuff(n);

        for (int i = 0; i < n; i++) {
            lStart[i] = land[i].first;
            lPref[i] = land[i].second;
            if (i) lPref[i] = min(lPref[i], lPref[i - 1]);
        }

        for (int i = n - 1; i >= 0; i--) {
            lSuff[i] = 1LL * land[i].first + land[i].second;
            if (i + 1 < n) lSuff[i] = min(lSuff[i], lSuff[i + 1]);
        }

        for (int j = 0; j < (int)waterStartTime.size(); j++) {
            long long x = 1LL * waterStartTime[j] + waterDuration[j];
            int p = upper_bound(lStart.begin(), lStart.end(), x) - lStart.begin() - 1;

            long long cur = LLONG_MAX;
            if (p >= 0) cur = min(cur, x + lPref[p]);
            if (p + 1 < n) cur = min(cur, lSuff[p + 1]);

            ans = min(ans, cur);
        }

        return (int)ans;
    }
};

int main(){
    EarliestFinishTimeForLandAndWaterRides_I eftflwr;
    vector<int> landStartTime = {1, 4, 6};
    vector<int> landDuration = {2, 3, 1};
    vector<int> waterStartTime = {2, 5};
    vector<int> waterDuration = {3, 2};
    cout << eftflwr.earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration) << endl;
    return 0;
}