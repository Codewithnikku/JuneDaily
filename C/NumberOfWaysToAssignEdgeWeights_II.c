#define MOD 1000000007LL

int depth[100005];
int lift[100005][18];
int *adj[100005];
int deg[100005];
int idx[100005];

long long power(long long base, int exp) {
    long long res = 1;
    base %= MOD;

    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }

    return res;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int t = u;
        u = v;
        v = t;
    }

    int diff = depth[u] - depth[v];

    for (int j = 17; j >= 0; --j) {
        if ((diff >> j) & 1) u = lift[u][j];
    }

    if (u == v) return u;

    for (int j = 17; j >= 0; --j) {
        if (lift[u][j] != lift[v][j]) {
            u = lift[u][j];
            v = lift[v][j];
        }
    }

    return lift[u][0];
}

int* assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize,
                       int** queries, int queriesSize, int* queriesColSize,
                       int* returnSize) {
    int n = edgesSize + 1;

    for (int i = 0; i <= n; ++i) {
        deg[i] = 0;
        depth[i] = 0;
        for (int j = 0; j < 18; ++j) lift[i][j] = 1;
    }

    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        deg[u]++;
        deg[v]++;
    }

    for (int i = 1; i <= n; ++i) {
        adj[i] = (int*)malloc(deg[i] * sizeof(int));
        idx[i] = 0;
    }

    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][idx[u]++] = v;
        adj[v][idx[v]++] = u;
    }

    int *q = (int*)malloc((n + 5) * sizeof(int));
    bool *vis = (bool*)calloc(n + 1, sizeof(bool));

    int front = 0, back = 0;
    q[back++] = 1;
    vis[1] = true;

    while (front < back) {
        int cur = q[front++];

        for (int i = 0; i < deg[cur]; ++i) {
            int nxt = adj[cur][i];

            if (vis[nxt]) continue;

            vis[nxt] = true;
            depth[nxt] = depth[cur] + 1;
            lift[nxt][0] = cur;
            q[back++] = nxt;
        }
    }

    for (int j = 1; j < 18; ++j) {
        for (int i = 1; i <= n; ++i) {
            lift[i][j] = lift[lift[i][j - 1]][j - 1];
        }
    }

    int *ans = (int*)malloc(queriesSize * sizeof(int));

    for (int i = 0; i < queriesSize; ++i) {
        int u = queries[i][0];
        int v = queries[i][1];

        int p = lca(u, v);
        int dist = depth[u] + depth[v] - 2 * depth[p];

        ans[i] = dist == 0 ? 0 : (int)power(2, dist - 1);
    }

    *returnSize = queriesSize;

    free(q);
    free(vis);

    for (int i = 1; i <= n; ++i) free(adj[i]);

    return ans;
}