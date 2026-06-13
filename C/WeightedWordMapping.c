#include <stdlib.h>
#include <string.h>

char *mapWordWeights(char **words, int wordsSize, int *weights, int weightsSize)
{
    char *result = (char *)malloc((wordsSize + 1) * sizeof(char));

    for (int i = 0; i < wordsSize; i++)
    {
        int sum = 0;

        for (int j = 0; words[i][j] != '\0'; j++)
        {
            sum += weights[words[i][j] - 'a'];
        }

        sum %= 26;
        result[i] = 'z' - sum;
    }

    result[wordsSize] = '\0';
    return result;
}