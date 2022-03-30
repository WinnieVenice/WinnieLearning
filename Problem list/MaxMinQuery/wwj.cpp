#include <bits/stdc++.h>
#define int long long
#define wwj
#ifdef wwj
std::ifstream cin("E:/workworkwork/GitHub/demo/test.in");
std::ofstream cout("E:/workworkwork/GitHub/demo/test.out");
#else
using namespace std;
#endif
template<typename _Tp>
struct Node{
    _Tp *v; 
    Node<_Tp> *lc, *rc;
    template<class ...args>
    Node(const args&... _v):lc(nullptr), rc(nullptr) { v = new _Tp(_v...); }
    ~Node() { if (lc != nullptr) delete lc; if (rc != nullptr) delete rc; }
};
template<typename _Tp>
struct Seg {
    template<class ...args>
    void create(Node<_Tp> * &x, const args&...v);
    template<class ...args>
    void apply(Node<_Tp> * &x, const int &l, const int &r, const args&...v);
    template<typename T>
    T merge(const T &x, const T &y);
    template<typename T, class ...args>
    T ret(Node<_Tp> *&x, const args& ...v);
    template<class ...args>
    void poll(Node<_Tp> * &x, const int &l, const int &r, const args&...v);
    template<class ...args>
    void push(Node<_Tp> * &x, const int &l, const int &r, const args&...v);
    template<class ...args> 
    void init(Node<_Tp> *&x, const int &l, const int &r, const args &...v, void(*init_apply)(Node<_Tp> *&x, const int &l, const int &r, const args &...v)) {
        create(x);
        if (l == r) {
            init_apply(x, l, r, v...);
            return;
        }
        int mid = l + r >> 1;
        init(x->lc, l, mid, v..., init_apply); init(x->rc, mid + 1, r, v..., init_apply);
        poll(x, l, r);
    }
    template<class ...args>
    void upd(Node<_Tp> * &x, const int &l, const int &r, const int &L, const int &R, const args &...v) {
        create(x);
        if (l > R || r < L) return;
        if (L <= l && r <= R) {
            apply(x, l, r, v...);
            return;
        }
        push(x, l, r);
        int mid = (l + r) >> 1;
        upd(x->lc, l, mid, L, R, v...); upd(x->rc, mid + 1, r, L, R, v...);
        poll(x, l, r);
    }
    template<typename T, class ...args>
    T que(Node<_Tp> * &x, const int &l, const int &r, const int &L, const int &R, const args& ...v) {
        create(x);
        if (l > R || r < L) return T(0);
        if (L <= l && r <= R) return ret<T>(x, v...);
        push(x, l, r);
        int mid = (l + r) >> 1;
        return merge<T>(que<T>(x->lc, l, mid, L, R, v...), que<T>(x->rc, mid + 1, r, L, R, v...));
    }
    Seg() {
        rt = new Node<_Tp>();
    }
    Node<_Tp> *rt;
};
const int mod = 998244353;
const int N = 5 + 5e5;
int a[N], inv[N];
int add(const int &x, const int &y) {
    return x + y > mod? x - mod + y: x + y;
}
int sub(const int &x, const int &y) {
    return x - y < 0? x - y + mod: x - y;
}
int mul(const int &x, const int &y) {
    return x * y % mod;
}
int qpow(int x, int y) { int _ = 1; for (; y; y >>= 1, x = mul(x, x)) if (y & 1) _ = mul(_, x); return _; }
struct node {
    int l, r, lt, rt;
    node(int _l = 0, int _r = 0, int _lt = 0, int _rt = 1): l(_l), r(_r), lt(_lt), rt(_rt) { }
};
template<> template<>
void Seg<node>::create(Node<node> * &x) {
    if (x == nullptr) x = new Node<node>();
}
template<> template<>
void Seg<node>::apply(Node<node> * &x, const int &l, const int &r, const int &pre, const int &id) {
    int g = mul(inv[pre], a[id + 1]);
    x->v->l = add(x->v->l, mul(x->v->r, id));
    x->v->r = mul(x->v->r, g);
    x->v->l = sub(x->v->l, mul(x->v->r, id));
    x->v->lt = add(x->v->lt, mul(x->v->rt, id));
    x->v->rt = mul(x->v->rt, g);
    x->v->lt = sub(x->v->lt, mul(x->v->rt, id));
}
template<> template<>
void Seg<node>::poll(Node<node> * &x, const int &l, const int &r) {
    create(x->lc); create(x->rc);
    x->v->l = add(x->lc->v->l, x->rc->v->l);
    x->v->r = add(x->lc->v->r, x->rc->v->r);
}
template<> template<>
void Seg<node>::push(Node<node> *&x, const int &l, const int &r) {
    create(x->lc); create(x->rc);
    x->lc->v->l = add(x->lc->v->l, mul(x->v->lt, x->lc->v->r));
    x->lc->v->r = mul(x->lc->v->r, x->v->rt);
    x->rc->v->l = add(x->rc->v->l, mul(x->v->lt, x->rc->v->r));
    x->rc->v->r = mul(x->rc->v->r, x->v->rt);
    x->lc->v->lt = add(x->lc->v->lt, mul(x->v->lt, x->lc->v->rt));
    x->lc->v->rt = mul(x->lc->v->rt, x->v->rt);
    x->rc->v->lt = add(x->rc->v->lt, mul(x->v->lt, x->rc->v->rt));
    x->rc->v->rt = mul(x->rc->v->rt, x->v->rt);
    x->v->lt = 0; x->v->rt = 1;
}
template<> template<>
int Seg<node>::ret<int>(Node<node> *&x, const int &id) {
    return add(x->v->l, mul(x->v->r, id));
}
template<> template<>
int Seg<node>::merge<int>(const int &x, const int &y) {
    return add(x, y);
}
void init_apply(Node<node> *&x, const int &l, const int &r) {
    x->v->l = -mul(l - 1, mul(a[l], a[l]));
    x->v->r = mul(a[l], a[l]);
}
std::tuple<int, int, int> q[N];
Seg<node> sg;
int ans[N];
signed main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        inv[i] = qpow(a[i], mod - 2);
    }
    sg.init(sg.rt, 0, n - 1, init_apply);
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        q[i] = std::tuple(l - 1, r - 1, i);
    }
    std::sort(q, q + m, [&](auto x, auto y) {
        return std::get<1>(x) < std::get<1>(y);
    });
    std::vector<int> mi, mx; mi.clear(); mx.clear();
    for (int i = 0, j = 0; i < n && j < m; i++) {
        for (; !mi.empty() && a[mi.back()] > a[i]; ) {
            auto x = mi.back(); mi.pop_back();
            auto l = mi.empty() ? 0: mi.back() + 1, r = x;
            sg.upd(sg.rt, 0, n - 1, l, r, x, i - 1);
        } 
        mi.push_back(i);
        for (; !mx.empty() && a[mx.back()] < a[i]; ) {
            auto x = mx.back(); mx.pop_back();
            auto l = mx.empty() ? 0: mx.back() + 1, r = x;
            sg.upd(sg.rt, 0, n - 1, l, r, x, i - 1);
        } 
        mx.push_back(i);
        for (; j < m && std::get<1>(q[j]) == i; j++) {
            ans[std::get<2>(q[j])] = sg.que<int>(sg.rt, 0, n - 1, std::get<0>(q[j]), std::get<1>(q[j]), i);
        }
    }
    for (int i = 0; i < m; i++) cout << (ans[i] + mod) % mod << '\n';
}