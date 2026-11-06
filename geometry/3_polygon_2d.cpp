
// Requiere: point 2d, segments 2d
// O(n) - Doble del area orientada; positiva para CCW
ll area2(const vector<point> &p) {
    ll ans = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) ans += cross(p[i], p[(i + 1) % n]);
    return ans;
}
// O(n) - 0 fuera, 1 borde, 2 dentro de poligono simple
int pointInPolygon(const vector<point> &p, point q) {
    bool in = false;
    int n = p.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (onSegment(p[i], p[j], q)) return 1;
        if ((p[i].y > q.y) != (p[j].y > q.y)) {
            ll c = cross(p[i], p[j], q);
            if ((c > 0) == (p[j].y > p[i].y)) in = !in;
        }
    }
    return in ? 2 : 0;
}
// O(log n) - 0 fuera, 1 borde, 2 dentro; hull CCW estricto
int pointInConvex(const vector<point> &p, point q) {
    int n = p.size();
    if (n == 0) return 0;
    if (n == 1) return p[0] == q ? 1 : 0;
    if (n == 2) return onSegment(p[0], p[1], q) ? 1 : 0;
    if (p[0] == q) return 1;
    ll a = cross(p[0], p[1], q);
    ll b = cross(p[0], p[n - 1], q);
    if (a < 0 || b > 0) return 0;
    if (a == 0) return onSegment(p[0], p[1], q) ? 1 : 0;
    if (b == 0) return onSegment(p[0], p[n - 1], q) ? 1 : 0;
    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) >> 1;
        if (cross(p[0], p[m], q) >= 0) l = m;
        else r = m;
    }
    ll c = cross(p[l], p[l + 1], q);
    if (c < 0) return 0;
    if (c == 0) return onSegment(p[l], p[l + 1], q) ? 1 : 0;
    return 2;
}
// O(n) - Verifica si un poligono simple es convexo
bool isConvex(const vector<point> &p) {
    int n = p.size();
    if (n < 3) return false;
    int d = 0;
    for (int i = 0; i < n; i++) {
        ll c = cross(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        int s = (c > 0) - (c < 0);
        if (s == 0) continue;
        if (d != 0 && d != s) return false;
        d = s;
    }
    return d != 0;
}
