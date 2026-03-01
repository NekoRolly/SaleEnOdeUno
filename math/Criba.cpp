bool criba[MX];
ll primerfactor[MX], phi[MX];
// criba para primerfactor, phi O(nlog(log(n)))
void completar() {
    for (int i = 0; i < MX; i++) {
        criba[i] = 1;
        primerfactor[i] = i;
        phi[i] = i;
    }
    criba[0] = 0;
    criba[1] = 0;
    for (ll i = 2; i < MX; i++) {
        if (criba[i]) {
            phi[i]--;
            for (ll j = 2 * i; j < MX; j += i) {
                criba[j] = 0;
                phi[j] -= phi[j] / i;
                if (primerfactor[j] == j) primerfactor[j] = i;
            }
        }
    }
}
vector<pll> factorizacioncriba(ll n) { // O(log(n))
    vector<pll> ans;
    while (n > 1) {
        ll f = primerfactor[n];
        ll pot = 0;
        while (primerfactor[n] == f) {
            n /= f;
            pot++;
        }
        ans.pb({f, pot});
    }
    return ans;
}
vector<ll> divisorescriba(ll n) { // O(d(x))
    vector<ll> fact = {1};
    while (n > 1) {
        ll f = primerfactor[n];
        ll sz = fact.size();
        ll divisor = 1;
        while (n % f == 0) {
            divisor *= f;
            n /= f;
            rep(i, sz) fact.pb(fact[i] * divisor);
        }
    }
    return fact;
}
