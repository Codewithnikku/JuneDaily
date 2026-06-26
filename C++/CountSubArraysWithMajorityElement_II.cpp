#include <vector>
using namespace std;

class CountSubArraysWithMajorityElement_II {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        int len = 2 * n + 2;

        vector<long long> countAtSum(len, 0);
        vector<long long> comulativeCount(len, 0);

        int idx = n + 1;
        countAtSum[idx] = 1;
        comulativeCount[idx] = 1;

        long long ans = 0;

        for (int num : nums) {
            if (num == target)
                idx++;
            else
                idx--;

            countAtSum[idx]++;
            ans += comulativeCount[idx - 1];
            comulativeCount[idx] = comulativeCount[idx - 1] + countAtSum[idx];
        }

        return ans;
    }
};