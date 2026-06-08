#include <iostream>
#include <string>
using namespace std;

class TotalWavinessofNumbersInRange_I {
public:
    int totalWaviness(int num1, int num2) {
        int total = 0;
        for (int n = num1; n <= num2; n++) {
            string s = to_string(n);
            int len = s.size();
            for (int i = 1; i < len - 1; i++) {
                if ((s[i] > s[i-1] && s[i] > s[i+1]) ||
                    (s[i] < s[i-1] && s[i] < s[i+1]))
                    total++;
            }
        }
        return total;
    }
};

int main() {
    TotalWavinessofNumbersInRange_I solution;
    int num1 = 120, num2 = 130;
    int result = solution.totalWaviness(num1, num2);
    cout << "Total Waviness: " << result << endl;
    return 0;
}