struct Line{
    ll m,b;
    
    ll y(ll x){ return m*x+b;}
};

struct Convex_Hull_Trick{
    vector<Line> vec;
    int l = 0;
    
    bool check(int i){
        double x1 = double(vec[i-1].b - vec[i+1].b)/(vec[i+1].m - vec[i-1].m);
        double x2 = double(vec[i].b - vec[i+1].b)/(vec[i+1].m - vec[i].m);
        return x1 >= x2;
    }
    
    void add(Line L){
        vec.push_back(L);
        while (vec.size() >= 3 && check(vec.size()-2))
            vec.erase(vec.end()-2);
        l = min(l, int(vec.size()-1));
    }
    
    ll query(ll x){ // O(1) amortizado
        while (l+1 < vec.size() && vec[l].y(x) > vec[l+1].y(x)) l++; 
        return vec[l].y(x);
    }

    ll find(ll x){ // O(logn)
        int l = 0, r = vec.size();
        while (l+1 < r){
            int m = (l+r)>>1;
            if (vec[m-1].y(x) > vec[m].y(x)) l = m;
            else r = m;
        }
        return vec[l].y(x);
    }
} cht; // by NekoRolly