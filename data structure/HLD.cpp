struct Graph {
    vector<vector<ll>> adj;
    vector<ll> padre, prof, heavy, head, pos, base, L, R;
    segmentTree st;
    ll curpos, n;
    ll dfs(ll u, ll p) {
        padre[u] = p;
        ll szu = 1;
        ll mxsz = 0;
        heavy[u] = 0;
        for (ll v : adj[u])
            if (v != p) {
                prof[v] = prof[u] + 1;
                ll szv = dfs(v, u);
                szu += szv;
                if (mxsz < szv) {
                    mxsz = szv;
                    heavy[u] = v;
                }
            }
        return szu;
    }
    void decompose(ll u, ll h, vector<ll> &a) {
        head[u] = h;
        L[u] = curpos;
        pos[u] = curpos++;
        base[pos[u]] = a[u - 1];
        if (heavy[u] != 0) decompose(heavy[u], h, a);
        for (ll v : adj[u])
            if (v != padre[u] && v != heavy[u]) decompose(v, v, a);
        R[u] = curpos - 1;
    }
    void pupdate(ll u, ll val) {
        st.pupdate(pos[u], val);
    }
    void update(ll u, ll v, ll val) {
        while (head[u] != head[v]) {
            if (prof[head[u]] > prof[head[v]]) swap(u, v);
            st.update(pos[head[v]], pos[v], val);
            v = padre[head[v]];
        }
        if (prof[u] > prof[v]) swap(u, v);
        st.update(pos[u], pos[v], val);
    }
    ll query(ll u, ll v) {
        ll ans = INF;
        while (head[u] != head[v]) {
            if (prof[head[u]] > prof[head[v]]) swap(u, v);
            ans = f(ans, st.query(pos[head[v]], pos[v]));
            v = padre[head[v]];
        }
        if (prof[u] > prof[v]) swap(u, v);
        ans = f(ans, st.query(pos[u], pos[v]));
        return ans;
    }
    ll subtreequery(ll u) {
        return st.query(L[u], R[u]);
    }
    void subtreeupdate(ll u, ll val) {
        st.update(L[u], R[u], val);
    }
    Graph(vector<ll> &a, vector<pll> &aristas, ll root = 1) : n(a.size()) {
        adj.assign(n + 1, vector<ll>()), padre.assign(n + 1, 0), prof.assign(n + 1, 0);
        heavy.assign(n + 1, 0), head.assign(n + 1, 0), pos.assign(n + 1, 0);
        L.assign(n + 1, 0), R.assign(n + 1, 0), base.resize(n);
        curpos = 0;
        for (auto [u, v] : aristas) {
            adj[u].pb(v);
            adj[v].pb(u);
        }
        prof[root] = 0;
        dfs(root, root);
        decompose(root, root, a);
        st = segmentTree(base);
    }
};
