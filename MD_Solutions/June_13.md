# Intuition

Each word contributes to a single encoded character based on the cumulative weight of its letters.

For a given word:

1. Calculate the sum of the weights of all characters in the word.
2. Reduce the sum using modulo `26` to keep the value within the English alphabet range.
3. Map the resulting value to a character by counting backward from `'z'`.

By repeating this process for every word and concatenating the generated characters, we obtain the final encoded string.

---

# Approach

1. Initialize an empty result string.
2. Iterate through each word in the `words` array.
3. For the current word:
   - Traverse all characters.
   - Use the character's position (`ch - 'a'`) to retrieve its corresponding weight from the `weights` array.
   - Accumulate these weights into a running sum.
4. Compute `sum % 26`.
5. Convert the value into a character using:
   
   ```text
   mappedCharacter = 'z' - (sum % 26)
   ```

6. Append the mapped character to the result.
7. Return the final result string after processing all words.

---

# Example

Suppose:

```text
words = ["abc", "de"]
weights = [1,2,3,4,5,...]
```

For `"abc"`:

```text
weight = 1 + 2 + 3 = 6
6 % 26 = 6
mapped character = 'z' - 6 = 't'
```

For `"de"`:

```text
weight = 4 + 5 = 9
9 % 26 = 9
mapped character = 'z' - 9 = 'q'
```

Final result:

```text
"tq"
```

---

# Complexity Analysis

Let:

- `n` = number of words
- `L` = total number of characters across all words

### Time Complexity

```text
O(L)
```

Each character is visited exactly once while computing the weight sum.

### Space Complexity

```text
O(n)
```

The output string stores one character for each word.

---

# Code

```cpp []
class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        string result;
        
        for (const string& word : words) {
            int sum = 0;
            
            for (char ch : word) {
                sum += weights[ch - 'a'];
            }
            
            int mod = sum % 26;
            char mapped = 'z' - mod;
            result.push_back(mapped);
        }
        
        return result;
    }
};
```
```java []
class Solution {
    public String mapWordWeights(String[] words, int[] weights) {
        StringBuilder sb = new StringBuilder();

        for (String word : words) {
            int sum = 0;

            for (char ch : word.toCharArray()) {
                sum += weights[ch - 'a'];
            }

            sum %= 26;
            sb.append((char) ('z' - sum));
        }

        return sb.toString();
    }
}
```
```python []
class Solution(object):
    def mapWordWeights(self, words, weights):
        result = []

        for word in words:
            total = 0

            for ch in word:
                total += weights[ord(ch) - ord('a')]

            total %= 26
            result.append(chr(ord('z') - total))

        return ''.join(result)
```
```javascript []
var mapWordWeights = function(words, weights) {
    let result = "";

    for (const word of words) {
        let sum = 0;

        for (const ch of word) {
            sum += weights[ch.charCodeAt(0) - 'a'.charCodeAt(0)];
        }

        sum %= 26;
        result += String.fromCharCode(
            'z'.charCodeAt(0) - sum
        );
    }

    return result;
};
```
```c []
char* mapWordWeights(char** words, int wordsSize,
                     int* weights, int weightsSize) {
    char* result = (char*)malloc((wordsSize + 1) * sizeof(char));

    for (int i = 0; i < wordsSize; i++) {
        int sum = 0;

        for (int j = 0; words[i][j] != '\0'; j++) {
            sum += weights[words[i][j] - 'a'];
        }

        sum %= 26;
        result[i] = 'z' - sum;
    }

    result[wordsSize] = '\0';
    return result;
}
```
# Key Observations

- Each word is transformed independently into exactly one character.
- The contribution of a word depends only on the **sum of its character weights**.
- Since the final mapping is based on the English alphabet, only the value of `sum % 26` matters.
- Characters are mapped in reverse alphabetical order using:

  ```text
  mappedCharacter = 'z' - (sum % 26)
  ```

- There is no need for additional data structures such as hash maps, sets, or prefix arrays. A simple traversal is sufficient.

---

# Techniques Used

### 1. Character Index Mapping

Each lowercase letter is converted into an index in the range `[0, 25]`.

```cpp
ch - 'a'
```

Example:

```text
'a' -> 0
'b' -> 1
'c' -> 2
...
'z' -> 25
```

This allows direct access to the corresponding weight.

---

### 2. Accumulation Pattern

For every word, we compute the total weight by accumulating the weight of each character.

```cpp
sum += weights[ch - 'a'];
```

This is a common technique used in string-processing problems.

---

### 3. Modular Arithmetic

Since there are only 26 lowercase letters, the accumulated weight is reduced using modulo.

```cpp
sum %= 26;
```

This keeps the value within the alphabet range and prevents unnecessary growth of the sum.

---

### 4. Character Encoding

The modulo result is converted into the final character by moving backward from `'z'`.

```cpp
char mapped = 'z' - (sum % 26);
```

Examples:

```text
0  -> 'z'
1  -> 'y'
2  -> 'x'
...
25 -> 'a'
```

---

# Why This Solution Works

For every word:

1. We correctly compute the total weight using the provided weight mapping.
2. We reduce the value to a valid alphabet range using modulo `26`.
3. We apply the required reverse-alphabet transformation.
4. Each generated character is appended to the answer in the same order as the input words.

Therefore, the resulting string exactly represents the weighted mapping of all words.

---

# Pattern Recognition

This problem combines several fundamental concepts frequently seen in coding interviews:

- String Traversal
- Character-to-Index Conversion
- Frequency/Weight Accumulation
- Modular Arithmetic
- Character Encoding

Recognizing these patterns makes the implementation straightforward and efficient.

---

# Complexity Summary

| Metric | Complexity |
|----------|----------|
| Time Complexity | **O(L)** |
| Space Complexity | **O(n)** |

Where:

- `L` = Total number of characters across all words.
- `n` = Number of words.

The algorithm processes each character exactly once and stores one output character per word.

---

# Takeaway

Whenever a problem involves:

- Mapping characters to numeric values,
- Aggregating values across a string,
- Compressing the result into a fixed-size alphabet,

a combination of **array indexing**, **running sums**, and **modular arithmetic** often leads to an optimal linear-time solution.