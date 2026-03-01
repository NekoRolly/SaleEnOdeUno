struct IterativeSegmentTree { // Index 0
    int n;
    ll ST[2 * MX];
    const ll NEUT = 0;
    void build(vector<ll> &a) {
        n = a.size();
        for (int i = n; i < (n << 1); i++) ST[i] = a[i - n];
        for (int i = n - 1; i > 0; i--) ST[i] = f(ST[i << 1], ST[i << 1 | 1]);
    }
    ll f(ll x, ll y) { return max(x, y); }
    void update(int i, ll val) {
        for (ST[i += n] = val; i >>= 1; ) ST[i] = f(ST[i << 1], ST[i << 1 | 1]);
    }
    ll query(int l, int r) { // [l, r>
        ll ansL = NEUT, ansR = NEUT;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ansL = f(ansL, ST[l++]);
            if (r & 1) ansR = f(ST[--r], ansR);
        }
        return f(ansL, ansR);
    }
};