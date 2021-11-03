#include<bits/stdc++.h>
#define ll long long  
using namespace std;
namespace Min25{
    const int N = 5 + 2e5;//2 * sqrt_n
    const long long mod = 7 + 1e9;
    const long long INV2 = 4 + 5e8;
    bool np[N];
    long long n, w[N];
    int sqrt_n, tot, m, pri[N], id0[N], id1[N];
    int Fp0[N], Fp1[N];
    int g0[N], g1[N];
    long long add(long long x, long long y) { return x + y >= mod ? x - mod + y : x + y; }
    long long sub(long long x, long long y) { return x - y < 0 ? x - y + mod : x - y; }
    long long mul(long long x, long long y) { return (__int128) x * y % mod; }
    long long f(long long p, long long t) { // f(p ^ t)
        //...
        return (p ^ t) % mod;
    }
    void init(int n) {
        tot = 0;
        np[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (!np[i]) {
                pri[++tot] = i;
                //Fp_t = \sum f_t(p)
                Fp0[tot] = add(Fp0[tot - 1], 1);
                Fp1[tot] = add(Fp1[tot - 1], i);
            }
            for (int j = 1; j <= tot && i * pri[j] <= n; j++) {
                np[i * pri[j]] = 1;
                if (i % pri[j] == 0) { break; }
            }
        }
    }
    int get_id(long long x) {
        if (x <= sqrt_n) return id0[x];
        else return id1[n / x];
    }
    void seive_g(long long n) {
        m = 0;
        for (long long i = 1, j; i <= n; i = j + 1) {
            long long k = n / i; j = n / k;
            w[++m] = k;
            if (k <= sqrt_n) id0[k] = m;
            else id1[n / k] = m;
            k %= mod;
            //calc g_t(m) = \sum_{j=2}^w[m]f_t(j)
            long long _w = w[m] % mod;
            g0[m] = sub(_w, 1);
            g1[m] = mul(mul(_w + 1, _w), INV2) - 1;
        }
        for (int i = 1; i <= tot; i++) {
            for (int j = 1; j <= m && 1ll * pri[i] * pri[i] <= w[j]; j++) {
                int id = get_id(w[j] / pri[i]);
                //translation g_t[j]=(g_t[j]-(f_t(p[i])*(g_t[id] - Fp_t[i-1]+MOD)%MOD)%MOD+MOD)%MOD
                g0[j] = sub(g0[j], sub(g0[id], Fp0[i - 1]));
                g1[j] = sub(g1[j], mul(pri[i], sub(g1[id], Fp1[i - 1])));
            }
        }
    }
    long long S(long long x, long long y) {
        if (x <= 1 || pri[y] > x) return 0;
        long long id = get_id(x), res = 0;
        //质数部分:res = g_t[id] - F_p[y - 1]
        res = sub(sub(g1[id], g0[id]), sub(Fp1[y - 1], Fp0[y - 1]));
        for (int i = y; i <= tot && 1ll * pri[i] * pri[i] <= x; i++) {
            long long t0 = pri[i], t1 = 1ll * pri[i] * pri[i];
            for (long long e = 1; t1 <= x; t0 = t1, t1 *= pri[i], e++) {
                long long fp0 = f(pri[i], e), fp1 = f(pri[i], e + 1); // 此处可优化
                res += (fp0 * S(x / t0, i + 1) % mod + fp1) % mod;
                res %= mod;
            }

        }
        return (res + mod) % mod;
    }
    long long solve(long long _n) {
        //f_1 = ...
        n = _n, sqrt_n = sqrt(n) + 1;
        init(sqrt_n); seive_g(n);
        int f_1 = 1;
        return (S(n, 1) + f_1) % mod;
    }
}
const ll mod = 7 + 1e9;
signed main() {
    ll n; cin >> n;
    cout << (Min25 :: solve(n) + (n > 1 ? 2 : 0)) % mod << endl;
}