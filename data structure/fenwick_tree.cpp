struct FenwickTree { // Index 1
    int n, ft[MX + 1];
    void update(int l, int v) {
        for (; l <= n; l += l & -l) ft[l] += val;
    }
    int query(int l) {
        int ans = 0;
        for (; l > 0; l -= l & -l) ans += t[l];
        return ans;
    }
    int query(int l, int r) { return query(r) - query(l - 1); }
}