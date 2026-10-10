ll pref[B];
unordered_map<ll, __int128> dp;
vector<int> primes;
void compute() {
    pref[1] = 1;
    for (int i = 2; i < B; i++) {
        if (pref[i] == 0) {
            pref[i] = i - 1;
            primes.pb(i);
        }
        for (int p : primes) {
            if (i * p >= B) break;
            if (i % p == 0) {
                pref[i * p] = pref[i] * p;
                break;
            } else pref[i * p] = pref[i] * (p - 1);
        }
    }
    for (int i = 1; i < B; i++) pref[i] += pref[i - 1];
}
// Formula:S_f(n) = (1 / g(1)) * (S_f*g(n) - sum( S_f(q) * ( S_g(r) - S_g(l-1) ) )
// q = n/l
// r = n/q
// sum : for(ll l = 2, r; l<=n; l = r+1)
// para f=phi, g=1: phi * 1 = ID
__int128 S_f(ll n) {
    if (n < B) return pref[n];
    if (dp.count(n)) return dp[n];
    __int128 ans = (__int128)n * (n + 1) / 2;
    for (ll l = 2, r; l <= n; l = r + 1) {
        ll q = n / l;
        r = n / q;
        ans -= S_f(q) * (r - l + 1);
    }
    return dp[n] = ans;
}