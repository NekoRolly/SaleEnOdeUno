// Requiere: point 2d; h = convexHull(p)
// O(n) - Maxima distancia al cuadrado, Rotating Calipers
ll diameter2(const vector<point> &h) {
    int n = h.size();
    if (n < 2) return 0;
    if (n == 2) return dist2(h[0], h[1]);
    ll ans = 0;
    int j = 1;
    for (int i = 0; i < n; i++) {
        int ni = (i + 1) % n;
        while (cross(h[i], h[ni], h[(j + 1) % n]) > cross(h[i], h[ni], h[j])) j = (j + 1) % n;
        ans = max({ans, dist2(h[i], h[j]), dist2(h[ni], h[j])});
        int nj = (j + 1) % n;
        if (cross(h[i], h[ni], h[nj]) == cross(h[i], h[ni], h[j]))
            ans = max({ans, dist2(h[i], h[nj]), dist2(h[ni], h[nj])});
    }
    return ans;
}
