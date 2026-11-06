
// Requiere: point 2d; al menos 2 puntos (si no, -1)
// O(n log n) - Minima distancia al cuadrado, Divide and Conquer
ll closestPair2(vector<point> p) {
    int n = p.size();
    if (n < 2) return -1;
    sort(all(p));
    vector<point> t(n);
    auto cmp = [](point a, point b) { return tie(a.y, a.x) < tie(b.y, b.x); };
    auto dfs = [&](auto &&self, int l, int r) -> ll {
        if (r - l <= 3) {
            ll ans = LLONG_MAX;
            for (int i = l; i < r; i++)
                for (int j = i + 1; j < r; j++) ans = min(ans, dist2(p[i], p[j]));
            sort(p.begin() + l, p.begin() + r, cmp);
            return ans;
        }
        int m = (l + r) >> 1;
        ll x = p[m].x;
        ll ans = min(self(self, l, m), self(self, m, r));
        merge(p.begin() + l, p.begin() + m, p.begin() + m, p.begin() + r, t.begin(), cmp);
        copy(t.begin(), t.begin() + r - l, p.begin() + l);
        vector<point> v;
        for (int i = l; i < r; i++) {
            ll dx = p[i].x - x;
            if (dx * dx >= ans) continue;
            for (int j = (int)v.size() - 1; j >= 0; j--) {
                ll dy = p[i].y - v[j].y;
                if (dy * dy >= ans) break;
                ans = min(ans, dist2(p[i], v[j]));
            }
            v.pb(p[i]);
        }
        return ans;
    };
    return dfs(dfs, 0, n);
}
