const int MOD = 998244353;
struct mint {
    int v;
    mint(long long x = 0) : v(x % MOD) {
        if (v < 0) v += MOD;
    }
    mint operator+(mint o) const {
        return v + o.v >= MOD ? v + o.v - MOD : v + o.v;
    }
    mint operator-(mint o) const {
        return v - o.v < 0 ? v - o.v + MOD : v - o.v;
    }
    mint operator*(mint o) const {
        return 1LL * v * o.v % MOD;
    }
    mint pow(long long k) const {
        mint res = 1, base = *this;
        while (k) {
            if (k & 1) res = res * base;
            base = base * base;
            k >>= 1;
        }
        return res;
    }
    mint inv() const {
        return pow(MOD - 2);
    }
};

struct BM {
    vector<mint> base, c;
    // O(N^2) - Obtiene la recurrencia
    BM(vector<mint> s) : base(s) {
        int n = s.size(), L = 0, m = 0;
        vector<mint> C(n, 0), B(n, 0), T;
        C[0] = B[0] = 1;
        mint b = 1;
        for (int i = 0; i < n; i++) {
            m++;
            mint d = s[i];
            for (int j = 1; j <= L; j++) d = d + C[j] * s[i - j];
            if (d.v == 0) continue;
            T = C;
            mint coef = d * b.inv();
            for (int j = m; j < n; j++) C[j] = C[j] - coef * B[j - m];
            if (2 * L > i) continue;
            L = i + 1 - L, B = T, b = d, m = 0;
        }
        c.assign(C.begin() + 1, C.begin() + L + 1);
        for (mint &x : c) x = mint(0) - x;
    }

    // O(L^2 log K) - Obtiene el k-ésimo término
    mint get(long long k) {
        int n = c.size();
        if (k < base.size()) return base[k];
        if (n == 0) return 0;
        auto combine = [&](vector<mint> A, vector<mint> B) {
            vector<mint> res(2 * n + 1, 0);
            for (int i = 0; i <= n; i++)
                for (int j = 0; j <= n; j++) res[i + j] = res[i + j] + A[i] * B[j];
            for (int i = 2 * n; i > n; i--)
                for (int j = 0; j < n; j++) res[i - 1 - j] = res[i - 1 - j] + res[i] * c[j];
            res.resize(n + 1);
            return res;
        };
        vector<mint> pol(n + 1, 0), e(n + 1, 0);
        pol[0] = 1;
        if (n > 0) e[1] = 1;
        k++;
        while (k) {
            if (k & 1) pol = combine(pol, e);
            e = combine(e, e);
            k >>= 1;
        }
        mint res = 0;
        for (int i = 0; i < n; i++) res = res + pol[i + 1] * base[i];
        return res;
    }
};