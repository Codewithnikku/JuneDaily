class SparseTable {
    constructor(nums) {
        const n = nums.length;
        const w = Math.floor(Math.log2(n)) + 1;

        this.minTable = Array.from({ length: w }, () => Array(n).fill(0));
        this.maxTable = Array.from({ length: w }, () => Array(n).fill(0));

        for (let i = 0; i < n; i++) {
            this.minTable[0][i] = nums[i];
            this.maxTable[0][i] = nums[i];
        }

        for (let k = 1; k < w; k++) {
            const half = 1 << (k - 1);
            const len = 1 << k;

            for (let j = 0; j + len <= n; j++) {
                this.minTable[k][j] = Math.min(
                    this.minTable[k - 1][j],
                    this.minTable[k - 1][j + half]
                );

                this.maxTable[k][j] = Math.max(
                    this.maxTable[k - 1][j],
                    this.maxTable[k - 1][j + half]
                );
            }
        }
    }

    query(left, right) {
        const len = right - left;
        if (len <= 0) return 0;

        const k = Math.floor(Math.log2(len));

        const mx = Math.max(
            this.maxTable[k][left],
            this.maxTable[k][right - (1 << k)]
        );

        const mn = Math.min(
            this.minTable[k][left],
            this.minTable[k][right - (1 << k)]
        );

        return mx - mn;
    }
}

class MyMaxHeap {
    constructor() {
        this.heap = [];
    }

    push(item) {
        this.heap.push(item);
        let i = this.heap.length - 1;

        while (i > 0) {
            const p = (i - 1) >> 1;
            if (this.heap[p][0] >= this.heap[i][0]) break;

            [this.heap[p], this.heap[i]] = [this.heap[i], this.heap[p]];
            i = p;
        }
    }

    pop() {
        if (this.heap.length === 1) return this.heap.pop();

        const top = this.heap[0];
        this.heap[0] = this.heap.pop();

        let i = 0;

        while (true) {
            let largest = i;
            const l = i * 2 + 1;
            const r = i * 2 + 2;

            if (l < this.heap.length && this.heap[l][0] > this.heap[largest][0]) {
                largest = l;
            }

            if (r < this.heap.length && this.heap[r][0] > this.heap[largest][0]) {
                largest = r;
            }

            if (largest === i) break;

            [this.heap[i], this.heap[largest]] =
                [this.heap[largest], this.heap[i]];

            i = largest;
        }

        return top;
    }

    peek() {
        return this.heap[0];
    }

    size() {
        return this.heap.length;
    }
}

var maxTotalValue = function(nums, k) {
    const n = nums.length;
    let res = 0;

    const lut = new SparseTable(nums);
    const pq = new MyMaxHeap();

    for (let i = 0; i < n; i++) {
        pq.push([lut.query(i, n), i, n]);
    }

    while (pq.size() > 0 && pq.peek()[0] > 0 && k > 0) {
        const [val, l, r] = pq.pop();

        res += val;
        k--;

        if (r - l > 1) {
            pq.push([lut.query(l, r - 1), l, r - 1]);
        }
    }

    return res;
};