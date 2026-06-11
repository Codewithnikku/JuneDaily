/**
 * @param {number[][]} edges
 * @return {number}
 */
var assignEdgeWeights = function(edges) {
    const MOD = 1000000007n;
    const n = edges.length + 1;

    const graph = Array.from({ length: n + 1 }, () => []);

    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }

    let maxDepth = 0;
    const stack = [[1, 0, 0]]; // node, parent, depth

    while (stack.length) {
        const [u, parent, depth] = stack.pop();
        maxDepth = Math.max(maxDepth, depth);

        for (const v of graph[u]) {
            if (v !== parent) {
                stack.push([v, u, depth + 1]);
            }
        }
    }

    if (maxDepth === 0) return 0;

    let base = 2n;
    let exp = BigInt(maxDepth - 1);
    let result = 1n;

    while (exp > 0n) {
        if (exp & 1n) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1n;
    }

    return Number(result);
};