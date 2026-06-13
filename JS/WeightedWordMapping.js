var mapWordWeights = function(words, weights) {
    let result = "";

    for (const word of words) {
        let sum = 0;

        for (const ch of word) {
            sum += weights[ch.charCodeAt(0) - 'a'.charCodeAt(0)];
        }

        sum %= 26;
        result += String.fromCharCode('z'.charCodeAt(0) - sum);
    }

    return result;
};