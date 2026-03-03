// find distance from source node to all nodes.
// supports negative edge weights.
// returns true if a negative cycle is detected.
bool bellmanFord(int s, int n) { // O(VE)
    d.assign(n + 1, INF);
    vector<bool> cycle(n, false);
    bool f = false;
    for (int i = 0; i < n; i++) {
        f = false;
        for (int u = 0; u < n; u++) {
            for (auto [v, w] : adj[u]) {
                if (d[u] != INF && d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    parent[v] = u;
                    f = true;
                    if (i == n - 1) cycle[v] = true;
                }
            }
        }
        if (!f) return false;
    }
    return true;
}