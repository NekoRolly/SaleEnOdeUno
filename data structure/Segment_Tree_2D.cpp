struct segmentTree2D {
    ll t[2 * MX][2 * MX];
    ll n, m;
    segmentTree2D(vector<vector<ll>> &a) {
        n = a.size();
        m = a[0].size();
        build(a, 1, 0, n - 1);
    }
    ll f(ll a, ll b) {
        return a + b;
    }
    void buildy(vector<vector<ll>> &a, ll idx, ll lx, ll rx, ll idy, ll ly, ll ry) {
        if (ly == ry) {
            if (lx == rx) t[idx][idy] = a[lx][ly];
            else {
                ll mx = (lx + rx) / 2;
                ll idlx = idx + 1;
                ll idrx = idx + 2 * (mx - lx + 1);
                t[idx][idy] = f(t[idlx][idy], t[idrx][idy]);
            }
        } else {
            ll my = (ly + ry) / 2;
            ll idly = idy + 1;
            ll idry = idy + 2 * (my - ly + 1);
            buildy(a, idx, lx, rx, idly, ly, my);
            buildy(a, idx, lx, rx, idry, my + 1, ry);
            t[idx][idy] = f(t[idx][idly], t[idx][idry]);
        }
    }
    void build(vector<vector<ll>> &a, ll idx, ll lx, ll rx) {
        if (lx == rx) buildy(a, idx, lx, rx, 1, 0, m - 1);
        else {
            ll mx = (lx + rx) / 2;
            ll idlx = idx + 1;
            ll idrx = idx + 2 * (mx - lx + 1);
            build(a, idlx, lx, mx);
            build(a, idrx, mx + 1, rx);
            buildy(a, idx, lx, rx, 1, 0, m - 1);
        }
    }
    ll queryy(ll qly, ll qry, ll idx, ll idy, ll ly, ll ry) {
        if (qly <= ly && ry <= qry) return t[idx][idy];
        ll my = (ly + ry) / 2;
        ll idly = idy + 1;
        ll idry = idy + 2 * (my - ly + 1);
        if (qry <= my) return queryy(qly, qry, idx, idly, ly, my);
        if (my + 1 <= qly) return queryy(qly, qry, idx, idry, my + 1, ry);
        return f(queryy(qly, qry, idx, idly, ly, my), queryy(qly, qry, idx, idry, my + 1, ry));
    }
    ll query(ll qlx, ll qrx, ll qly, ll qry, ll idx, ll lx, ll rx) {
        if (qlx <= lx && rx <= qrx) return queryy(qly, qry, idx, 1, 0, m - 1);
        ll mx = (lx + rx) / 2;
        ll idlx = idx + 1;
        ll idrx = idx + 2 * (mx - lx + 1);
        if (qrx <= mx) return query(qlx, qrx, qly, qry, idlx, lx, mx);
        if (mx + 1 <= qlx) return query(qlx, qrx, qly, qry, idrx, mx + 1, rx);
        return f(query(qlx, qrx, qly, qry, idlx, lx, mx),
                 query(qlx, qrx, qly, qry, idrx, mx + 1, rx));
    }
    ll query(ll qlx, ll qrx, ll qly, ll qry) {
        return query(qlx, qrx, qly, qry, 1, 0, n - 1);
    }
    void updatey(ll posy, ll val, ll idx, ll lx, ll rx, ll idy, ll ly, ll ry) {
        if (ly == ry) {
            if (lx == rx) t[idx][idy] = val;
            else {
                ll mx = (lx + rx) / 2;
                ll idlx = idx + 1;
                ll idrx = idx + 2 * (mx - lx + 1);
                t[idx][idy] = f(t[idlx][idy], t[idrx][idy]);
            }
        } else {
            ll my = (ly + ry) / 2;
            ll idly = idy + 1;
            ll idry = idy + 2 * (my - ly + 1);
            if (posy <= my) updatey(posy, val, idx, lx, rx, idly, ly, my);
            else updatey(posy, val, idx, lx, rx, idry, my + 1, ry);
            t[idx][idy] = f(t[idx][idly], t[idx][idry]);
        }
    }
    void update(ll posx, ll posy, ll val, ll idx, ll lx, ll rx) {
        if (lx == rx) updatey(posy, val, idx, lx, rx, 1, 0, m - 1);
        else {
            ll mx = (lx + rx) / 2;
            ll idlx = idx + 1;
            ll idrx = idx + 2 * (mx - lx + 1);
            if (posx <= mx) update(posx, posy, val, idlx, lx, mx);
            else update(posx, posy, val, idrx, mx + 1, rx);
            updatey(posy, val, idx, lx, rx, 1, 0, m - 1);
        }
    }
    void update(ll posx, ll posy, ll val) {
        update(posx, posy, val, 1, 0, n - 1);
    }
};
