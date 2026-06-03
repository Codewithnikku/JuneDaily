/**
 * @param {number[]} landStartTime
 * @param {number[]} landDuration
 * @param {number[]} waterStartTime
 * @param {number[]} waterDuration
 * @return {number}
 */
var earliestFinishTime = function(landStartTime, landDuration, waterStartTime, waterDuration) {

    function solve(s1, d1, s2, d2) {
        const m = s2.length;

        const rides = new Array(m);
        for (let i = 0; i < m; i++) {
            rides[i] = [s2[i], d2[i]];
        }

        rides.sort((a, b) => a[0] - b[0]);

        const starts = new Int32Array(m);
        const pref = new Int32Array(m);
        const suff = new Int32Array(m);

        starts[0] = rides[0][0];
        pref[0] = rides[0][1];

        for (let i = 1; i < m; i++) {
            starts[i] = rides[i][0];
            const d = rides[i][1];
            pref[i] = d < pref[i - 1] ? d : pref[i - 1];
        }

        suff[m - 1] = rides[m - 1][0] + rides[m - 1][1];

        for (let i = m - 2; i >= 0; i--) {
            const v = rides[i][0] + rides[i][1];
            suff[i] = v < suff[i + 1] ? v : suff[i + 1];
        }

        let ans = Number.MAX_SAFE_INTEGER;

        for (let i = 0, n = s1.length; i < n; i++) {
            const t = s1[i] + d1[i];

            let l = 0, r = m;
            while (l < r) {
                const mid = (l + r) >>> 1;
                if (starts[mid] <= t) l = mid + 1;
                else r = mid;
            }

            if (l) {
                const v = t + pref[l - 1];
                if (v < ans) ans = v;
            }

            if (l < m && suff[l] < ans) {
                ans = suff[l];
            }
        }

        return ans;
    }

    const a = solve(
        landStartTime,
        landDuration,
        waterStartTime,
        waterDuration
    );

    const b = solve(
        waterStartTime,
        waterDuration,
        landStartTime,
        landDuration
    );

    return a < b ? a : b;
};

const LandStartTime = [1, 2, 3];
const LandDuration = [2, 3, 1];
const WaterStartTime = [2, 3, 4];
const WaterDuration = [1, 2, 3];
console.log(earliestFinishTime(LandStartTime, LandDuration, WaterStartTime, WaterDuration));