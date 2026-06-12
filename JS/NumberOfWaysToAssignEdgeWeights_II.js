/**
 * @param {number[][]} edges
 * @param {number[][]} queries
 * @return {number[]}
 */
var assignEdgeWeights = function(edges, queries) {
    const MOD = 1000000007;
    const n = edges.length + 1;
    const adj = Array.from({ length: n + 1 }, () => []);
    const depth = Array(n + 1).fill(0);
    const lift = Array.from({ length: n + 1 }, () => Array(18).fill(1));

    for (const [u, v] of edges) {
        adj[u].push(v);
        adj[v].push(u);
    }

    const vis = Array(n + 1).fill(false);
    const q = [1];
    vis[1] = true;

    for (let i = 0; i < q.length; i++) {
        const cur = q[i];
        for (const nxt of adj[cur]) {
            if (vis[nxt]) continue;
            vis[nxt] = true;
            depth[nxt] = depth[cur] + 1;
            lift[nxt][0] = cur;
            q.push(nxt);
        }
    }

    for (let j = 1; j < 18; j++) {
        for (let i = 1; i <= n; i++) {
            lift[i][j] = lift[lift[i][j - 1]][j - 1];
        }
    }

    const lca = (u, v) => {
        if (depth[u] < depth[v]) [u, v] = [v, u];
        let diff = depth[u] - depth[v];

        for (let j = 17; j >= 0; j--) {
            if ((diff >> j) & 1) u = lift[u][j];
        }

        if (u === v) return u;

        for (let j = 17; j >= 0; j--) {
            if (lift[u][j] !== lift[v][j]) {
                u = lift[u][j];
                v = lift[v][j];
            }
        }

        return lift[u][0];
    };

    const power = (b, e) => {
        let res = 1n, base = BigInt(b);
        while (e > 0) {
            if (e & 1) res = res * base % BigInt(MOD);
            base = base * base % BigInt(MOD);
            e >>= 1;
        }
        return Number(res);
    };

    return queries.map(([u, v]) => {
        const p = lca(u, v);
        const dist = depth[u] + depth[v] - 2 * depth[p];
        return dist === 0 ? 0 : power(2, dist - 1);
    });
};