static mt19937 rng(chrono::steady_clock::now()
    .time_since_epoch().count());
#define rnd(a,b) (uniform_int_distribution<ll>(a,b)(rng))