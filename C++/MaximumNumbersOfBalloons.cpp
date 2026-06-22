#include<algorithm>
#include<string>
using namespace std;

class MaximumNumbersOfBalloons {
public:
    int maxNumberOfBalloons(string text) {
        int freq[26] = {0};

        for (char ch : text) {
            freq[ch - 'a']++;
        }

        int mn = freq['b' - 'a'];
        mn = min(mn, freq['a' - 'a']);
        mn = min(mn, freq['n' - 'a']);
        mn = min(mn, freq['l' - 'a'] / 2);
        mn = min(mn, freq['o' - 'a'] / 2);

        return mn;
    }
};