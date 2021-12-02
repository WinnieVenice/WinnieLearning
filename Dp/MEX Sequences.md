# MEX Sequences

https://codeforces.com/contest/1613/problem/D

## 题意

$$

$$

## 做法

$$
\\ 001122+(2/3/4) \leftarrow 非下降状态 \leftarrow 状态0
\\ 00112244+(2) \leftarrow 上下抖,向下 \leftarrow 状态1
\\ 0011224422+(4) \leftarrow 上下抖,向上 \leftarrow 状态2
\\ 因此一个序列有3种状况
\\ 考虑dp[x][0/1/2]表示a_i=x时且序列状态为0/1/2时的方案数
\\ 考虑转移:
\\ f[x][0]\rightarrow f[x][0],f[x-1][0]\rightarrow f[x][0]
\\ f[x][1]\rightarrow f[x][1],f[x+2][2]\rightarrow f[x][1]
\\ f[x][2]\rightarrow f[x][2],f[x-2][0]\rightarrow f[x][2],f[x-2][1]\rightarrow f[x][2]
\\ 考虑边界状态:
\\ f[x][0]=1,x=0
$$

## Code

```C++
#include<bits/stdc++.h>
#define LL __int128
#define endl '\n'
#define int long long 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b,ll p){a%=p; ll ret=1;for(;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p; return ret;}
ll qpow(ll a,ll b){ll ret=1; for(;b;b>>=1,a*=a) if(b&1) ret*=a; return ret;}
ll getInv(ll x,ll p){return qpow(x,p-2,p);}
const int mod = 998244353;
int add(int x, int y) {
    x += y; if (x >= mod) x-= mod;
    return x;
}
const int N = 5 + 5e5;
int f[N][3];

signed main(){
    int _; cin >> _;
    while (_--) {
        int n; cin >> n;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < 3; j++) {
                f[i][j] = 0;
            }
        }
        for (int i = 1; i <= n; i++) {
            int x; cin >> x;
            f[x][0] = add(f[x][0], f[x][0]);
            if (!x) { f[x][0] = add(f[x][0], 1); }
            else { f[x][0] = add(f[x][0], f[x - 1][0]); }
            f[x][2] = add(f[x][2], f[x][2]);
            if (x == 1) { f[x][2] = add(f[x][2], 1); }
            else if (x > 1) { 
                f[x][2] = add(f[x][2], f[x - 2][0]);
                f[x][2] = add(f[x][2], f[x - 2][1]);    
            }
            f[x][1] = add(f[x][1], f[x][1]);
            if (x + 2 <= n) f[x][1] = add(f[x][1], f[x + 2][2]);
        }
        int ans = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < 3; j++) {
                ans = add(ans, f[i][j]);
            }
        }
        cout << ans << endl;
    }
}
```

