#include<bits/stdc++.h>
using namespace std;
const int N = 5 + 1e5;
int fa[N], sz[N];
int find(int x) { return x == fa[x]? x: fa[x] = find(fa[x]); }
vector<pair<int, int>> s[3];// 0 : 012 ; 1 : 01 ; 2 : 02
void del(int x) {
    for (int t = 0; t < 3; t++) {
        for (auto u = s[t].begin(); u != s[t].end(); u++) {
            if (u->second == x) {
                s[t].erase(u); break;
            }
        }
    }
}
int ans[3];
signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[i] = 1 << x;
    }
    for (int i = 1; i <= n; i++) {
        fa[i] = i; sz[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            if (!j || (a[i] & (1 << j))) {
                s[j].push_back({sz[i], i});
            }
        }
    }
    int cnt = 1;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        x = find(x), y = find(y);
        if (x != y) {
            del(x); del(y);
            sz[x] += sz[y];
            fa[y] = x;
            for (int t = 0; t < 3; t++) {
                if (!t || (a[x] & (1 << t))) {
                    s[t].push_back({sz[x], x});
                }
            }
        } else {
            cnt++;
        }
        int id = -1;
        for (int j = 0, SZ = s[0].size(); j < SZ; j++) {
            int u = s[0][j].second;
            if (a[u] & (1 << 0)) {
                if (id == -1 || sz[id] < sz[u]) {
                    id = u;
                }
            }
        }
        if (id != -1) {
            swap(s[0][0], s[0][id]);
            sort(s[0].begin(), s[0].end(), [&](auto x, auto y) {
                return x.first > y.first;
            });
            ans[0] = 0;
            for (int j = 0, SZ = s[0].size(); j < cnt && j < SZ; j++) {
                ans[0] += s[0][j].first;
            }
        } else ans[0] = -1;
        for (int t = 1; t < 3; t++) {
            sort(s[t].begin(), s[t].end(), [&](auto x, auto y) {
                return x.first > y.first;
            });
            ans[t] = 0;
            for (int j = 0, SZ = s[t].size(); j < cnt && j < SZ; j++) {
                ans[t] += s[t][j].first;
            }
        }
        cout << (*max_element(ans, ans + 3)) - 1<< '\n';
    }
}