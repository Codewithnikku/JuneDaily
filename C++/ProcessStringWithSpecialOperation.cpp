#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class ProcessStringWithSpecialOperation {
public:
    string processStr(string s) {
        string result;

        for (char ch : s) {
            if (ch >= 'a' && ch <= 'z') {
                result.push_back(ch);
            }
            else if (ch == '*') {
                if (!result.empty())
                    result.pop_back();
            }
            else if (ch == '#') {
                result += result;
            }
            else if (ch == '%') {
                reverse(result.begin(), result.end());
            }
        }

        return result;
    }
};

int main() {
    ProcessStringWithSpecialOperation sol;

    string s = "a#b%*";

    cout << "Input: " << s << endl;
    cout << "Output: " << sol.processStr(s) << endl;

    return 0;
}