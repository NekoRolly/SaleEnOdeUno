void prefix_function(string &s,int pf[]){
    int n = s.size(); pf[0] = 0;
    for (int i=1; i<n; i++){
        int j = pf[i-1];
        while (j>0 && s[j] != s[i]) j = pf[j-1];
        pf[i] = j + (s[i] == s[j]);
    }
} // by NekoRolly