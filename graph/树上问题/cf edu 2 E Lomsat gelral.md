# cf edu 2 E Lomsat gelral

## 题意

$$
\\ 给定一棵根为1的树, 节点编号为[1,n],每个节点的颜色为c_i.
\\ 求每个节点以其为根的子树的出现次数最多的不同颜色的和
$$

## Code

### 做法1 dsu on tree

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
int n;
int c[N];
vector<int> G[N];
int son[N], sz[N];
void dfs0(int x, int f) {
    sz[x] = 1; son[x] = 0;
    for (auto v: G[x]) {
        if (v != f) {
            dfs0(v, x);
            sz[x] += sz[v];
            if (sz[son[x]] < sz[v]) son[x] = v;
        }
    }
}
map<int, int> mp;
int mx, sum, Son;
int ans[N];
void add(int x, int f) {
    mp[c[x]]++;
    if (mx <= mp[c[x]]) {
        if (mx < mp[c[x]]) {
            mx = mp[c[x]]; sum = 0;
        }
        sum += c[x];
    }
    for (auto &v: G[x]) {
        if (v != f && v != Son) add(v, x);
    }
}
void dfs(int x, int f, int T, int hson) {
    if (T) {
        for (auto &v: G[x]) {
            if (v != f && v != son[x]) dfs(v, x, 1, 0);
        }
    }
    if (son[x] && son[x] != f) {
        dfs(son[x], x, 1, 1);
        Son = son[x];
    }
    add(x, f);
    Son = 0;
    if (T) ans[x] = sum;
    if (T && !hson) mp.clear(), sum = 0, mx = 0;   
}
signed main() {
    ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) { cin >> c[i]; }
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }    
    dfs0(1, 0);
    dfs(1, 0, 1, 1);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}
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
struct T {
    int l, r, mx, sum;
};
const int N = 5 + 1e5;
int n;
int c[N];
vector<int> G[N];
int tot, rt[N];
T st[1 << 21];
void pb(int &x, int &l, int &r) { 
    st[x].mx = max(st[l].mx, st[r].mx);
    int res = 0;
    if (st[x].mx == st[l].mx) res += st[l].sum;
    if (st[x].mx == st[r].mx) res += st[r].sum;
    st[x].sum = res;
}
void upd(int &x, int l, int r, int p) {
    if (!x) x = ++tot;
    if (l == r) {
        st[x].mx++;
        st[x].sum = l;
        return;
    }
    int mid = l + r >> 1;
    if (p <= mid) upd(st[x].l, l, mid, p);
    else upd(st[x].r, mid + 1, r, p);
    pb(x, st[x].l, st[x].r);    
}
int merge(int u, int v, int l, int r) {
    if (!u || !v) return u + v;
    if (l == r) {
        st[u].mx = st[u].mx + st[v].mx;
        return u;
    }
    int mid = l + r >> 1;
    st[u].l = merge(st[u].l, st[v].l, l, mid); 
    st[u].r = merge(st[u].r, st[v].r, mid + 1, r);
    pb(u, st[u].l, st[u].r);
    return u;
}
int ans[N];
void dfs(int x, int f) {
    for (auto v: G[x]) {
        if (v != f) {
            dfs(v, x);
            rt[x] = merge(rt[x], rt[v], 1, n);
        }
    }
    upd(rt[x], 1, n, c[x]);
    ans[x] = st[rt[x]].sum;   
}
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }    
    dfs(1, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << endl;
}
```

