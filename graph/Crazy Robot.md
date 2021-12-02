# Crazy Robot



https://codeforces.com/contest/1613/problem/E

## 题目

$$

$$

## 做法

$$
\\ 简单的转换,对于一个[.]我们能将他周围的一个[.]变为不可达
\\ 考虑一个[.]能到达终点: 如果一个[.]周围只有一个[.]和若干个[+],那么显然该机器人能到达终点
\\ 不难知道最开始能到达终点的就是[L],因此通过bfs,每次检查中心的点,更新答案
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
const int mod = 998244353;
const int N = 5 + 1e6;
string s[N];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
int n, m;
bool ck(int x, int y) {
    return x < 0 || x >= n || y < 0 || y >= m;
}
int d[N];
bool vis[N];
void check(int x, int y) {
    int u = x * m + y;
    d[u] = 4;
    for (int i = 0; i < 4; i++) {
        int cx = x + dx[i], cy = y + dy[i];
        if (ck(cx, cy) || s[cx][cy] == '#' || s[cx][cy] == 'L' || s[cx][cy] == '+') {
            d[u]--;
        }
    }
}
signed main() {
    int _; cin >> _;
    while (_--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> s[i];
        queue<int> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (s[i][j] == 'L') q.push(i * m + j);
            }
        }
        for (int i = 0; i <= n * m; i++) vis[i] = 0;
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            int x = u / m, y = u % m;
            for (int i = 0; i < 4; i++) {
                int cx = x + dx[i], cy = y + dy[i];
                if (ck(cx, cy) || s[cx][cy] == '#' || s[cx][cy] == 'L' || vis[cx * m + cy]) continue;
                check(cx, cy);
                if (d[cx * m + cy] <= 1) {
                    s[cx][cy] = '+';
                    q.push(cx * m + cy);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            cout << s[i] << endl;
        }
    }    
}
```

