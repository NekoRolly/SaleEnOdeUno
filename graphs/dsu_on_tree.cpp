vector<int> adj[N];
int L[N],V[N],sz[N],cur;

void dfs1(int u,int p){
    L[u] = cur, V[cur++] = u, sz[u] = 1;
    for (int v : adj[u]){
        if (v == p) continue;
        dfs1(v, u);
        sz[u] += sz[v];
    }
}

void dfs2(int u,int p,bool flag){
    int big = -1;
    for (int v : adj[u])
        if (v != p && (big == -1 || sz[big] < sz[v])) big = v;
    for (int v : adj[u])
        if (v != p && v != big) dfs2(v, u, true);
    if (big != -1) dfs2(big, u, false);
    update(a[u], 1); // add
    for (int v : adj[u]){
        if (v == p || v == big) continue;
        for (int i=L[v]; i<L[v]+sz[v]; i++)
            update(a[V[i]], 1); // add
    }       
    ans[u] = dif;
    if (!flag) return;
    for (int i=L[u]; i<L[u]+sz[u]; i++)
        update(a[V[i]], -1); // remove
} // by NekoRolly