var zigZagArrays = function(n, l, r) {
    const MOD = 1000000007n;
    const m = r - l + 1;

    const T = Array.from({ length: m }, (_, i) =>
        Array.from({ length: m }, (_, j) => i >= m - j ? 1n : 0n)
    );

    const mul = (A, B) => {
        const C = Array.from({ length: m }, () => Array(m).fill(0n));
        for (let i = 0; i < m; i++) {
            for (let k = 0; k < m; k++) {
                if (A[i][k] === 0n) continue;
                for (let j = 0; j < m; j++) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    };

    const mpow = (base, exp) => {
        let res = Array.from({ length: m }, (_, i) =>
            Array.from({ length: m }, (_, j) => i === j ? 1n : 0n)
        );

        while (exp > 0) {
            if (exp & 1) res = mul(res, base);
            base = mul(base, base);
            exp >>= 1;
        }
        return res;
    };

    const P = mpow(T, n - 1);

    let ans = 0n;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < m; j++) {
            ans = (ans + P[i][j]) % MOD;
        }
    }

    return Number((ans * 2n) % MOD);
};