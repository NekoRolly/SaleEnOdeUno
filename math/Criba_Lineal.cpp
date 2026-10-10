int spf[MX];
int mu[MX];
int phi[MX];
vector<int> primes;
void compute() {
    spf[1] = mu[1] = phi[1] = 1;
    for (int i = 2; i < MX; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            mu[i] = -1;
            phi[i] = i - 1;
            primes.pb(i);
        }
        for (int p : primes) {
            if (p > spf[i] || i * p >= MX) break;
            spf[i * p] = p;
            if (p == spf[i]) {
                mu[i * p] = 0;
                phi[i * p] = phi[i] * p;
            } else {
                mu[i * p] = -mu[i];
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
}