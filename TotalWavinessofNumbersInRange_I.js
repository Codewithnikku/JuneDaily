var totalWaviness = function(num1, num2) {
    let total = 0;
    for (let n = num1; n <= num2; n++) {
        const s = String(n);
        for (let i = 1; i < s.length - 1; i++) {
            if ((s[i] > s[i-1] && s[i] > s[i+1]) ||
                (s[i] < s[i-1] && s[i] < s[i+1]))
                total++;
        }
    }
    return total;
};

const num1 = 120
const num2 = 130
const result = totalWaviness(num1, num2);
console.log("Total Waviness:", result);