# SegmentTree

## 指针版动态开点模板

```C++
template<typename _Tp>
struct Node{
    _Tp *v; 
    Node<_Tp> *lc, *rc;
    template<class ...args>
    Node(const args&... _v):lc(NULL), rc(NULL) { v = new _Tp(_v...); }
    ~Node() { if (lc != NULL) delete lc; if (rc != NULL) delete rc; }
};
template<typename _Tp>
struct Seg {
    template<class ...args>
    void create(Node<_Tp> * &x, const args&...) { }
    template<class ...args>
    void apply(Node<_Tp> * &x, const int &l, const int &r, const args&...) { }
    _Tp merge(const _Tp &x, const _Tp &y) { }
    template<class ...args>
    void poll(Node<_Tp> * &x, const int &l, const int &r, const args&...) { }
    template<class ...args>
    void push(Node<_Tp> * &x, const int &l, const int &r, const args&...) { }
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
    _Tp que(Node<_Tp> * &x, const int &l, const int &r, const int &L, const int &R) {
        create(x);
        if (l > R || r < L) return 0;
        if (L <= l && r <= R) return x->v;
        push(x, l, r);
        int mid = (l + r) >> 1;
        return merge(que(x->lc, l, mid, L, R), que(x->rc, mid + 1, r, L, R));
    }
    Seg() {
        rt = new Node<_Tp>();
    }
    Node<_Tp> *rt;
};
struct node {
    int v, lt, rt;
    node(int _v = 0, int _lt = 0, int _rt = 0): v(_v), lt(_lt), rt(_rt) { }
};
template<> template<>
void Seg<node>::create(Node<node> * &x) {
    if (x == NULL) x = new Node<node>();
}
template<> template<>
void Seg<node>::apply(Node<node> * &x, const int &l, const int &r, const int &v) {
    x->v->v += v; x->v->lt += v; x->v->rt += v;    
}
template<> template<>
void Seg<node>::poll(Node<node> * &x, const int &l, const int &r) {
    int mid = (l + r) >> 1;
    create(x->lc); 
    create(x->rc);
    if (x->lc->v->v == mid - l + 1 && x->rc->v->v == r - mid) {
        x->v->v = x->v->lt = x->v->rt = r - l + 1;
    } else {
        x->v->v = max(x->lc->v->v, x->rc->v->v);
        if (x->lc->v->rt && x->rc->v->lt) {
            x->v->v = max(x->v->v, x->lc->v->rt + x->rc->v->lt);
        }
        x->v->lt = x->lc->v->lt + (x->lc->v->lt == mid - l + 1? x->rc->v->lt: 0); 
        x->v->rt = x->rc->v->rt + (x->rc->v->rt == r - mid? x->lc->v->rt: 0);
    }
}
```

