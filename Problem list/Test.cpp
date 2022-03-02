#include<bits/stdc++.h>
const int N = 5 + 1e6;
int st[N << 2], lz[N << 2];
void push(int x) {
    st[x << 1] = std::max(st[x << 1], lz[x]);
    st[x << 1| 1] = std::max(st[x << 1| 1], lz[x]);
    lz[x << 1] = std::max(lz[x << 1], lz[x]);
    lz[x << 1| 1] = std::max(lz[x << 1| 1], lz[x]);
    lz[x] = 0;
}
void upd(int x, int l, int r, int p, int v) {
    if (l == r) {
        //std::cout << "upd:" << x << ' ' << l << ' ' << r << ' ' << p << ' ' << v << '\n';
        st[x] = v;
        return;
    }
    push(x);
    int mid = l + r >> 1;
    if (p <= mid) upd(x << 1, l, mid, p, v);
    else upd(x << 1| 1, mid + 1, r, p, v);
}
void upd(int x, int l, int r, int L, int R, int v) {
    if (l > R || r < L) return;
    if (L <= l && r <= R) {
        st[x] = std::max(st[x], v);
        lz[x] = std::max(v, lz[x]);
        return;
    }
    push(x);
    int mid = l + r >> 1;
    upd(x << 1, l, mid, L, R, v); upd(x << 1| 1, mid + 1, r, L, R, v);
}
int que(int x, int l, int r, int p) {
    if (l == r) {
        //std::cout << "que:" << x << ' ' << l << ' ' << r << ' ' << p << '\n';
        return st[x];
    }
    push(x);
    int mid = l + r >> 1;
    if (p <= mid) return que(x << 1, l, mid, p);
    else return que(x << 1| 1, mid + 1, r, p);
} 
signed main() {
    int n, q; std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int x; std::cin >> x;
        upd(1, 1, n, i, x); 
    }
    for (; q--; ) {
        int op; std::cin >> op;
        if (op == 1) {
            int x, v; std::cin >> x >> v;
            upd(1, 1, n, x, v);
        } else {
            int v; std::cin >> v;
            upd(1, 1, n, 1, n, v);
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cout << que(1, 1, n, i) << ' ';
    }
    std::cout << '\n';
}
