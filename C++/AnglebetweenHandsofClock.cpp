#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

class AnglebetweenClockHands {
public:
    double angleClock(int hour, int minutes) {
        double hourDegree = (hour%12)*30 + (0.5)*minutes;
        double minuteDegree = (minutes)*6;
        double diff = abs(hourDegree - minuteDegree);
        return min(diff, 360-diff);
    }
};

int main() {
    AnglebetweenClockHands sol;

    int hour, minutes;
    cout << "Enter hour and minutes: ";
    cin >> hour >> minutes;

    cout << "Angle: " << sol.angleClock(hour, minutes) << endl;

    return 0;
}