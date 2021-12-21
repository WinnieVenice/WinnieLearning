# BA-String

https://codeforces.com/contest/1620/problem/C

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
    int _; cin >> _;
    for (; _--; ) {
        int n, k, x; cin >> n >> k >> x;
        string s; cin >> s;
        s = 'a' + s + 'a';
        vector<int> f(n + 2, 0);
        f[n + 1] = 1;
        for (int i = n; i >= 0; i--) {
            if (s[i] == 'a') {
                for (int j = i + 1; j <= n + 1; j++) {
                    if (s[j] == 'a') {
                        if (1.0 * f[j] * ((j - i - 1) * k + 1) <= 1e18) {
                            f[i] = f[j] * ((j - i - 1) * k + 1);
                        }
                        break;
                    }
                }
            }
        }
        for (int i = 0; i <= n; i++) {
            if (s[i] == 'a') {
                if (i) cout << 'a';
                for (int j = i + 1; j <= n + 1; j++) {
                    if (s[j] == 'a') {
                        if (!f[j]) break;
                        for (int u = (x - 1) / f[j]; u; u--) cout << 'b';
                        x = (x - 1) % f[j] + 1;
                        break;
                    }
                }
            }
        }
        cout << endl;
    }

}
```

