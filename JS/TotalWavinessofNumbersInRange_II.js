var totalWaviness = function (num1, num2) {
  const solve = (n) => {
    if (n < 0) return 0;

    const s = n.toString();
    const memo = new Map();

    const dfs = (pos, started, len, a, b, tight) => {
      if (pos === s.length) {
        return [1n, 0n];
      }

      const key = `${pos},${started},${len},${a},${b}`;

      if (!tight && memo.has(key)) {
        return memo.get(key);
      }

      const limit = tight ? Number(s[pos]) : 9;

      let totalCnt = 0n;
      let totalWav = 0n;

      for (let d = 0; d <= limit; d++) {
        const nextTight = tight && d === limit;

        if (!started && d === 0) {
          const [cnt, wav] = dfs(pos + 1, false, 0, 10, 10, nextTight);
          totalCnt += cnt;
          totalWav += wav;
        } else {
          if (!started) {
            const [cnt, wav] = dfs(pos + 1, true, 1, 10, d, nextTight);
            totalCnt += cnt;
            totalWav += wav;
          } else if (len === 1) {
            const [cnt, wav] = dfs(pos + 1, true, 2, b, d, nextTight);
            totalCnt += cnt;
            totalWav += wav;
          } else {
            const add = (b > a && b > d) || (b < a && b < d) ? 1n : 0n;

            const [cnt, wav] = dfs(pos + 1, true, 2, b, d, nextTight);

            totalCnt += cnt;
            totalWav += wav + cnt * add;
          }
        }
      }

      const res = [totalCnt, totalWav];

      if (!tight) {
        memo.set(key, res);
      }

      return res;
    };

    return dfs(0, false, 0, 10, 10, true)[1];
  };

  return Number(solve(num2) - solve(num1 - 1));
};

const num1 = 120;
const num2 = 130;
console.log(totalWaviness(num1, num2));