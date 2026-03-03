void z_function(string &s,int zf[]){
    int n = s.size();
    for (int i=1,l=0,r=0; i<n; i++){
        if (i < r) zf[i] = min(zf[i-l], r-i);
        while (i+zf[i] < n && s[i+zf[i]] == s[zf[i]]) zf[i]++;
        if (i+zf[i] > r) l = i, r = i+zf[i];
    }
} // by NekoRolly