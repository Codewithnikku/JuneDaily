#include<vector>
#include<algorithm>
using namespace std;

class FindTheHighestAltitude {
public:
    int largestAltitude(vector<int>& gain) {
        int Max=0;
        int curr=0;
        for(int g : gain) {
            curr+=g;
            Max = max(curr, Max);
        }

        return Max;
    }
};