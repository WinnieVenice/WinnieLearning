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
    std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
    const int N = 5 + 2e6;
    std::vector<int> d1(N, 1), d2(N, 1);
    for (int i = 2; i < N; i++) {
        for (int j = i; j < N; j += i) {
            d1[j] += i; d2[j] += i * i;
        }
    }
    for (int i = 2; i < N; i++) {
        d1[i] += d1[i - 1];
    } 
    int q; std::cin >> q;
    for (int i = 0; i < q; i++) {
        int n, k; std::cin >> n >> k;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int mi = LONG_LONG_MAX;
            for (int j = 1; ; j++) {
                mi = std::min(mi, std::abs(d1[j] - d2[i]));
                if (d1[j] > d2[i]) break;
            }
            ans += mi <= k;
        }
        std::cout << ans << '\n';
    }
}