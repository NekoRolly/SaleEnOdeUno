struct Trie{
    int t[N*B][2],sz[N*B];
    int cur;

    void insert(int x){
        int u = 0; sz[u]++;
        for (int i=B-1; i>=0; i--){
            int k = x>>i&1;
            if (t[u][k] == 0) t[u][k] = ++cur;
            u = t[u][k], sz[u]++;
        }
    }

    void erase(int x){
        int u = 0; sz[0]--;
        for (int i=B-1; i>=0; i--){
            int k = x>>i&1;
            u = t[u][k], sz[u]--;
        }
    }

    int get_min(int x){ // min xor
        int u = 0, ans = 0;
        for (int i=B-1; i>=0; i--){
            int k = x>>i&1;
            if (t[u][k] != 0 && sz[t[u][k]] > 0) u = t[u][k];
            else u = t[u][k^1], ans ^= 1<<i;
        }
        return ans;
    }

    int get_max(int x){ // max xor
        int u = 0, ans = 0;
        for (int i=B-1; i>=0; i--){
            int k = x>>i&1;
            if (t[u][k^1] != 0 && sz[t[u][k^1]] > 0)
                u = t[u][k^1], ans ^= 1<<i;
            else u = t[u][k];
        }
        return ans;
    }
} tr; // by NekoRolly