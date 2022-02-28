#  倍增LCA

```C++
void dfs(int u, int fa) {	//init
    dp[u] = dp[fa] + 1;
    for (int i = 1; (1 << i) <= dp[u]; i++) {
        f[i][u] = f[i - 1][f[i - 1][u]]; 
    }
    for (auto &v: G[u]) {
        if (v == fa) continue;
        f[0][v] = u;
        dfs(v, u);
    }
}
int lca(int x, int y) {
    if (dp[x] < dp[y]) std::swap(x, y);
    for (int i = 20; i >= 0; i--) {
        if (f[i][x] != f[i][y]) {
            x = f[i][x]; y = f[i][y];
        }
    }
    return f[0][x];
}

```

