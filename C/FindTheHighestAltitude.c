#include <math.h>

int largestAltitude(int* gain, int gainSize) {
    int maxAltitude = 0;
    int curr = 0;

    for (int i = 0; i < gainSize; i++) {
        curr += gain[i];
        maxAltitude = (int)fmax(curr, maxAltitude);
    }

    return maxAltitude;
}