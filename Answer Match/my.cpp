#include<bits/stdc++.h>
#define int long long 
using namespace std;
signed main() {
    std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0);
    int n; cin >> n;
    std::vector<int> pos_x;
    std::vector<std::tuple<int, int, int, int>> line;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        pos_x.push_back(x1); pos_x.push_back(x2);
        line.push_back({x1, x2, y1, 1});
        line.push_back({x1, x2, y2, -1});
    }
    std::sort(pos_x.begin(), pos_x.end());
    int m = std::unique(pos_x.begin(), pos_x.end()) - pos_x.begin();
    std::map<int, int> inv;
    for (int i = 0; i < m; i++) {
        inv[pos_x[i]] = i;
    }
    std::sort(line.begin(), line.end(), [&](auto x, auto y) {
        return std::get<2>(x) < std::get<2>(y);
    });
    std::vector<int> cnt((m + 1) << 2, 0), len((m + 1) << 2, 0);
    auto poll = [&](int x, int l, int r) {
        if (cnt[x]) {
            len[x] = pos_x[r + 1] - pos_x[l];
        } else if (l < r) {
            len[x] = len[x << 1] + len[x << 1| 1];
        } else len[x] = 0;
    };
    std::function<void(int, int, int, int, int, int)> upd = [&](int x, int l, int r, int L, int R, int v) {
        if (pos_x[l] > pos_x[R] || pos_x[r] < pos_x[L]) return;
        if (pos_x[L] <= pos_x[l] && pos_x[r] <= pos_x[R]) {
            cnt[x] += v;
            poll(x, l, r);
            return;
        }
        int mid = l + r >> 1;
        upd(x << 1, l, mid, L, R, v); upd(x << 1| 1, mid + 1, r, L, R, v);
        poll(x, l, r);
    };
    int ans = 0;
    for (int i = 0, sz = n << 1; i < sz - 1; ++i) {
        upd(1, 0, m - 1, inv[std::get<0>(line[i])], inv[std::get<1>(line[i])] - 1, std::get<3>(line[i]));
        ans += (std::get<2>(line[i + 1]) - std::get<2>(line[i])) * len[1];
    }
    std::cout << ans << '\n';
}