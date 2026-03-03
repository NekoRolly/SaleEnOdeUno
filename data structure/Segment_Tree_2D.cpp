struct ST2D {
    int n, m;
    vector<vector<ll>> t;
    ll f(ll a, ll b) {
        return a + b;
    }
    ST2D(vector<vector<ll>> &a) {
        n = a.size();
        m = a[0].size();
        t.assign(2 * n, vector<ll>(2 * m, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) t[i + n][j + m] = a[i][j];
        for (int i = n; i < 2 * n; i++)
            for (int j = m - 1; j > 0; j--) t[i][j] = f(t[i][j << 1], t[i][j << 1 | 1]);
        for (int i = n - 1; i > 0; i--)
            for (int j = 1; j < 2 * m; j++) t[i][j] = f(t[i << 1][j], t[i << 1 | 1][j]);
    }
    void update(int x, int y, ll val) {
        x += n, y += m, t[x][y] = val;
        for (int j = y; j > 1; j >>= 1) t[x][j >> 1] = f(t[x][j], t[x][j ^ 1]);
        for (int i = x >> 1; i > 0; i >>= 1) {
            int j = y;
            t[i][j] = f(t[i << 1][j], t[i << 1 | 1][j]);
            for (; j > 1; j >>= 1) t[i][j >> 1] = f(t[i][j], t[i][j ^ 1]);
        }
    }
    ll queryY(int i, int l, int r) {
        ll ans = 0;
        for (l += m, r += m + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = f(ans, t[i][l++]);
            if (r & 1) ans = f(t[i][--r], ans);
        }
        return ans;
    }
    ll query(int lx, int rx, int ly, int ry) {
        ll ans = 0;
        for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1) {
            if (x1 & 1) ans = f(ans, queryY(x1++, y1, y2));
            if (x2 & 1) ans = f(queryY(--x2, y1, y2), ans);
        }
        return ans;
    }
};
