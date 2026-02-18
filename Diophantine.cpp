ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1;
    while (b) {
        ll q = a / b;
        tie(x, x1) = make_pair(x1, x - q * x1);
        tie(y, y1) = make_pair(y1, y - q * y1);
        tie(a, b) = make_pair(b, a - q * b);
    }
    return a < 0 ? (x *= -1, y *= -1, a *= -1, a) : a;
}
bool diophantine(ll a, ll b, ll c, ll &x, ll &y, ll &g) {
    if (a == 0 && b == 0) return c ? 0 : (x = y = 0, 1);
    g = extended_gcd(a, b, x, y);
    return (c % g == 0 ? (x *= c / g, y *= c / g, 1) : 0);
}
ll divdown(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b);
}
ll divup(ll a, ll b) {
    return a / b + ((a ^ b) >= 0 && a % b);
}
vector<pll> allsolution(ll a, ll b, ll c, ll lx, ll rx, ll ly, ll ry) {
    // x = x0 + k*(b/g)    y = y0 - k*(a/g)
    ll x0, y0, g;
    if (!diophantine(a, b, c, x0, y0, g)) return {};
    vector<pll> ans;
    if (!g) {
        for (ll x = lx; x <= rx; x++)
            for (ll y = ly; y <= ry; y++) ans.pb({x, y});
        return ans;
    }
    if (!a) {
        ll y = c / b;
        if (!(ly <= y && y <= ry)) return {};
        for (ll x = lx; x <= rx; x++) ans.pb({x, y});
        return ans;
    }
    if (!b) {
        ll x = c / a;
        if (!(lx <= x && x <= rx)) return {};
        for (ll y = ly; y <= ry; y++) ans.pb({x, y});
        return ans;
    }
    ll dx = b / g, dy = a / g;
    ll kmin, kmax;
    if (dx > 0) kmin = divup(lx - x0, dx), kmax = divdown(rx - x0, dx);
    else kmin = divup(rx - x0, dx), kmax = divdown(lx - x0, dx);
    if (dy > 0) kmin = max(kmin, divup(y0 - ry, dy)), kmax = min(kmax, divdown(y0 - ly, dy));
    else kmin = max(kmin, divup(y0 - ly, dy)), kmax = min(kmax, divdown(y0 - ry, dy));
    for (ll k = kmin; k <= kmax; k++) ans.pb({x0 + k * dx, y0 - k * dy});
    return ans;
}
bool positive_sol_minf(ll a, ll b, ll c, ll &x, ll &y, ll cx, ll cy) {
    // f(x,y)= cx*x + cy*y
    ll g;
    if (!diophantine(a, b, c, x, y, g)) return 0;
    ll dx = b / g, dy = a / g;
    ll kmin = -INF, kmax = INF;
    dx > 0 ? kmin = max(kmin, divup(-x, dx)) : kmax = min(kmax, divdown(-x, dx));
    dy < 0 ? kmin = max(kmin, divup(y, dy)) : kmax = min(kmax, divdown(y, dy));
    if (kmin > kmax) return 0;
    ll df = cx * dx - cy * dy;
    ll k = df >= 0 ? kmin : kmax; // df<0 para max
    x += dx * k;
    y -= dy * k;
    return 1;
}
