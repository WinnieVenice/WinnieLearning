# BA-String

https://codeforces.com/contest/1620/problem/C

## 题面

定义只包含‘a’,’b’串的字符串,称为BA-字符串.给定一个长度为n的字符串s,只包含‘a’,’\*’.其中每个‘\*’需要替换成[0,k]个‘b’.问该字符串经过替换后的所有BA-字符串中字典序第x小的串是什么.

## 做法       

显然连续的‘\*’的可以缩成一个,那么类似于康托展开,从左到右,第i个位置的‘b’的个数是$x_i/suffer\_prod_i$ ,其中x_i表示到达第i个位置的时候x的值,$suffer\_prod_i$表示每个位置‘b’数量的后缀积. 

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

