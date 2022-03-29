#include<bits/stdc++.h>
#define int long long
#define ll long long
signed main() {
    const int mod = 998244353;
    std::function<ll(ll, ll)> add = [&](ll x, ll y) { return x + y >= mod ? x + y - (x + y) / mod * mod: x + y; };
    std::function<ll(ll, ll)> sub = [&](ll x, ll y) { return x - y < 0 ? x - y + (y - x + mod - 1) / mod * mod: add(x - y, 0); };
    std::function<ll(ll, ll)> mul = [&](ll x, ll y) { return x * y % mod; };
    std::function<ll(ll, ll, ll)> qpow = [&](ll x, ll y, ll p) { ll res = 1; for (; y; y >>= 1, x = x * x % p) if (y & 1) res = res * x % p; return res; };
    std::ios :: sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
    int n, m; std::cin >> n >> m;
    std::vector<int> a(n + 1), inv(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        inv[i] = qpow(a[i], mod - 2, mod);
    }
    std::vector<std::tuple<int, int, int>> q(m);
    for (int i = 0; i < m; i++) {
        int l, r; std::cin >> l >> r;
        q[i] = {l, r, i};
    }
    std::sort(q.begin(), q.end(), [&](auto x, auto y) {
        return std::get<1>(x) > std::get<1>(y);
    });
    std::vector<int> L((n + 2) << 2), R((n + 2) << 2), L_tag((n + 2) << 2, 0), R_tag((n + 2) << 2, 1);
    std::function<void(int)> poll = [&](int x) {
        L[x] = add(L[x << 1], L[x << 1| 1]);
        R[x] = add(R[x << 1], R[x << 1| 1]);
    };
    std::function<void(int)> push = [&](int x) {
        L[x << 1] = add(L[x << 1], mul(L_tag[x], R[x << 1]));
        L[x << 1| 1] = add(L[x << 1| 1], mul(L_tag[x], R[x << 1| 1]));
        R[x << 1] = mul(R[x << 1], R_tag[x]);
        R[x << 1| 1] = mul(R[x << 1| 1], R_tag[x]);
        L_tag[x << 1] = add(L_tag[x << 1], mul(L_tag[x], R_tag[x << 1]));
        L_tag[x << 1| 1] = add(L_tag[x << 1| 1], mul(L_tag[x], R_tag[x << 1| 1]));
        R_tag[x << 1] = mul(R_tag[x << 1], R_tag[x]);
        R_tag[x << 1| 1] = mul(R_tag[x << 1| 1], R_tag[x]);
        L_tag[x] = 0;
        R_tag[x] = 1;
    };
    std::function<void(int, int, int)> init = [&](int x, int l, int r) {
        if (l == r) {
            L[x] = -mul(l - 1, mul(a[l], a[l]));
            R[x] = mul(a[l], a[l]);
            return;
        }
        int mid = l + r >> 1;
        init(x << 1, l, mid); init(x << 1| 1, mid + 1, r);
        poll(x);
    };
    std::function<void(int, int, int, int, int, int, int)> upd = [&](int x, int l, int r, int _l, int _r, int pre_id, int cur_id) {
        if (l > _r || r < _l) return;
        if (_l <= l && r <= _r) {
            int val = mul(inv[pre_id], a[cur_id + 1]);
            L[x] = add(L[x], mul(R[x], cur_id));
            R[x] = mul(R[x], val);
            L[x] = sub(L[x], mul(R[x], cur_id));
            L_tag[x] = add(L_tag[x], mul(R_tag[x], cur_id));
            R_tag[x] = mul(R_tag[x], val);
            L_tag[x] = sub(L_tag[x], mul(R_tag[x], cur_id));
            return;
        }
        push(x);
        int mid = l + r >> 1;
        upd(x << 1, l, mid, _l, _r, pre_id, cur_id); upd(x << 1| 1, mid + 1, r, _l, _r, pre_id, cur_id);
        poll(x);
    };
    std::function<int(int, int, int, int, int, int)> que = [&](int x, int l, int r, int _l, int _r, int cur_id) {
        if (l > _r || r < _l) return 0ll;
        if (_l <= l && r <= _r) {
            return add(L[x], mul(R[x], cur_id));
        }
        push(x);
        int mid = l + r >> 1;
        return add(que(x << 1, l, mid, _l, _r, cur_id), que(x << 1| 1, mid + 1, r, _l, _r, cur_id));
    };
    init(1, 1, n);
    std::vector<int> mi, mx;
    std::vector<int> ans(m);
    for (int i = 1; i <= n && !q.empty(); i++) {
        for (; !mi.empty() && a[mi.back()] > a[i]; ) {
            int x = mi.back(); mi.pop_back();
            int l = mi.empty() ? 1: mi.back() + 1, r = x;
            upd(1, 1, n, l, r, x, i - 1);
        }
        mi.push_back(i);
        for (; !mx.empty() && a[mx.back()] < a[i]; ) {
            int x = mx.back(); mx.pop_back();
            int l = mx.empty() ? 1: mx.back() + 1, r = x;
            upd(1, 1, n, l, r, x, i - 1);
        }
        mx.push_back(i);
        for (;!q.empty() && i == std::get<1>(q.back()); ) {
            ans[std::get<2>(q.back())] = que(1, 1, n, std::get<0>(q.back()), std::get<1>(q.back()), i);
            q.pop_back();
        }
    }
    for (int i = 0; i < m; i++) std::cout << (ans[i] + mod) % mod << '\n';
}