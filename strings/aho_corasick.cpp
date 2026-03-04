struct Aho_Corasick{
    int t[N][K],cur;
    int pa[N],go[N][K],lnk[N];
    queue<int> qu;

    int insert(string &s){
        int u = 0;
        for (char &c : s){
            int k = c-'a';
            if (t[u][k] == 0)
                t[u][k] = ++cur, pa[cur] = u;
            u = t[u][k];
        }
        return u;
    }

    void bfs(){
        fill(lnk+1, lnk+cur+1, -1);
        for (qu.push(0); !qu.empty(); ){
            int u = qu.front(); qu.pop();
            for (int k=0; k<K; k++){
                int v = t[u][k];
                if (v == 0) go[u][k] = go[lnk[u]][k];
                else{
                    lnk[v] = u == 0 ? 0 : go[lnk[u]][k];
                    go[u][k] = t[u][k];
                    qu.push(v);
                }
            }
        }
    }
} aho; // by NekoRolly