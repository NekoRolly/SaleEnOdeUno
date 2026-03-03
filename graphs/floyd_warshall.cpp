void Ini(int n) {
    for0(u, n) {
        for0(v, n) d[u][v] = INF, parent[u][v] = -1;
        d[u][u] = 0;
    }
}

void addEdge(int u, int v, int w) {
    if (w < d[u][v]) {
        d[u][v] = w;
        parent[u][v] = u;
    }
}

void floydWarshall(int n) { // O(V^3)
    for0(k, n) for0(u, n) for0(v, n) {
        if (d[u][k] == INF) continue;
        if (d[k][v] == INF) continue;
        if (d[u][k] + d[k][v] < d[u][v]) {
            d[u][v] = max(-INF, d[u][k] + d[k][v]);
            parent[u][v] = parent[k][v];
        }
    }

    // negative cycles
    for0(u, n) for0(v, n) for0(k, n) {
        if (d[k][k] < 0 && d[u][k] != INF && d[k][v] != INF) {
            d[u][v] = -INF;
        }
    }
}