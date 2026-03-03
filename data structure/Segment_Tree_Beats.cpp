struct node {
    ll sum;
    ll max1, max2, cont; // min para chmax
};
node f(node a, node b) { // simetrico con min para chmax
    node ans;
    ans.sum = a.sum + b.sum;
    ans.max1 = max(a.max1, b.max1);
    if (a.max1 == b.max1) ans.max2 = max(a.max2, b.max2), ans.cont = a.cont + b.cont;
    else if (a.max1 > b.max1) ans.max2 = max(a.max2, b.max1), ans.cont = a.cont;
    else ans.max2 = max(a.max1, b.max2), ans.cont = b.cont;
    return ans;
}
struct SegmentTree {
    vector<node> t;
    int n;
    SegmentTree(vector<ll> &a) : n(a.size()) {
        t.resize(2 * n);
        build(a, 1, 0, n - 1);
    }
    void build(vector<ll> &a, int id, int l, int r) {
        if (l == r) t[id] = {a[l], a[l], -INF, 1}; // chmax: -INF -> INF
        else {
            int m = (l + r) >> 1;
            int idl = id + 1;
            int idr = id + 2 * (m - l + 1);
            build(a, idl, l, m), build(a, idr, m + 1, r);
            t[id] = f(t[idl], t[idr]);
        }
    }
    void apply(ll val, int id) {
        if (t[id].max1 <= val) return; // chmax: (<=) -> (>=)
        t[id].sum += t[id].cont * (val - t[id].max1);
        t[id].max1 = val;
    }
    void push(int id, int l, int r) {
        if (l == r) return;
        int m = (l + r) >> 1;
        int idl = id + 1;
        int idr = id + 2 * (m - l + 1);
        apply(t[id].max1, idl);
        apply(t[id].max1, idr);
    }
    void update(int ql, int qr, ll val, int id, int l, int r) {
        if (qr < l || r < ql || t[id].max1 <= val) return; //chmax: (<=) -> (>=)
        if (ql <= l && r <= qr && t[id].max2 < val) apply(val, id); // chmax: (<) -> (>)
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
        if (ql <= l && r <= qr) return t[id].sum;
        push(id, l, r);
        int m = (l + r) >> 1;
        int idl = id + 1;
        int idr = id + 2 * (m - l + 1);
        return query(ql, qr, idl, l, m) + query(ql, qr, idr, m + 1, r);
    }
};
