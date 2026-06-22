var maxNumberOfBalloons = function(text) {
    let freq = new Array(26).fill(0);

    for (let ch of text) {
        freq[ch.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }

    let mn = freq['b'.charCodeAt(0) - 'a'.charCodeAt(0)];
    mn = Math.min(mn, freq['a'.charCodeAt(0) - 'a'.charCodeAt(0)]);
    mn = Math.min(mn, freq['n'.charCodeAt(0) - 'a'.charCodeAt(0)]);
    mn = Math.min(mn, Math.floor(freq['l'.charCodeAt(0) - 'a'.charCodeAt(0)] / 2));
    mn = Math.min(mn, Math.floor(freq['o'.charCodeAt(0) - 'a'.charCodeAt(0)] / 2));

    return mn;
};