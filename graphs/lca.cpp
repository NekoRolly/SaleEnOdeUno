int tIn[MX], tOut[MX];
int anc[MX][LG];
int timer;

void dfs(int u) {
    tIn[u] = timer++;
    for (int j = 1; j < LG; j++) anc[u][j] = anc[anc[u][j - 1]][j - 1];
    for (int v : adj[u]) {
        if (v == anc[u][0]) continue;
        anc[v][0] = u;
        dfs(v);
    }
    tOut[u] = timer++;
}

bool isAnc(int u, int v) { // is u ancestor of v ?
    return tIn[u] <= tIn[v] && tOut[u] >= tOut[v];
}

int lca(int u, int v) { // O(log n)
    if (isAnc(u, v)) return u;
    if (isAnc(v, u)) return v;
    for (int i = LG - 1; i >= 0; i--) {
        if (!isAnc(anc[u][i], v)) u = anc[u][i];
    }
    return anc[u][0];
}