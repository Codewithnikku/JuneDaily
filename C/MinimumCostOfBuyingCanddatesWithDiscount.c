typedef struct {
    int **mn;
    int **mx;
    int levels;
    int n;
} SparseTable;

static int minInt(int a, int b) {
    return a < b ? a : b;
}

static int maxInt(int a, int b) {
    return a > b ? a : b;
}

static int log2Floor(int x) {
    int res = 0;
    while ((1 << (res + 1)) <= x) res++;
    return res;
}

SparseTable* createSparseTable(int* nums, int n) {
    SparseTable* st = (SparseTable*)malloc(sizeof(SparseTable));

    st->n = n;
    st->levels = 0;
    while ((1 << st->levels) <= n) st->levels++;

    st->mn = (int**)malloc(st->levels * sizeof(int*));
    st->mx = (int**)malloc(st->levels * sizeof(int*));

    for (int i = 0; i < st->levels; i++) {
        st->mn[i] = (int*)calloc(n, sizeof(int));
        st->mx[i] = (int*)calloc(n, sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        st->mn[0][i] = nums[i];
        st->mx[0][i] = nums[i];
    }

    for (int k = 1; k < st->levels; k++) {
        int half = 1 << (k - 1);
        int len = 1 << k;

        for (int j = 0; j + len <= n; j++) {
            st->mn[k][j] = minInt(
                st->mn[k - 1][j],
                st->mn[k - 1][j + half]
            );

            st->mx[k][j] = maxInt(
                st->mx[k - 1][j],
                st->mx[k - 1][j + half]
            );
        }
    }

    return st;
}

int query(SparseTable* st, int left, int right) {
    int len = right - left;
    if (len <= 0) return 0;

    int k = log2Floor(len);

    int mx = maxInt(
        st->mx[k][left],
        st->mx[k][right - (1 << k)]
    );

    int mn = minInt(
        st->mn[k][left],
        st->mn[k][right - (1 << k)]
    );

    return mx - mn;
}

void freeSparseTable(SparseTable* st) {
    for (int i = 0; i < st->levels; i++) {
        free(st->mn[i]);
        free(st->mx[i]);
    }
    free(st->mn);
    free(st->mx);
    free(st);
}

typedef struct {
    int val;
    int l;
    int r;
} Node;

typedef struct {
    Node* heap;
    int size;
    int cap;
} MaxHeap;

void heapInit(MaxHeap* h, int cap) {
    h->heap = (Node*)malloc(cap * sizeof(Node));
    h->size = 0;
    h->cap = cap;
}

void heapPush(MaxHeap* h, Node x) {
    if (h->size == h->cap) {
        h->cap *= 2;
        h->heap = (Node*)realloc(h->heap, h->cap * sizeof(Node));
    }

    int i = h->size++;
    h->heap[i] = x;

    while (i > 0) {
        int p = (i - 1) / 2;

        if (h->heap[p].val >= h->heap[i].val)
            break;

        Node tmp = h->heap[p];
        h->heap[p] = h->heap[i];
        h->heap[i] = tmp;

        i = p;
    }
}

Node heapPop(MaxHeap* h) {
    Node top = h->heap[0];

    h->heap[0] = h->heap[--h->size];

    int i = 0;

    while (1) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < h->size &&
            h->heap[left].val > h->heap[largest].val)
            largest = left;

        if (right < h->size &&
            h->heap[right].val > h->heap[largest].val)
            largest = right;

        if (largest == i)
            break;

        Node tmp = h->heap[i];
        h->heap[i] = h->heap[largest];
        h->heap[largest] = tmp;

        i = largest;
    }

    return top;
}

Node heapTop(MaxHeap* h) {
    return h->heap[0];
}

long long maxTotalValue(int* nums, int numsSize, int k) {
    int n = numsSize;
    long long res = 0;

    SparseTable* st = createSparseTable(nums, n);

    MaxHeap pq;
    heapInit(&pq, n + k + 5);

    for (int i = 0; i < n; i++) {
        Node cur = {query(st, i, n), i, n};
        heapPush(&pq, cur);
    }

    while (pq.size > 0 && heapTop(&pq).val > 0 && k > 0) {
        Node cur = heapPop(&pq);

        res += cur.val;
        k--;

        if (cur.r - cur.l > 1) {
            Node nxt = {
                query(st, cur.l, cur.r - 1),
                cur.l,
                cur.r - 1
            };
            heapPush(&pq, nxt);
        }
    }

    freeSparseTable(st);
    free(pq.heap);

    return res;
}