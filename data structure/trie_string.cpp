struct Trie{
    int t[N][K],sz[N],cur;

    void insert(string &s){
        int u = 0; sz[u]++;
        for (char &c : s){
            int k = c-'a';
            if (t[u][k] == 0) t[u][k] = ++cur;
            u = t[u][k], sz[u]++;
        }
    }

    void erase(string &s){
        int u = 0; sz[u]--;
        for (char &c : s){
            int k = c-'a';
            u = t[u][k], sz[u]--;
        }
    }
} tr; // by NekoRolly