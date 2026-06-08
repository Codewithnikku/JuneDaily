#include <iostream>
#include <vector>
using namespace std;

class LeftRightSUmDifferences {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        vector<int> ans(nums.size());

        int rightSum = 0;
        for (int num : nums) {
            rightSum += num;
        }

        int leftSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            rightSum -= nums[i];
            ans[i] = abs(leftSum - rightSum);
            leftSum += nums[i];
        }

        return ans;
    }
};

int main() {
    vector<int> nums = {10, 4, 8, 3};

    LeftRightSUmDifferences lrsd;
    vector<int> result = lrsd.leftRightDifference(nums);

    for (int x : result) {
        cout << x << " ";
    }

    return 0;
}