#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        string result;

        for (string& word : words) {
            int sum = 0;

            for (char ch : word) {
                sum += weights[ch - 'a'];
            }

            sum %= 26;
            result.push_back('z' - sum);
        }

        return result;
    }
};

int main(){
    
    return 0;
}