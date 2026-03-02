struct Centroid_Decomposition{
    vector<int> adj[N];
    int sz[N],vis[N],aux;
    int pa[N];

    int find(int u,int p,int Sz){
        int mx = 0, c = 0; sz[u] = 1;
        for (auto v : adj[u]){
            if (v == p || vis[v]) continue;
            c ^= find(v, u, Sz);
            sz[u] += sz[v];
            mx = max(mx, sz[v]);
        }
        if (max(mx, Sz-sz[u]) <= Sz/2)
            aux = p, c = u;
        return c;
    }

    void build(int u,int p,int Sz){
        aux = -1, u = find(u, -1, Sz);
        if (aux != -1) sz[aux] = Sz-sz[u];
        vis[u] = 1, sz[u] = Sz, pa[u] = p;
        for (auto v : adj[u])
            if (!vis[v]) build(v, u, sz[v]);
    }
} cd; // by NekoRolly