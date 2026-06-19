#include <stdio.h>
#include <math.h>

double angleClock(int hour, int minutes) {
    double hourDegree = (hour % 12) * 30 + 0.5 * minutes;
    double minuteDegree = minutes * 6;

    double diff = fabs(hourDegree - minuteDegree);
    return fmin(diff, 360 - diff);
}

int main() {
    int hour, minutes;

    printf("Enter hour and minutes: ");
    scanf("%d %d", &hour, &minutes);

    printf("Angle: %.1f\n", angleClock(hour, minutes));

    return 0;
}