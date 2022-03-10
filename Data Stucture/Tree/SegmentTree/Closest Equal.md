# Closest Equal

## 题面

给定一个下标从 1~n 的序列 a，然后进行 m 次询问。

每次询问给出一对 [l,r]，找到区间中数值相等的且距离最相近的两个数 $a_i$ 和 $a_j$，求它们的距离。

换言之找到一组数 $(a_i,a_j)$ 满足

-   $a_i=a_j$
-   $l≤i,j≤r (i≠j)$

求 |i−j| 的最小值，如果区间中不存在相等的两个数，则输出 −1。

## 输入

第一行输入两个整数 $1≤n,m≤5×10^5$。

第二行输入 n 个整数 $1≤ai≤10^9$。

接下来 m 行，每行输入两个整数 $1≤l≤r≤n$。

## 做法



## Code

```C++
#include <bits/stdc++.h>
#define int long long 
//#define wwj
#ifdef wwj
    #include<wwj.h>
#endif

signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
    int n, m; std::cin >> n >> m;
    std::vector<int> a(n);
    for (auto &v: a) std::cin >> v;
    std::vector<std::vector<std::pair<int, int>>> q(n + 1);
    for (int i = 0; i < m; i++) {
        int l, r; std::cin >> l >> r;
        q[l].push_back({r, i});
    }
    std::vector<int> st((n + 1) << 2, 2e9);
    std::function<void(int, int, int, int, int)> upd = [&](int x, int l, int r, int p, int v) {
        if (l == r) {
            st[x] = std::min(st[x], v);
            return;
        }
        int mid = l + r >> 1;
        if (p <= mid) upd(x << 1, l, mid, p, v);
        else upd(x << 1| 1, mid + 1, r, p, v);
        st[x] = std::min(st[x << 1], st[x << 1| 1]);
    };
    std::function<int(int, int, int, int, int)> que = [&](int x, int l, int r, int L, int R) {
        if (l > R || r < L) return (int)2e9;
        if (L <= l && r <= R) return st[x];
        int mid = l + r >> 1;
        return std::min(que(x << 1, l, mid, L, R), que(x << 1| 1, mid + 1, r, L, R));
    };
    std::vector<int> ans(m);
    std::map<int, int> pre;
    for (int i = n - 1; ~i; --i) {
        if (pre.count(a[i])) {
            upd(1, 1, n, pre[a[i]] + 1, pre[a[i]] - i);
        }
        pre[a[i]] = i;
        for (auto &v: q[i + 1]) {
            ans[v.second] = que(1, 1, n, 1, v.first);
        }
    }
    for (int i = 0; i < m; i++) std::cout << (ans[i] == 2e9? -1: ans[i]) << '\n';
}
```



```C++
#include <bits/stdc++.h>
#define int long long 
//#define wwj
#ifdef wwj
    #include<wwj.h>
#endif

signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
    int n, m; std::cin >> n >> m;
    std::map<int, std::vector<int>> a;
    for (int i = 0; i < n; i++) {
        int x; std::cin >> x;
        a[x].push_back(i + 1);
    }
    std::vector<std::tuple<int, int, int, int>> q;
    for (int i = 0; i < m; i++) {
        int l, r; std::cin >> l >> r;
        q.push_back({l, r, i, 0});
    }
    for (auto &v: a) {
        for (int i = 1, sz = v.second.size(); i < sz; i++) {
            q.push_back({v.second[i - 1], v.second[i], 0, v.second[i] - v.second[i - 1]});
        }
    }
    std::sort(q.begin(), q.end(), [&](auto x, auto y) {
        if (std::get<1>(x) != std::get<1>(y)) return std::get<1>(x) < std::get<1>(y);
        else if (std::get<3>(x)) return true;
        else return false;
    });
    std::vector<int> st((n + 1) << 2, 2e9);
    std::function<void(int, int, int, int, int)> upd = [&](int x, int l, int r, int p, int v) {
        if (l == r) {
            st[x] = std::min(st[x], v);
            return;
        }
        int mid = l + r >> 1;
        if (p <= mid) upd(x << 1, l, mid, p, v);
        else upd(x << 1| 1, mid + 1, r, p, v);
        st[x] = std::min(st[x << 1], st[x << 1| 1]);
    };
    std::function<int(int, int, int, int, int)> que = [&](int x, int l, int r, int L, int R) {
        if (l > R || r < L) return (int)2e9;
        if (L <= l && r <= R) return st[x];
        int mid = l + r >> 1;
        return std::min(que(x << 1, l, mid, L, R), que(x << 1| 1, mid + 1, r, L, R));
    };
    std::vector<int> ans(m);
    for (auto u: q) {
        if (std::get<3>(u)) {
            upd(1, 1, n, std::get<0>(u), std::get<3>(u));

        } else {
            ans[std::get<2>(u)] = que(1, 1, n, std::get<0>(u), n);
        }
    }
    for (int i = 0; i < m; i++) std::cout << (ans[i] == 2e9? -1: ans[i]) << '\n';
}
```

