struct Hashing{
    const int mod = 1e9+9;
    const int p = 367, q = 467;
    int ep[N],eq[N],prp[N],prq[N];

    int P(int a,int b){ return 1ll*a*b%mod;}
    int S(int a,int b){ return (a+b)%mod;}

    void build(string &s){
        int n = s.size();
        ep[0] = eq[0] = 1;
        prp[0] = prq[0] = 0;
        for (int i=1; i<=n; i++){
            prp[i] = S(P(prp[i-1], p), s[i-1]);
            prq[i] = S(P(prq[i-1], q), s[i-1]);
            ep[i] = P(ep[i-1], p);
            eq[i] = P(eq[i-1], q);
        }
    }

    ll substr(int i,int len){ i++;
        ll hp = S(prp[i+len-1], mod-P(prp[i-1], ep[len]));
        ll hq = S(prq[i+len-1], mod-P(prq[i-1], eq[len]));
        return hp*mod + hq;
    }
} H1, H2;