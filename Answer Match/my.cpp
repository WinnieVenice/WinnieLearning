#include<bits/stdc++.h>
using namespace std;
#define int long long
const int M = 5 + 1e5;
int st[M << 2], tag[M << 2];
void push(int x, int l, int r) {
    if (tag[x]) {
        int v = tag[x]; tag[x] = 0;
        int mid = l + r >> 1;
        st[x << 1] += (mid - l + 1) * v; tag[x << 1] += v; 
        st[x << 1| 1] += (r - (mid + 1) + 1) * v;   tag[x << 1| 1] += v;
    }
}
void upd(int x, int l, int r, int L, int R) {
    if (l > R || r < L) return;
    if (L <= l && r <= R) {
        st[x] += r - l + 1;
        tag[x]++;
        return;
    }
    push(x, l, r);
    int mid = l + r >> 1;
    upd(x << 1, l, mid, L, R); upd(x << 1| 1, mid + 1, r, L, R);
    st[x] = st[x << 1] + st[x << 1| 1];
}
int que(int x, int l, int r, int L, int R) {
    if (l > R || r < L) return 0;
    if (L <= l && r <= R) return st[x];
    int mid = l + r >> 1;
    push(x, l, r);
    return que(x << 1, l, mid, L, R) + que(x << 1| 1, mid + 1, r, L, R);
}
signed main() {
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
    std::vector<int> K(N);
    for (int i = 1; i < N; i++) {
        auto x = std::lower_bound(d1.begin(), d1.end(), d2[i]) - d1.begin();
        //std::cout << i << ' ' << d1[x] - d2[i] << ' ' << ( x ? d2[i] - d1[x - 1]: (int)1e9) << '\n';
        K[i] = std::min({d1[x] - d2[i], x ? d2[i] - d1[x - 1]: (int)1e9});
    }
    int m; cin >> m;
    std::vector<std::tuple<int, int, int>> q(m);
    for (int i = 0; i < m; i++) {
        int n, k; cin >> n >> k;
        q.push_back({n, k, i});
    }
    std::sort(q.begin(), q.end(), [&](auto x, auto y) {
        return std::get<0>(x) < std::get<0>(y);
    });
    int pre = 0;
    std::vector<int> ans(m);
    int mx = 0;
    for (auto [n, k, i]: q) {
        mx = std::max(mx, n);
        for (; pre < n; pre++) {
            upd(1, 0, M - 1, K[pre + 1], K[pre + 1]);
        }
        ans[i] = que(1, 0, M - 1, 0, k);
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << '\n';
    }
}