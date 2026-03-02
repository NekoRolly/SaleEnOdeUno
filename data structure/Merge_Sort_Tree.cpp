struct segmentTree {
    vector<vector<ll>> seg;
    ll n, N;
    segmentTree() {}
    segmentTree(vector<ll> &a) : n(a.size()) {
        N = 1;
        while (N < n) N <<= 1;
        seg.assign(2 * N, vector<ll>());
        for (int i = 0; i < n; i++) seg[i + N] = {a[i]};
        for (int i = N - 1; i > 0; i--) {
            auto &l = seg[i << 1], &r = seg[i << 1 | 1];
            seg[i].resize((ll)l.size() + (ll)r.size());
            merge(all(l), all(r), seg[i].begin());
        }
    }
    // cantidad de elementos mayores a "a" en el intervalo [ql,qr]
    ll query1(ll ql, ll qr, ll a) {
        ll l = ql + N, r = qr + N;
        ll ans = 0;
        while (l <= r) {
            if (l & 1) {
                auto &v = seg[l++];
                ans += v.end() - upper_bound(all(v), a);
            }
            if (!(r & 1)) {
                auto &v = seg[r--];
                ans += v.end() - upper_bound(all(v), a);
            }
            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
    // cantidad de elementos menores a "a" en el intervalo [ql,qr]
    ll query2(ll ql, ll qr, ll a) {
        ll l = ql + N, r = qr + N;
        ll ans = 0;
        while (l <= r) {
            if (l & 1) {
                auto &v = seg[l++];
                ans += lower_bound(all(v), a) - v.begin();
            }
            if (!(r & 1)) {
                auto &v = seg[r--];
                ans += lower_bound(all(v), a) - v.begin();
            }
            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
};
