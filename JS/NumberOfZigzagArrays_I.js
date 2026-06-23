var zigZagArrays = function(n, l, r) {
    const MOD = 1000000007;
    const m = r - l + 1;
    let up = new Array(m).fill(1);
    let down = new Array(m).fill(1);
    let pre = new Array(m + 1).fill(0);
    let suf = new Array(m + 1).fill(0);
    let newUp = new Array(m);
    let newDown = new Array(m);

    for (let len = 2; len <= n; len++) {
        pre[0] = 0;
        suf[m] = 0;
        for (let i = 0; i < m; i++) { pre[i + 1] = (pre[i] + down[i]) % MOD; }
        for (let i = m - 1; i >= 0; i--) { suf[i] = (suf[i + 1] + up[i]) % MOD; }
        for (let i = 0; i < m; i++) { newUp[i] = pre[i]; newDown[i] = suf[i + 1]; }
        [up, newUp] = [newUp, up];
        [down, newDown] = [newDown, down];
    }

    let ans = 0;
    for (let i = 0; i < m; i++) { ans = (ans + up[i] + down[i]) % MOD; }
    return ans;
};