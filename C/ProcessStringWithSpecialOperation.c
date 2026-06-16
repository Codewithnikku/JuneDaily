#include <stdlib.h>
#include <string.h>

char* processStr(char* s) {
    int capacity = 100000;
    char* result = (char*)malloc(capacity * sizeof(char));
    int len = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        char ch = s[i];

        if (ch >= 'a' && ch <= 'z') {
            result[len++] = ch;
        }
        else if (ch == '*') {
            if (len > 0) {
                len--;
            }
        }
        else if (ch == '#') {
            for (int j = 0; j < len; j++) {
                result[len + j] = result[j];
            }
            len *= 2;
        }
        else if (ch == '%') {
            int left = 0, right = len - 1;
            while (left < right) {
                char temp = result[left];
                result[left] = result[right];
                result[right] = temp;
                left++;
                right--;
            }
        }
    }

    result[len] = '\0';
    return result;
}