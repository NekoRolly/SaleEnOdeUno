// A(DP) X G_STATIC
// Ecuación: dp[i] += c[i] * sum_{j} (A[j] * G[i - j - off])
void dfs_AG(int l, int r, int offset, vector<int> &dp, vector<int> &A, const vector<int> &G,
            const vector<int> &c) {
    if (l == r) {
        // Aqui ya esta calculado dp[i] = sum_{j} (A[j] * G[i - j - off]) y dp[j]
        // para j < i ya esta calculado
        dp[l] = mult(dp[l], c[l]);
        A[l] = mult(l, dp[l]);
        return;
    }
    int mid = (l + r) >> 1;
    dfs_AG(l, mid, offset, dp, A, G, c);
    vector<int> a(A.begin() + l, A.begin() + mid + 1);
    vector<int> b(G.begin(), G.begin() + max(0, r - l - offset + 1));
    vector<int> conv = convolution(a, b);
    for (int i = max(mid + 1, l + offset); i <= min(r, (int)conv.size() + l + offset - 1); i++)
        dp[i] = smod(dp[i], conv[i - l - offset]);
    dfs_AG(mid + 1, r, offset, dp, A, G, c);
}

// A(DP) X A(DP)
// Ecuación Simétrica: dp[i] = c[i] * sum_{j} (A[j] * A[i - j - off]) + g[i]
// Ejemplo de dependencia: A[i] = i * dp[i]
void dfs_sim(int l, int r, int offset, vector<int> &dp, vector<int> &A, const vector<int> &c,
             const vector<int> &g) {
    if (l == r) {
        dp[l] = smod(mult(c[l], dp[l]), g[l]);
        A[l] = mult(l, dp[l]);
        return;
    }
    int mid = (l + r) >> 1;
    dfs_sim(l, mid, offset, dp, A, c, g);
    vector<int> a(A.begin() + l, A.begin() + mid + 1);
    vector<int> b =
        (l == 0) ? a : vector<int>(A.begin(), A.begin() + max(0, r - l - offset + 1));
    vector<int> conv = convolution(a, b);
    for (int i = max(mid + 1, l + offset); i <= min(r, (int)conv.size() + l + offset - 1); i++)
        dp[i] = smod(dp[i], mult(conv[i - l - offset], 2 - !l));
    dfs_sim(mid + 1, r, offset, dp, A, c, g);
}

// A(DP) X B(DP)
// Ecuación: dp[i] += c[i] * sum_{j} (A[j] * B[i - j - off])
// A[i] = i * dp[i]
// B[i] = sum_{k=0}^{i} dp[k] (Suma prefija)
void dfs_gen(int l, int r, int offset, vector<int> &dp, vector<int> &A, vector<int> &B,
             const vector<int> &c) {
    if (l == r) {
        dp[l] = mult(dp[l], c[l]); // dp[l] = c[i] * sum_{j} (A[j] * B[i - j - off])
        A[l] = mult(l, dp[l]);
        B[l] = smod((l > 0) ? B[l - 1] : 0, dp[l]);
        return;
    }
    int mid = (l + r) >> 1;
    dfs_gen(l, mid, offset, dp, A, B, c);
    vector<int> a1(A.begin() + l, A.begin() + mid + 1);
    vector<int> b1(B.begin(), B.begin() + max(0, r - l - offset + 1));
    vector<int> conv1 = convolution(a1, b1);
    for (int i = max(mid + 1, l + offset); i <= min(r, (int)conv1.size() + l + offset - 1);
         i++)
        dp[i] = smod(dp[i], conv1[i - l - offset]);
    if (l > 0) {
        vector<int> a2(B.begin() + l, B.begin() + mid + 1);
        vector<int> b2(A.begin(), A.begin() + max(0, r - l - offset + 1));
        vector<int> conv2 = convolution(a2, b2);
        for (int i = max(mid + 1, l + offset); i <= min(r, (int)conv2.size() + l + offset - 1);
             i++)
            dp[i] = smod(dp[i], conv2[i - l - offset]);
    }
    dfs_gen(mid + 1, r, offset, dp, A, B, c);
}