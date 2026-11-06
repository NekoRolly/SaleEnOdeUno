// Requiere: point 2d
// O(n log n) - Andrew: hull (Antihorario) sin colineales
vector<point> convexHull(vector<point> p) {
    sort(all(p));
    p.erase(unique(all(p)), p.end());
    int n = p.size();
    if (n <= 2) return p;
    vector<point> h;
    for (int i = 0; i < n; i++) {
        while (h.size() > 1 && cross(h[h.size() - 2], h.back(), p[i]) <= 0) h.pop_back();
        h.pb(p[i]);
    }
    int t = h.size();
    for (int i = n - 2; i >= 0; i--) {
        while (h.size() > t && cross(h[h.size() - 2], h.back(), p[i]) <= 0) h.pop_back();
        h.pb(p[i]);
    }
    h.pop_back();
    return h;
}
