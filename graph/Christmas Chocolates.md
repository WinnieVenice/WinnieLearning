# Christmas Chocolates

https://codeforces.com/contest/1617/problem/E

## 题面

给定n个数$\{a_i\}$,你有这样一种操作:选择某个下标i的数$a_i$和一个非负整数k,使得$a_i=2^k-a_i$,要求$2^k\geq a_i$.这样的操作你可以执行任意次,问$\{a_i\rightarrow a_j\}$的解集中,最少操作次数的最大是多少?注意,$a_i\rightarrow a_j$过程的每一步操作都是都是使它的操作次数尽可能少的.

## 做法

考虑$z=2^k-x$中不同k对z的影响.不妨假设$x=(1011010)_2$,那么$k\geq8$.

$k=8,z=(0100110)_2$,不难看出z的实际变位的是从右到左第一个1的左边到最高位按位取反,保留第一个1.

$k=9,z=2^8+(2^8-x)=2^8+(0100110)_2$
$$
\\\begin{align}
\\ k>8,z&=2^{k-1}+2^{k-2}+\dots+2^8+(2^8-x)
\\ &=2^{k-1}+2^{k-2}+\dots+2^8+(0100110)_2
\\\end{align}
$$






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

