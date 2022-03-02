#include<bits/stdc++.h>
using namespace std;
#define wwj
signed main() {
    #ifdef wwj
        std::ifstream cin("E:\\workworkwork\\GitHub\\WinnieLearning\\Problem list\\cat party\\4.in");
        std::ofstream cout("E:\\workworkwork\\GitHub\\WinnieLearning\\Problem list\\cat party\\4.out");
    #endif
    int n, m; cin >> n >> m;
    std::vector<int> a(n + 1, 0), g(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        g[i] = 1 << x;  
    }
    std::vector<int> fa(n + 1), sz(n + 1);
    std::function<int(int)> find = [&](int x) { return x == fa[x] ? x: fa[x] = find(fa[x]); };
    for (int i = 0; i <= n; i++) {
        fa[i] = i; sz[i] = 1;
    }
    std::set<std::pair<int, int>, std::less<std::pair<int, int>>> s[3];// 0: 012 1:01  2:02
    std::set<std::pair<int, int>, std::greater<std::pair<int, int>>> e[3];
    int ans[3] = {0, 0, 0};
    int cnt = 0;
    int id = 0; //选一个最大的0的下标
    std::function<void(int x)> del = [&](int x) {
        for (int i = 0; i < 3; i++) {
            if (s[i].count({sz[x], x})) {
                s[i].erase({sz[x], x});
                ans[i] -= sz[x];
            }
            if (e[i].count({sz[x], x})) {
                e[i].erase({sz[x], x});
            }
            if (!i && id == x) {
                ans[i] -= sz[id];
                id = 0;
            }
        }
    };
    for (int j = 0; j < 3; j++) {
        for (int i = 1; i <= n; i++) {
            if (!j || ((1 << j) & g[i])) {
                if (!j && (g[i] & 1) && !id) {
                    ans[j] += sz[id = i];
                } else e[j].insert({sz[i], i});
            }
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            del(fu); del(fv);
            fa[fv] = fu;
            sz[fu] += sz[fv];
            g[fu] |= g[fv];
            for (int j = 0; j < 3; j++) {
                if (!j || (1 << j) & g[fu]) {
                    if (!j && (g[fu] & 1) && !id || (int)s[j].size() < cnt + (j ? 1: 0)) {
                        if (!j && !id && (g[fu] & 1)) {
                            id = fu;
                        }else s[j].insert({sz[fu], fu});
                        ans[j] += sz[fu];
                    } else {
                        if (!j && (g[fu] & 1) && sz[id] < sz[fu]) {
                            ans[j] -= sz[id];
                            e[j].insert({sz[id], id});
                            ans[j] += sz[id = fu];
                        } else e[j].insert({sz[fu], fu}); 
                    }
                }
                for (; (int)s[j].size() > cnt + (j ? 1: 0); ) {
                    ans[j] -= (*s[j].begin()).first;
                    e[j].insert(*s[j].begin());
                    s[j].erase(s[j].begin());
                }
                for (; (int)s[j].size() < cnt + (j ? 1: 0) && !e[j].empty(); ) {
                    s[j].insert(*e[j].begin());
                    ans[j] += (*e[j].begin()).first;
                    e[j].erase(e[j].begin());
                }
                for (; !s[j].empty() && !e[j].empty() && (*s[j].begin()).first < (*e[j].begin()).first; ) {
                    auto x = *s[j].begin(), y = *e[j].begin(); 
                    s[j].erase(s[j].begin()); e[j].erase(e[j].begin());
                    s[j].insert(y); e[j].insert(x);
                    ans[j] += y.first - x.first;
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
        cout << (*std::max_element(ans, ans + 3)) - 1 << '\n';
        #ifdef wwj
        if (i < 50) {
            std::cout << "m:" << i << '\n';
            std::cout << "id:" << id << '\n';
            for (int _ = 0; _ < 3; _++) {
                std::cout << "s" << _ << ":" << '\n';
                for (auto __: s[_]) std::cout << "->" << __.first << ' ' << __.second;
                std::cout << '\n'; 
            }
        } else if (i == m - 1) {
            std::cout << "m:" << i << '\n';
            std::cout << "id:" << id << '\n';
            for (int _ = 0; _ < 3; _++) {
                std::cout << "s" << _ << ":" << '\n';
                for (auto __: s[_]) if (__.first > 1) std::cout << "->" << __.first << ' ' << __.second;
                std::cout << '\n';
            }
            for (int _ = 0; _ < 3; _++) {
                std::cout << "e" << _ << ":" << '\n';
                for (auto __: e[_]) if (__.first > 1) std::cout << "->" << __.first << ' ' << __.second;
            std::cout << '\n';  
            }
        }
        #endif
    }
    #ifdef wwj
        std::cout << "cnt:" << cnt << '\n';
    #endif
}
