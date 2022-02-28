#include<bits/stdc++.h>
//#define wwj
using namespace std;
signed main() {
    #ifdef wwj
        std::ifstream cin("E:\\workworkwork\\GitHub\\WinnieLearning\\出题\\猫趴\\1.in");
        std::ofstream cout("E:\\workworkwork\\GitHub\\WinnieLearning\\出题\\猫趴\\1.out");
    #endif
    int n, m; std::cin >> n >> m;
    std::vector<int> a(n + 1, 0), g(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int x; std::cin >> x;
        g[i] = 1 << x;  
    }
    std::vector<int> fa(n + 1), sz(n + 1);
    std::function<int(int)> find = [&](int x) { return x == fa[x] ? x: fa[x] = find(fa[x]); };
    for (int i = 1; i <= n; i++) {
        fa[i] = i; sz[i] = 1;
    }
    std::set<std::pair<int, int>, std::less<std::pair<int, int>>> s[3];// 0: 012 1:01  2:02
    std::set<std::pair<int, int>, std::greater<std::pair<int, int>>> e[3];
    int ans[3] = {0, 0, 0};
    int cnt = 0;
    std::function<void(int x)> del = [&](int x) {
        for (int i = 0; i < 3; i++) {
            if (s[i].count({sz[x], x})) {
                s[i].erase({sz[x], x});
                ans[i] -= sz[x];
            }
            if (e[i].count({sz[x], x})) {
                e[i].erase({sz[x], x});
            }
        }
    };
    for (int j = 0; j < 3; j++) {
        for (int i = 1; i <= n; i++) {
            e[j].insert({sz[i], i});
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v; std::cin >> u >> v;
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            del(fu); del(fv);
            fa[fv] = fu;
            sz[fu] += sz[fv];
            g[fu] |= g[fv];
            for (int j = 0; j < 3; j++) {
                if ((1 << j) & g[fu]) {
                    if (s[j].empty()) {
                        s[j].insert({sz[fu], fu});
                        ans[j] = sz[fu];
                    } else {
                        if ((*s[j].begin()).first >= sz[fu]) {
                            e[j].insert({sz[fu], fu});
                        } else {
                            ans[j] -= (*s[j].begin()).first;
                            e[j].insert(*s[j].begin());
                            s[j].erase(s[j].begin());

                            ans[j] += sz[fu];
                            s[j].insert({sz[fu], fu});
                        }
                    }
                }
                for (; (int)s[j].size() < cnt + 1 && !e[j].empty(); ) {
                    s[j].insert(*e[j].begin());
                    ans[j] += (*e[j].begin()).first;
                    e[j].erase(e[j].begin());
                }
            }
        } else {
            cnt++;
            for (int j = 0; j < 3; j++) {
                if (!e[j].empty()) {
                    ans[j] += (*e[j].begin()).first;
                    s[j].insert(*e[j].begin()); 
                    e[j].erase(e[j].begin());
                }
            }
        }
        std::cout << (*std::max_element(ans, ans + 3)) - 1 << '\n';
    }
}
