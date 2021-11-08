# Phi(n)

## Solution

$$
F(n) = \sum_{i=1}^n \phi(i)
\\\because ID(n)=\sum_{d|n}\phi(d)=\phi*1=1*\phi=\sum_{d|n}\phi(n/d)
\\\Rightarrow \phi(n)=ID(n)-\sum_{d|n,d>1}\phi(d)
\\\therefore F(n)=\sum_{i=1}^n\phi(i)=\sum_{i=1}^n ID(i)-\sum_{i=1}^n\sum_{d|i,d>1}\phi(d)
\\=\frac{n(n+1)}{2}-\sum_{i=1}^n\sum_{d=2}^{n}[d|i]\phi(d)
\\=\frac{n(n+1)}{2}-\sum_{d=2}^{n}\phi(d)\sum_{i=1}^n[d|i]
\\=\frac{n(n+1)}{2}-\sum_{d=2}^{n}\phi(d)\lfloor\frac{n}{d}\rfloor
\\=\frac{n(n+1)}{2}-\sum_{l=2,r=n/(n/l)}^{l\leq n}{\phi(n/l)(r-l+1)}
$$

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
const long long mod = 7 + 1e9;
const int N = 5 + 1e6; //sqrt_n~n^{2/3}
bool np[N];
int tot, pri[N];
int phi[N];
void seive(int n) {
    np[1] = 1;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!np[i]) {
            pri[++tot] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= tot && i * pri[j] <= n; j++) {
            np[i * pri[j]] = 1;
            if (i % pri[j] == 0 ){
                phi[i * pri[j]] = 1ll * phi[i] * pri[j] % mod;
                break;
            }
            phi[i * pri[j]] = 1ll * phi[i] * (pri[j] - 1) % mod;
        }
    }
    for (int i = 2; i <= n; i++) {
        phi[i] = (1ll * phi[i] + phi[i - 1]) % mod;
    }
}
int sqrt_n;
unordered_map<long long, int> s_p;
int djs_phi(long long x) {
    if (x < sqrt_n) return phi[x];
    if (s_p[x]) return s_p[x];
    int res = 1ll * x * (x + 1) / 2 % mod;
    for (long long l = 2, r; l <= x; l = r + 1) {
        long long d = x / l; r = x / d;
       	res = (1ll * res - (r - l + 1) * djs_phi(d) % mod) % mod;
    }
    return s_p[x] = res;
}
signed main(){
    seive(N - 1);
    long long n; cin >> n;
    cout << djs_phi(n) << endl;
}
```

