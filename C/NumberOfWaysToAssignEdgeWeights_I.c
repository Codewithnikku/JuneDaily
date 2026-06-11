#define MOD 1000000007LL

long long modPow(long long base, long long exp) {
    long long res = 1;

    while (exp > 0) {
        if (exp & 1)
            res = (res * base) % MOD;

        base = (base * base) % MOD;
        exp >>= 1;
    }

    return res;
}

int assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize) {
    int n = edgesSize + 1;

    int *deg = (int *)calloc(n + 1, sizeof(int));

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        deg[u]++;
        deg[v]++;
    }

    int **graph = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 1; i <= n; i++) {
        graph[i] = (int *)malloc(deg[i] * sizeof(int));
        deg[i] = 0;
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        graph[u][deg[u]++] = v;
        graph[v][deg[v]++] = u;
    }

    int *stackNode = (int *)malloc((n + 1) * sizeof(int));
    int *stackParent = (int *)malloc((n + 1) * sizeof(int));
    int *stackDepth = (int *)malloc((n + 1) * sizeof(int));

    int top = 0;
    stackNode[top] = 1;
    stackParent[top] = 0;
    stackDepth[top] = 0;
    top++;

    int maxDepth = 0;

    while (top) {
        top--;

        int u = stackNode[top];
        int parent = stackParent[top];
        int depth = stackDepth[top];

        if (depth > maxDepth)
            maxDepth = depth;

        for (int i = 0; i < deg[u]; i++) {
            int v = graph[u][i];

            if (v != parent) {
                stackNode[top] = v;
                stackParent[top] = u;
                stackDepth[top] = depth + 1;
                top++;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        free(graph[i]);

    free(graph);
    free(deg);
    free(stackNode);
    free(stackParent);
    free(stackDepth);

    if (maxDepth == 0)
        return 0;

    return (int)modPow(2, maxDepth - 1);
}