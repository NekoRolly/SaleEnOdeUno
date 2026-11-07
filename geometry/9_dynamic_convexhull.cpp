using i128 = __int128_t;
struct Point {
    ll x, y;
    bool operator==(const Point &p) const {
        return x == p.x && y == p.y;
    }
};
i128 cross(Point a, Point b, Point c) {
    return (i128)(b.x - a.x) * (c.y - a.y) - (i128)(b.y - a.y) * (c.x - a.x);
}
struct DynamicConvexHull {
    map<ll, ll> up, low;
    void addChain(map<ll, ll> &ch, Point p, bool upper) {
        auto it = ch.lower_bound(p.x);
        if (it != ch.end() && it->first == p.x) {
            if (upper ? it->second >= p.y : it->second <= p.y) return;
            it = ch.erase(it);
        }
        if (it != ch.begin() && it != ch.end()) {
            auto l = prev(it);
            i128 c = cross({l->first, l->second}, p, {it->first, it->second});
            if (upper ? c >= 0 : c <= 0) return;
        }
        auto cur = ch.emplace_hint(it, p.x, p.y);
        while (cur != ch.begin()) {
            auto b = prev(cur);
            if (b == ch.begin()) break;
            auto a = prev(b);
            i128 c = cross({a->first, a->second}, {b->first, b->second}, p);
            if (upper ? c < 0 : c > 0) break;
            ch.erase(b);
        }
        while (next(cur) != ch.end()) {
            auto b = next(cur), c = next(b);
            if (c == ch.end()) break;
            i128 z = cross(p, {b->first, b->second}, {c->first, c->second});
            if (upper ? z < 0 : z > 0) break;
            ch.erase(b);
        }
    }
    void add(Point p) {
        addChain(up, p, true);
        addChain(low, p, false);
    }
    int check(const map<ll, ll> &ch, Point p, bool upper) const {
        if (ch.empty() || p.x < ch.begin()->first || p.x > ch.rbegin()->first) return -1;
        auto it = ch.lower_bound(p.x);
        if (it->first == p.x) {
            if (p.y == it->second) return 0;
            return (upper ? p.y > it->second : p.y < it->second) ? -1 : 1;
        }
        auto l = prev(it);
        i128 c = cross({l->first, l->second}, {it->first, it->second}, p);
        if (c == 0) return 0;
        return (upper ? c > 0 : c < 0) ? -1 : 1;
    }
    // 0: fuera, 1: dentro, 2: borde
    int contains(Point p) const {
        int a = check(up, p, true);
        int b = check(low, p, false);
        if (a < 0 || b < 0) return 0;
        if (!a || !b || p.x == up.begin()->first || p.x == up.rbegin()->first) return 2;
        return 1;
    }
    // Vertices en orden horario
    vector<Point> getHull() const {
        vector<Point> res;
        for (auto [x, y] : up) res.push_back({x, y});

        for (auto it = low.rbegin(); it != low.rend(); ++it) {
            Point p{it->first, it->second};
            if (!(p == res.front()) && !(p == res.back())) res.push_back(p);
        }
        return res;
    }
    int size() const {
        if (up.empty()) return 0;
        int ans = up.size() + low.size();
        if (up.begin()->second == low.begin()->second) --ans;
        if (up.size() > 1 && up.rbegin()->second == low.rbegin()->second) --ans;
        return ans;
    }
};