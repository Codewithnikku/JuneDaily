class MaximumIceCreamBars {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        vector<int> count(100001, 0);

        for (int cost : costs) {
            count[cost]++;
        }

        int ans = 0;

        for (int i = 1; i < count.size(); i++) {
            while (count[i] > 0 && coins >= i) {
                ans++;
                count[i]--;
                coins -= i;
            }
        }

        return ans;
    }
};