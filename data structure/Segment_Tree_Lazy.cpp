struct SegmentTree { // id: index 1. Vector a: Index 0
    vector<ll> t, lazy;
    int n;
    SegmentTree(vector<ll> &a) : n(a.size()) {
        t.assign(2 * n, NEUT), lazy.assign(2 * n, NEUT_LAZY);
        build(a, 1, 0, n - 1);
    }
    ll f(ll a, ll b) {
        return a + b;
    }
    void aply(ll val, int id, int l, int r) {
        t[id] += (r - l + 1) * val;
        lazy[id] += val;
    }
    void build(vector<ll> &a, int id, int l, int r) {
        if (l == r) t[id] = a[l];
        else {
            int m = (l + r) >> 1;
            int idl = id + 1;
            int idr = id + 2 * (m - l + 1);
            build(a, idl, l, m), build(a, idr, m + 1, r);
            t[id] = f(t[idl], t[idr]);
        }
    }
    void push(int id, int l, int r) {
        if (l == r || lazy[id] == NEUT_LAZY) return;
        int m = (l + r) >> 1;
        int idl = id + 1;
        int idr = id + 2 * (m - l + 1);
        aply(lazy[id], idl, l, m);
        aply(lazy[id], idr, m + 1, r);
        lazy[id] = NEUT_LAZY;
    }
    void update(int ql, int qr, ll val, int id, int l, int r) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) aply(val, id, l, r);
        else {
            push(id, l, r);
            int m = (l + r) >> 1;
            int idl = id + 1;
            int idr = id + 2 * (m - l + 1);
            update(ql, qr, val, idl, l, m), update(ql, qr, val, idr, m + 1, r);
            t[id] = f(t[idl], t[idr]);
        }
    }
    ll query(int ql, int qr, int id, int l, int r) {
        if (qr < l || r < ql) return NEUT;
        if (ql <= l && r <= qr) return t[id];
        push(id, l, r);
        int m = (l + r) >> 1;
        int idl = id + 1;
        int idr = id + 2 * (m - l + 1);
        return f(query(ql, qr, idl, l, m), query(ql, qr, idr, m + 1, r));
    }
};
