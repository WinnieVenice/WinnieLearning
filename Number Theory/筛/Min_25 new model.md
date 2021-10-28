# Min_25 new model

```c++
#include<bits/stdc++.h>
using namespace std;
namespace Min25{
    const int N = 5 + 2e5;//2 * sqrt_n
    const long long mod = 7 + 1e9;
    int sqrt_n;
    long long f(long long p, long long t) { // f(p ^ t)
        //...
    }
    void init(int n) {
        tot = 0;
        np[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (!np[i]) { np[i] = 1; pri[++tot] = i; }
            for (int j = 1, val = i * pri[j]; j <= tot && val <= n; j++) {
                np[val] = 1;
                if (i % pri[j] == 0) { break; }
            }
        }
    }
    int get_id(long long x) {
        if (x <= sqrt_n) return id0[x];
        else return id1[n / x];
    }
    void sieve_g(long long n) {
        m = 0;
        for (long long i = 1, j; i <= n; i = j + 1) {
            long long k = n / i; j = n / k;
            w[++m] = k;
            if (k <= sqrt_n) id0[k] = m;
            else id1[n / k] = m;
            k %= mod;
            //calc g_t(m) = \sum_{j=2}^w[m]f_t(j)
        }
        for (int i = 1; i <= tot; i++) {
            for (int j = 1; j <= m && 1ll * pri[i] * pri[i] <= w[j]; j++) {
                int id = get_id(w[j] / pri[i]);
                //translation g_t[j]=(g_t[j]-(f_t(p[i])*(g_t[op]-sum_t[i-1]+MOD)%MOD)%MOD+MOD)%MOD
            }
        }
    }
    long long S(long long x, long long y) {
        if (x <= 1 || pri[y] > x) return 0;
        long long id = get_id(x), res = 0;
        //质数部分:res = g_t[id] - F_p[y - 1]
        for (int i = y; i <= tot && 1ll * pri[i] * pri[i] <= x; i++) {
            long long t0 = pri[i], t1 = pri[i] * pri[i];
            for (long long e = 1; t1 <= x; t0 = t1, t1 *= pri[i], e++) {
                long long fp0 = f(pri[i], e), fp1 = f(pri[i], e + 1); // 此处可优化
                res += (fp0 * S(x / t0, i + 1) % mod + fp1) % mod;
                res %= mod;
            }

        }
        return res;
    }
    long long solve(long long n) {
        //f_1 = ...
        return (S(n, 1) + f_1) % mod;
    }
}
signed main() {
    
}
```

