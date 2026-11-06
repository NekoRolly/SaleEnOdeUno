
// Requiere: point 2d; poligonos convexos CCW, n,m >= 3
// O(n + m) - Suma de Minkowski; puede incluir colineales
vector<point> minkowskiSum(vector<point> a, vector<point> b) {
    if (a.empty() || b.empty()) return {};
    auto reorder = [](vector<point> &p) {
        int k = 0;
        for (int i = 1; i < (int)p.size(); i++)
            if (tie(p[i].y, p[i].x) < tie(p[k].y, p[k].x)) k = i;
        rotate(p.begin(), p.begin() + k, p.end());
    };
    reorder(a), reorder(b);
    int n = a.size(), m = b.size();
    a.pb(a[0]), b.pb(b[0]);
    int i = 0, j = 0;
    vector<point> ans;
    while (i < n || j < m) {
        ans.pb(a[i] + b[j]);
        if (i == n) {
            j++;
            continue;
        }
        if (j == m) {
            i++;
            continue;
        }
        ll c = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
        if (c >= 0) i++;
        if (c <= 0) j++;
    }
    return ans;
}
