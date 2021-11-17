# cf edu 2 E Lomsat gelral

## 题意

$$
\\ 给定一棵根为1的树, 节点编号为[1,n],每个节点的颜色为c_i.
\\ 求每个节点以其为根的子树的出现次数最多的不同颜色的和
$$

## Code

### 做法1 dsu on tree

```c++

```

### 做法2 dfs序+分治

$$

$$



```c++
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
const int N = 5 + 1e5;
int c[N];
vector<int> G[N];
int sz[N], tot, dfn[N], idx[N];
void dfs(int x, int f) {
    sz[x] = 1;
    dfn[x] = ++tot; idx[tot] = x;
    for (auto &v: G[x]) {
        if (v != f) {
            dfs(v, x);
            sz[x] += sz[v];
        }
    }
}
map<int, int> mp;
int mx, sum;
void add(int x) {
    mp[c[idx[x]]]++;
    if (mx <= mp[c[idx[x]]]) {
        if (mx < mp[c[idx[x]]]) { mx = mp[c[idx[x]]]; sum = 0; }
        sum += c[idx[x]]; 
    }
}
int ans[N];
void solve(int l, int r) {
    if (l == r) {
        ans[idx[l]] = c[idx[l]];
        return;
    }
    int mid = l + r >> 1;
    solve(l, mid); solve(mid + 1, r);
    mp.clear(); mx = 0; sum = 0;
    for (int i = mid, j, p = mid; l <= i && (j = i + sz[idx[i]] - 1) <= r; i--) {
        add(i);
        if (j <= mid) continue; 
        while (p < j) add(++p);
        ans[idx[i]] = sum;
    }
}
signed main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }    
    dfs(1, 0);
    solve(1, n);
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << endl;
}
```

### 做法3 线段树合并

$$

$$

```c++

```

