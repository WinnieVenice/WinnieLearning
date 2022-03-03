#include<bits/stdc++.h>
namespace discrete {
    #define T long long
    std::vector<T> a;
    int n;
    void init(T inf) { a.clear(); a.emplace_back(-inf); a.emplace_back(inf); }
    void add(T x) { a.emplace_back(x); }
    void work() {
        std::sort(a.begin(), a.end());
        n = std::unique(a.begin(), a.end()) - a.begin();
    }
    void era() { a.erase(a.begin() + n, a.end()); }
    int get(T x, int y) {
        int u = 0;
        if (y == 0) { // 找第一个a_i <= x
            u = std::upper_bound(a.begin(), a.begin() + n, x) - a.begin();
            u--;
        } else if (y == 1) { // 找第一个a_i >= x
            u = std::lower_bound(a.begin(), a.begin() + n, x) - a.begin();
        } else if (y == 2) { // 找第一个a_i > x
            u = std::upper_bound(a.begin(), a.begin() + n, x) - a.begin();
        } else { //找第一个a_i < x
            u = std::lower_bound(a.begin(), a.end(), x) - a.begin();
            u++;
        }
        return u;
    }
    #undef T
}