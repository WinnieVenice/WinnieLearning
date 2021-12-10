# Steadily Growing Steam

2021ICPC上海站I

## 题面

给定n张卡牌，每张卡牌有点数t和利益v，有一次操作：选m张卡牌使其点数翻倍。现在将这n张卡牌分成两堆S、T（但不要求n张都要选，即：$S\cup T=\{1,2,\dots,n\}$不是必须的），要求两堆的点数和相同，即：$\sum_{i\in S}t_i=\sum_{j\in T}t_j$，问满足条件的两堆的利益和最大是多少？即：$max\{\sum_{i\in S}v_i+\sum_{j\in T}v_j\}$

$1\leq n\leq 100,0\leq k\leq n,|v_i|\leq10^9,1\leq t_i\leq 13$

## 做法

对于每张牌有3种状态：选进S，选进T，不选。有点像01背包，考虑dp：

$dp[i][j]:表示考虑到第i张牌,当前点数为j的最大利益$

考虑转移:
$$
\\ dp[i][j]\leftarrow max\{dp[i-1][j-t_i]+v_i\}，选进S
\\ dp[i][j]\leftarrow max\{dp[i-1][j+t_i]+v_i\}，选进T
\\ dp[i][j]\leftarrow max\{dp[i-1][j]\}，不选
$$
再考虑操作:

$dp[i][j][k]:表示考虑到第i张牌，当前点数为j，已经操作了k张牌的最大利益$

考虑转移：
$$
\\ dp[i][j][k]\leftarrow max\{dp[i-1][j-t_i][k]+v_i\},选进S,不进行操作
\\ dp[i][j][k]\leftarrow max\{dp[i-1][j+t_i][k]+v_i\}，选进T，不进行操作
\\ dp[i][j][k]\leftarrow max\{dp[i-1][j][k]\}，不选，不进行操作
\\ dp[i][j][k]\leftarrow max\{dp[i-1][j-2t_i][k-1]+v_i\}，选进S,进行操作
\\ dp[i][j][k]\leftarrow max\{dp[i-1][j+2t_i][k-1]+v_i\}，选进T，不进行操作
$$
那么$ans=max_{k=0}^m\{dp[n][0][k]\}$，由于j不能是负数，所以考虑偏移即可

另外，显然可以把i这一维滚动优化	

事实上可以多一条转移：$dp[i][j][k]\leftarrow dp[i-1][j][k-1]$，那么$ans=dp[n][0][m]$	

## Code

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

int v[105], t[105];
int dp[2][6005][105];
signed main() {
    int lim = 3000;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) { cin >> v[i] >> t[i]; }
    memset(dp, -0x3f, sizeof(dp));
    dp[0][lim][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0 + lim; j <= lim + lim; j++) {
            for (int k = 0; k <= m; k++) {
                dp[i & 1][j][k] = dp[(i - 1) & 1][j][k];
                if (k > 0) {
                    dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[(i - 1) & 1][j][k - 1]);
                }
                dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[(i - 1) & 1][j - t[i]][k] + v[i]);
                if (k > 0) {
                    dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[(i - 1) & 1][j - 2 * t[i]][k - 1] + v[i]);
                }
                dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[(i - 1) & 1][j + t[i]][k] + v[i]);
                if (k > 0) {
                    dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[(i - 1) & 1][j + 2 * t[i]][k - 1] + v[i]);
                }
            }
        }
    }
    cout << dp[n & 1][lim][m] << endl;
}
```

