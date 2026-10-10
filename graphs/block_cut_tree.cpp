vector<int> adj[MX], bcc[MX], bct[2 * MX], st;
// bcc[u] = componentes a la que pertenece el nodo u
// bct[u] = adj del BCT
int tin[MX], low[MX], timer;
// low[u] : minimo tin de los backedges entre todos los de los desendientes de u en el __dfs
int comp[MX]; // representante de u en el BCT
int c;
void __dfs(int u, int p = -1) {
    tin[u] = low[u] = ++timer;
    st.pb(u);
    bool skip = 1; // Si ha  multiedges
    for (int v : adj[u]) {
        if (v == p && skip) {
            skip = 0;
            continue;
        }
        if (tin[v]) low[u] = min(low[u], tin[v]);
        else {
            __dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (tin[u] <= low[v]) {
                c++;
                int x = -1;
                while (x != v) x = st.back(), st.pop_back(), bcc[x].pb(c);
                bcc[u].pb(c);
            }
        }
    }
}
void buildBCT(int n) {
    for (int i = 1; i <= n; i++)
        if (!tin[i]) {
            __dfs(i);
            st.pop_back();
            if (bcc[i].empty()) bcc[i].pb(++c);
        }
    for (int u = 1; u <= n; u++) {
        if (bcc[u].size() == 1) comp[u] = bcc[u].back();
        else {
            comp[u] = ++c;
            for (int v : bcc[u]) bct[comp[u]].pb(v), bct[v].pb(comp[u]);
        }
    }
}