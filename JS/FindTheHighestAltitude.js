var largestAltitude = function(gain) {
    let maxAltitude=0;
    let curr=0;
    for(let g of gain) {
        curr+=g;
        maxAltitude = Math.max(curr, max);
    }

    return maxAltitude;
};