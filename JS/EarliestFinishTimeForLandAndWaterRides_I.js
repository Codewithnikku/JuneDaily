/**
 * @param {number[]} landStartTime
 * @param {number[]} landDuration
 * @param {number[]} waterStartTime
 * @param {number[]} waterDuration
 * @return {number}
 */
var earliestFinishTime = function (
  landStartTime,
  landDuration,
  waterStartTime,
  waterDuration,
) {
  let ans = Infinity;

  const water = waterStartTime.map((s, i) => [s, waterDuration[i]]);
  water.sort((a, b) => a[0] - b[0]);

  const m = water.length;
  const wStart = new Array(m);
  const wPref = new Array(m);
  const wSuff = new Array(m);

  for (let i = 0; i < m; i++) {
    wStart[i] = water[i][0];
    wPref[i] = water[i][1];
    if (i) wPref[i] = Math.min(wPref[i], wPref[i - 1]);
  }

  for (let i = m - 1; i >= 0; i--) {
    wSuff[i] = water[i][0] + water[i][1];
    if (i + 1 < m) wSuff[i] = Math.min(wSuff[i], wSuff[i + 1]);
  }

  for (let i = 0; i < landStartTime.length; i++) {
    const x = landStartTime[i] + landDuration[i];
    let l = 0,
      r = m;

    while (l < r) {
      const mid = (l + r) >> 1;
      if (wStart[mid] <= x) l = mid + 1;
      else r = mid;
    }

    const p = l - 1;
    let cur = Infinity;

    if (p >= 0) cur = Math.min(cur, x + wPref[p]);
    if (p + 1 < m) cur = Math.min(cur, wSuff[p + 1]);

    ans = Math.min(ans, cur);
  }

  const land = landStartTime.map((s, i) => [s, landDuration[i]]);
  land.sort((a, b) => a[0] - b[0]);

  const n = land.length;
  const lStart = new Array(n);
  const lPref = new Array(n);
  const lSuff = new Array(n);

  for (let i = 0; i < n; i++) {
    lStart[i] = land[i][0];
    lPref[i] = land[i][1];
    if (i) lPref[i] = Math.min(lPref[i], lPref[i - 1]);
  }

  for (let i = n - 1; i >= 0; i--) {
    lSuff[i] = land[i][0] + land[i][1];
    if (i + 1 < n) lSuff[i] = Math.min(lSuff[i], lSuff[i + 1]);
  }

  for (let i = 0; i < waterStartTime.length; i++) {
    const x = waterStartTime[i] + waterDuration[i];
    let l = 0,
      r = n;

    while (l < r) {
      const mid = (l + r) >> 1;
      if (lStart[mid] <= x) l = mid + 1;
      else r = mid;
    }

    const p = l - 1;
    let cur = Infinity;

    if (p >= 0) cur = Math.min(cur, x + lPref[p]);
    if (p + 1 < n) cur = Math.min(cur, lSuff[p + 1]);

    ans = Math.min(ans, cur);
  }

  return ans;
};

const EFTFLWR = {
  LandStartTime: [1, 4, 6],
  LandDuration: [2, 3, 1],
  WaterStartTime: [2, 5],
  WaterDuration: [3, 2],
};

const EFLAWR_I = earliestFinishTime(
  EFTFLWR.LandStartTime,
  EFTFLWR.LandDuration,
  EFTFLWR.WaterStartTime,
  EFTFLWR.WaterDuration,
);

console.log(EFLAWR_I);
