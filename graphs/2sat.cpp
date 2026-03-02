struct SAT { // Index_1
    vector<vector<int>> adj, adjt;
    vector<bool> used;
    vector<int> comp;
    int n;
    stack<int> st;
    SAT(int n) : n(n) {
        adj.resize(2 * n + 1), adjt.resize(2 * n + 1);
        used.assign(2 * n + 1, 0), comp.assign(2 * n + 1, 0);
    }
    void add(int p, bool bp, int q, bool bq) { // add p -> q
        p += (!bp) * n;
        q += (!bq) * n;
        adj[p].pb(q);
        adjt[q].pb(p);
    }
    void addor(int p, bool bp, int q, bool bq) { // add p or q
        add(p, !bp, q, bq);
        add(q, !bq, p, bp);
    }
    void addxor(int p, bool bp, int q, bool bq) { // add p xor q
        addor(p, bp, q, bq);
        addor(p, !bp, q, !bq);
    }
    void addnxor(int p, bool bp, int q, bool bq) { // add ~(p xor q)
        addor(p, !bp, q, bq);
        addor(p, bp, q, !bq);
    }
    void dfs(int u) {
        used[u] = 1;
        for (int v : adj[u])
            if (!used[v]) dfs(v);
        st.push(u);
    }
    void _dfs(int u, int c) {
        comp[u] = c;
        for (int v : adjt[u])
            if (!comp[v]) _dfs(v, c);
    }
    bool solve(vector<bool> &ans) {
        ans.resize(n + 1);
        for (int u = 1; u <= 2 * n; u++)
            if (!used[u]) dfs(u);
        int c = 0;
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            if (!comp[u]) _dfs(u, ++c);
        }
        for (int p = 1; p <= n; p++) {
            if (comp[p] == comp[p + n]) return false;
            ans[p] = comp[p] > comp[p + n];
        }
        return true;
    }
};
