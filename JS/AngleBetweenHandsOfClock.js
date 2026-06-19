var angleClock = function(hour, minutes) {
    let hourDegree = (hour % 12) * 30 + 0.5 * minutes;
    let minuteDegree = minutes * 6;

    let diff = Math.abs(hourDegree - minuteDegree);
    return Math.min(diff, 360 - diff);
};

console.log(angleClock(3, 15)); 
console.log(angleClock(12, 30));
console.log(angleClock(1, 57)); 