#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MinimumCostOfBuyingCanddatesWithDiscount {
public:
    int minimumCost(vector<int>& cost) {
        sort(cost.begin(), cost.end(), greater<int>());
        int ans = 0;
        for (int i = 0; i < cost.size(); i++) {
            if (i % 3 != 2) ans += cost[i];
        }
        return ans;
    }
};



int main(){
    MinimumCostOfBuyingCanddatesWithDiscount mbcwd;
    vector<int> cost = {1, 2, 3};
    cout << mbcwd.minimumCost(cost) << endl;
    return 0;
}