vector<int> adj[MX];
int tin[MX], low[MX], timer;
vector<pii> bridges;
int component[MX];
vector<int> nods[MX];
vector<array<int, 3>> adjcomp[MX];
void dfs(int u, int p) {
    tin[u] = low[u] = ++timer;
    for (int v : adj[u])
        if (v != p) {
            if (tin[v]) low[u] = min(low[u], tin[v]);
            else dfs(v, u), low[u] = min(low[u], low[v]);
            if (tin[u] < low[v]) bridges.pb({u, v});
        }
}
bool isbridge(int u, int v) {
    if (tin[u] > tin[v]) swap(u, v);
    return tin[u] < low[v];
}
void dfsc(int u, int comp) {
    component[u] = comp;
    nods[comp].pb(u);
    for (int v : adj[u])
        if (!isbridge(u, v) && !component[v]) dfsc(v, comp);
}
int tree_bridge(int n) {
    dfs(1, 1);
    int comp = 0;
    for (int u = 1; u <= n; u++)
        if (!component[u]) dfsc(u, ++comp);
    for (auto [u, v] : bridges) {
        int cu = component[u], cv = component[v];
        adjcomp[cu].pb({cv, u, v});
        adjcomp[cv].pb({cu, u, v});
    }
    return comp;
}
