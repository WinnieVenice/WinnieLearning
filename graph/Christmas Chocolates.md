# Christmas Chocolates

https://codeforces.com/contest/1617/problem/E

## 题面



## 做法



## Code

```C++

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LL __int128
using namespace std;
int qpow(int a, int b, int p) {int ret = 1; for(a %= p; b; b >>= 1, a = a * a % p) if(b & 1) ret = ret * a % p; return ret; }
int qpow(int a,int b) {int ret = 1; for(; b; b >>= 1, a *= a) if(b & 1) ret *= a; return ret; }
int gcd(int x,int y) {return y ? gcd(y, x % y) : x; }
pair<int,int> exgcd(int a,int b) { if(!b) return {1, 0}; pair<int,int> ret = exgcd(b, a % b); return {ret.second, ret.first - a / b * ret.second }; }
int lcm(int x,int y){ return x / gcd(x, y) * y; }

signed main() {
    ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
    vector<int> fac2 = {1};
    for (int i = 1; i < 32; i++) fac2.push_back(fac2.back() << 1);
    int n; cin >> n;
    vector<int> a(n + 1);
    unordered_map<int, int> id;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        id[a[i]] = i;
    }
    unordered_map<int,vector<int>> G;
    for (int i = 1; i <= n; i++) {
        for (int u = a[i], v = (*lower_bound(fac2.begin(), fac2.end(), u)) - u; u; u = v, v = (*lower_bound(fac2.begin(), fac2.end(), u)) - u) {
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }
    unordered_map<int, int> d;
    function<pair<int, int>(int, int, int)> dfs = [&](int x, int y, int z) {
        if (d[x]) return make_pair(x, d[x]); 
        pair<int, int> res = make_pair(x, d[x] = z);
        for (auto v: G[x]) {
            if (v != y) {
                auto u = dfs(v, x, z + 1);
                if (id[u.first] && u.second > res.second) res = u;
            }
        }
        return res;
    };
    auto [x, tmp] = dfs(0, -1, 0);
    d.clear();
    auto [y, dep] = dfs(x, -1, 0);
    cout << id[x] << " " << id[y] << " " << dep << endl;
}
```

