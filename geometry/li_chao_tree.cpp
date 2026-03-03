struct Line{
    ll m,b;
    
    ll y(ll x){ return m*x+b;}
};

struct Li_Chao_Tree{
    Line t[N*4];

    void update(int id,int l,int r,Line L){
        if (l+1 == r || t[id].b == -infll){
            if (L.y(l) > t[id].y(l)) t[id] = L;
            return;
        }
        int m = (l+r)>>1;
        if (t[id].y(m) < L.y(m)) swap(t[id], L);
        if (t[id].m > L.m) update(id<<1, l, m, L);
        else update(id<<1|1, m, r, L);
    }

    ll query(int id,int l,int r,ll x){
        if (l+1 == r) return t[id].y(x);
        int m = (l+r)>>1;
        if (x < m) return max(t[id].y(x), query(id<<1, l, m, x));
        else return max(t[id].y(x), query(id<<1|1, m, r, x));
    }
} lct; // by NekoRolly