int maxNumberOfBalloons(char* text) {
    int freq[26] = {0};

    for (int i = 0; text[i] != '\0'; i++) {
        freq[text[i] - 'a']++;
    }

    int min = freq['b' - 'a'];

    if (freq['a' - 'a'] < min) min = freq['a' - 'a'];
    if (freq['n' - 'a'] < min) min = freq['n' - 'a'];
    if (freq['l' - 'a'] / 2 < min) min = freq['l' - 'a'] / 2;
    if (freq['o' - 'a'] / 2 < min) min = freq['o' - 'a'] / 2;

    return min;
}