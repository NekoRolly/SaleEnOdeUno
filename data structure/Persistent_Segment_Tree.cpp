const ll MX = 2e5 + 5;
const ll Q = 2e5 + 5;
const ll MXT = 2 * MX + 20 * Q;
struct PST {
    ll root[Q + 1], t[MXT], L[MXT], R[MXT];
    ll n, nodos, lastversion = 0;
    PST(vector<ll> &a) : n(a.size()) {
        nodos = 2 * n - 1;
        root[0] = 1;
        build(a, 1, 0, n - 1);
    }
    ll f(ll a, ll b) {
        return a + b;
    }
    void build(vector<ll> &a, ll id, ll l, ll r) {
        if (l == r) t[id] = a[l];
        else {
            ll m = (l + r) / 2;
            ll idl = id + 1;
            ll idr = id + 2 * (m - l + 1);
            L[id] = idl;
            R[id] = idr;
            build(a, idl, l, m);
            build(a, idr, m + 1, r);
            t[id] = f(t[idl], t[idr]);
        }
    }
    ll query(ll ql, ll qr, ll id, ll l, ll r) {
        if (ql <= l && r <= qr) return t[id];
        ll m = (l + r) / 2;
        if (qr <= m) return query(ql, qr, L[id], l, m);
        if (m + 1 <= ql) return query(ql, qr, R[id], m + 1, r);
        return f(query(ql, qr, L[id], l, m), query(ql, qr, R[id], m + 1, r));
    }
    ll query(ll ql, ll qr, ll version = -1) {
        if (version == -1) version = lastversion;
        return query(ql, qr, root[version], 0, n - 1);
    }
    void update(ll pos, ll val, ll prev, ll &id, ll l, ll r) {
        id = ++nodos;
        if (l == r) t[id] = val;
        else {
            ll m = (l + r) / 2;
            L[id] = L[prev];
            R[id] = R[prev];
            if (pos <= m) update(pos, val, L[prev], L[id], l, m);
            else update(pos, val, R[prev], R[id], m + 1, r);
            t[id] = f(t[L[id]], t[R[id]]);
        }
    }
    void update(ll pos, ll val, ll version = -1) {
        if (version == -1) version = lastversion;
        lastversion++;
        update(pos, val, root[version], root[lastversion], 0, n - 1);
    }
};
