struct nod {
    ll t;
    ll lazy;
    nod *l;
    nod *r;
};
static nod nods[ND];
static int id = 0;
nod *crearnodo() {
    nods[id].t = NEUT, nods[id].lazy = NEUT_LAZY, nods[id].l = nods[id].r = NULL;
    return &nods[id++];
}
ll f(ll a, ll b) {
    return a + b;
}
void aply(ll val, nod *u, ll l, ll r) {
    u->t = (r - l + 1) * val;
    u->lazy = val;
}
struct segmentTree {
    ll n;
    nod *root = NULL;
    segmentTree(ll n) : n(n) {}
    void push(nod *u, ll l, ll r) {
        if (u->lazy == NEUT_LAZY || l == r) return;
        ll m = (l + r) / 2;
        if (!u->l) u->l = crearnodo();
        if (!u->r) u->r = crearnodo();
        aply(u->lazy, u->l, l, m);
        aply(u->lazy, u->r, m + 1, r);
        u->lazy = NEUT_LAZY;
    }
    ll query(ll ql, ll qr, nod *u, ll l, ll r) {
        if (qr < l || r < ql || !u) return NEUT;
        if (ql <= l && r <= qr) return u->t;
        push(u, l, r);
        ll m = (l + r) / 2;
        return f(query(ql, qr, u->l, l, m), query(ql, qr, u->r, m + 1, r));
    }
    ll query(ll ql, ll qr) {
        return query(ql, qr, root, 0, n - 1);
    }
    void update(ll ql, ll qr, ll val, nod *&u, ll l, ll r) {
        if (qr < l || r < ql) return;
        if (!u) u = crearnodo();
        if (ql <= l && r <= qr) aply(val, u, l, r);
        else {
            push(u, l, r);
            ll m = (l + r) / 2;
            update(ql, qr, val, u->l, l, m);
            update(ql, qr, val, u->r, m + 1, r);
            u->t = f(u->l ? u->l->t : NEUT, u->r ? u->r->t : NEUT);
        }
    }
    void update(ll ql, ll qr, ll val) {
        update(ql, qr, val, root, 0, n - 1);
    }
};
