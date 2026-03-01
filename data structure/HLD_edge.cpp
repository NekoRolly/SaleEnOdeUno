struct Graph {
    vector<vector<pll>> adj;
    vector<ll> padre, wpadre, prof, heavy, head, pos, base, L, R;
    segmentTree st;
    ll curpos;
    ll n;
    ll dfs(ll u, ll p, ll wp) {
        padre[u] = p;
        wpadre[u] = wp;
        ll szu = 1;
        ll mxsz = 0;
        heavy[u] = 0;
        for (auto [v, w] : adj[u])
            if (v != p) {
                prof[v] = prof[u] + 1;
                ll szv = dfs(v, u, w);
                szu += szv;
                if (mxsz < szv) mxsz = szv, heavy[u] = v;
            }
        return szu;
    }
    void decompose(ll u, ll h) {
        head[u] = h;
        L[u] = curpos;
        pos[u] = curpos++;
        base[pos[u]] = wpadre[u];
        if (heavy[u] != 0) decompose(heavy[u], h);
        for (auto [v, w] : adj[u])
            if (v != padre[u] && v != heavy[u]) decompose(v, v);
        R[u] = curpos - 1;
    }
    void pupdate(ll u, ll v, ll val) {
        if (u == padre[v]) swap(u, v);
        st.pupdate(pos[u], val);
    }
    void update(ll u, ll v, ll val) {
        while (head[u] != head[v]) {
            if (prof[head[u]] > prof[head[v]]) swap(u, v);
            st.update(pos[head[v]], pos[v], val);
            v = padre[head[v]];
        }
        if (prof[u] > prof[v]) swap(u, v);
        if (u != v) st.update(pos[u] + 1, pos[v], val);
    }
    ll query(ll u, ll v) {
        ll ans = INF;
        while (head[u] != head[v]) {
            if (prof[head[u]] > prof[head[v]]) swap(u, v);
            ans = f(ans, st.query(pos[head[v]], pos[v]));
            v = padre[head[v]];
        }
        if (prof[u] > prof[v]) swap(u, v);
        if (u != v) ans = f(ans, st.query(pos[u] + 1, pos[v]));
        return ans;
    }
    ll subtreequery(ll u) {
        if (L[u] == R[u]) return 0;
        return st.query(L[u] + 1, R[u]);
    }
    void subtreeupdate(ll u, ll val) {
        if (L[u] == R[u]) return;
        st.update(L[u] + 1, R[u], val);
    }
    Graph(vector<pair<pll, ll>> &aristas, ll root = 1) : n(aristas.size() + 1) {
        adj.assign(n + 1, vector<pll>());
        padre.assign(n + 1, 0), wpadre.assign(n + 1, 0), prof.assign(n + 1, 0);
        heavy.assign(n + 1, 0), head.assign(n + 1, 0), pos.assign(n + 1, 0);
        L.assign(n + 1, 0), R.assign(n + 1, 0), base.resize(n);
        curpos = 0;
        for (auto [edge, w] : aristas) {
            auto [u, v] = edge;
            adj[u].pb({v, w});
            adj[v].pb({u, w});
        }
        prof[root] = 0;
        dfs(root, root, 0LL);
        decompose(root, root);
        st = segmentTree(base);
    }
};
