#include <stdio.h>
#include <string.h>

int totalWaviness(int num1, int num2) {
    int total = 0;
    for (int n = num1; n <= num2; n++) {
        char s[7];
        sprintf(s, "%d", n);
        int len = strlen(s);
        for (int i = 1; i < len - 1; i++) {
            if ((s[i] > s[i-1] && s[i] > s[i+1]) ||
                (s[i] < s[i-1] && s[i] < s[i+1]))
                total++;
        }
    }
    return total;
}

int main() {
    int num1 = 120, num2 = 130;
    int result = totalWaviness(num1, num2);
    printf("Total Waviness: %d\n", result);
    return 0;
}