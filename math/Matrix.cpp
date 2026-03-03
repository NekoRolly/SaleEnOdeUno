#define matrix array<array<int, N>, N>
matrix multiply(matrix &a, matrix &b) {
    matrix ans{};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++) ans[i][j] = smod(ans[i][j], mult(a[i][k], b[k][j]));
    return ans;
}
matrix pow(matrix &a, ll e) {
    matrix ans{};
    for (int i = 0; i < N; i++) ans[i][i] = 1;
    while (e) {
        if (e & 1) ans = multiply(ans, a);
        a = multiply(a, a);
        e >>= 1;
    }
    return ans;
}
