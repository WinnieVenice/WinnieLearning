#include <bits/stdc++.h>
#include<random>
#include<chrono>
#define int long long
#define endl '\n'
#define LL __int128
#define random(a,b) ((a)+rand()%((b)-(a)+1))
using namespace std;
int qpow(int a, int b, int p) {int ret = 1; for(a %= p; b; b >>= 1, a = a * a % p) if(b & 1) ret = ret * a % p; return ret; }
int qpow(int a,int b) {int ret = 1; for(; b; b >>= 1, a *= a) if(b & 1) ret *= a; return ret; }
int gcd(int x,int y) {return y ? gcd(y, x % y) : x; }
pair<int,int> exgcd(int a,int b) { if(!b) return {1, 0}; pair<int,int> ret = exgcd(b, a % b); return {ret.second, ret.first - a / b * ret.second }; }
int lcm(int x,int y){ return x / gcd(x, y) * y; }

#define wwj
signed main() {
    #ifdef wwj
        std::ifstream cin("E:\\workworkwork\\GitHub\\WinnieLearning\\Problem list\\cat party\\5.in");
        std::ofstream cout("E:\\workworkwork\\GitHub\\WinnieLearning\\Problem list\\cat party\\4.in");
    #endif 
    std::mt19937 rng(std::random_device{}());
    std::srand(rng());
    std::uniform_int_distribution<long long> _n(1, 1e5);
    std::uniform_int_distribution<long long> _m(1, 1e5);
    std::uniform_int_distribution<long long> _a(1, 2);
    int n = 1e5, m = 1e5; 
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = _a(rng);
    /*
    for (int i = 0; i < n / 3; i++) a[i] = 0;
    for (int i = n / 3 + 1; i < n / 3 * 2; i++) a[i] = 1;
    for (int i = n / 3 * 2 + 1; i < n; i++) a[i] = 2;
    */
    std::shuffle(a.begin(), a.end(), default_random_engine(rng()));
    std::vector<std::vector<int>> b(3, std::vector<int>());
    for (int i = 0; i < n; i++) {
        b[a[i]].push_back(i + 1);
        if (a[i]) b[0].push_back(i + 1);
    }
    for (int i = 0; i < 3; i++) {
        std::shuffle(b[i].begin(), b[i].end(), default_random_engine(rng()));
    }
    std::set<std::pair<int, int>> Q;
    for (int _ = 0; _ < 3; _++) {   //菊花
        if (b[_].size() < 2) continue;
        for (int tot = b[_].size(), rt = 0; rt < (int)b[_].size() && tot > 0 && Q.size() < m; rt++) {
            int cur_tot = random(1, tot);
            tot -= cur_tot;
            for (int i = rt + 1; i < std::min(rt + cur_tot, (int)b[_].size()) && Q.size() < m; i++) {
                Q.insert({b[_][rt] + 1, b[_][i] + 1});
            }
            rt += cur_tot;
        }
    }
    /*
    for (; (int)Q.size() < m; ) {
        int id = _a(rng);
        int x = random(0, (int)b[id].size() - 1), y = random(0, (int)b[id].size() - 1);
        for (; y == x; ) y = random(0, (int)b[id].size() - 1);
        //cout << x << ' ' << y << '\n';
        Q.insert({b[id][x] + 1, b[id][y] + 1});
    }
    */
    m = Q.size();
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << '\n';
    for (auto &v: Q) cout << v.first << ' ' << v.second << '\n';
    std::cout << "done" << '\n';
}