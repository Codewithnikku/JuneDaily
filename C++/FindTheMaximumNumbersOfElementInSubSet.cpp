#include <bits/stdc++.h>
using namespace std;

class FindTheMaximumNumbersOfElementInSubSet {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> freq;
        for (int num : nums) {
            freq[(long long)num]++;
        }

        int ans = 0;
        if (freq.count(1LL)) {
            int ones = freq[1LL];
            ans = (ones % 2 == 0) ? ones - 1 : ones;
            freq.erase(1LL);
        }

        unordered_map<long long, int> memo;
        for (auto &p : freq) {
            ans = max(ans, dfs(p.first, freq, memo));
        }
        return ans;
    }

private:
    int dfs(long long num, unordered_map<long long,int>& freq, unordered_map<long long,int>& memo) {
        if (!freq.count(num)) return 0;
        if (memo.count(num)) return memo[num];

        int count;
        if (freq[num] >= 2) {
            count = 2 + dfs(num * num, freq, memo);
        } else {
            count = 1;
        }

        if (count % 2 == 0) count--; 
        memo[num] = count;
        return count;
    }
};
