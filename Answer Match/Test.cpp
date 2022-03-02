#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

constexpr int Mod = 998244353;

int add(int x, int y) {
    x += y;
    return x >= Mod ? x - Mod : x;
}
int sub(int x, int y) {
    x -= y;
    return x < 0 ? x + Mod : x;
}
int mul(int x, int y) {
    int64_t res = int64_t(x) * y % Mod;
    return int(res);
}
int inv(int x) {
    int res = 1;
    for (int i = Mod - 2; i > 0; i /= 2) {
        if (i % 2 > 0) {
            res = mul(res, x);
        }
        x = mul(x, x);
    }
    return res;
}

struct Node {
    int sum, coef;
    int lazy, lazyCoef;
    Node *left, *right;

    void Apply(int v, int c) {
        sum = add(sum,mul(coef, mul(sub(c, 1), sub(1, v))));
        coef = mul(coef, v);
        lazy = add(lazy, mul(lazyCoef, mul(sub(c, 1), sub(1, v))));
        lazyCoef = mul(lazyCoef, v);
    }
    void ApplyLazy(Node *par) {
        sum = add(sum, mul(coef, par->lazy));
        coef = mul(coef, par->lazyCoef);
        lazy = add(lazy, mul(par->lazy, lazyCoef));
        lazyCoef = mul(lazyCoef, par->lazyCoef);
    }
    void Push(int t) {
        if (left != nullptr) {
            left->ApplyLazy(this);
        }
        if (right != nullptr) {
            right->ApplyLazy(this);
        }
        lazy = 0, lazyCoef = 1;
    }
    void Maintain() {
        if (left == nullptr && right == nullptr) {
            return;
        }
        sum = coef = 0;
        for (auto p : {left, right}) {
            if (p != nullptr) {
                sum = add(sum, p->sum);
                coef = add(coef, p->coef);
            }
        }
    }
    void Update(int from, int to, int val, int t, int l, int r) {
        if (r < from || to < l) {
            return;
        }
        if (from <= l && r <= to) {
            Apply(val, t);
            return;
        }
        Push(t);
        int mid = (l + r) / 2;
        left->Update(from, to, val, t, l, mid);
        right->Update(from, to, val, t, mid + 1, r);
        Maintain();
    }
    int Query(int from, int to, int t, int l, int r) {
        if (r < from || to < l) {
            return 0;
        }
        if (from <= l && r <= to) {
            return add(sum, mul(coef, t));
        }
        Push(t);
        int mid = (l + r) / 2;
        return add(left->Query(from, to, t, l, mid),
                   right->Query(from, to, t, mid + 1, r));
    }
};
namespace NodePool {
    const int Limit = 1010000;
    Node pool[Limit];
    int cur = 0;

    Node* NewNode() {
        pool[cur].lazy = 0, pool[cur].lazyCoef = 1;
        pool[cur].sum = 0, pool[cur].coef = 1;
        pool[cur].left = pool[cur].right = nullptr;
        return &pool[cur++];
    }
};

struct SegmentTree {
    Node *root_;
    int low_, high_;

    SegmentTree(int low, int high) {
        root_ = NodePool::NewNode();
        low_ = low, high_ = high;
        build(root_, low_, high_);
    }

    void build(Node* cur, int l, int r) {
        if (l == r) {
            cur->sum = -(l - 1);
            return;
        }
        int mid = (l + r) / 2;
        cur->left = NodePool::NewNode();
        cur->right = NodePool::NewNode();
        build(cur->left, l, mid);
        build(cur->right, mid + 1, r);
        cur->Maintain();
    }

    void Update(int from, int to, int val, int t) const {
        root_->Update(from, to, val, t, this->low_, this->high_);
    }
    [[nodiscard]] int Query(int from, int to, int t) const {
        return root_->Query(from, to, t, this->low_, this->high_);
    }
};

struct Range {
    int l, r, i;
};

int main (int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<Range> ranges(m);
    for (int i = 0; i < m; i++) {
        cin >> ranges[i].l >> ranges[i].r;
        ranges[i].i = i;
    }

    sort(ranges.begin(), ranges.end(), [&](const auto& x, const auto& y) {
        return x.r < y.r;
    });

    vector<int> result(m);
    SegmentTree sgt(1, n);
    vector<pair<int, int>> stack1, stack2;
    stack1.emplace_back(0, INT_MAX);
    stack2.emplace_back(0, -1);

    for (int i = 0, j = 0; i < n; i++) {
        sgt.Update(i + 1, i + 1, mul(a[i], a[i]), i + 1);

        int r = i;
        while (stack1.back().second < a[i]) {
            int v = mul(a[i], inv(stack1.back().second));
            stack1.pop_back();

            sgt.Update(stack1.back().first + 1, r, v, i + 1);
            r = stack1.back().first;
        }
        stack1.emplace_back(i + 1, a[i]);

        r = i;
        while (stack2.back().second > a[i]) {
            int v = mul(a[i], inv(stack2.back().second));
            stack2.pop_back();

            sgt.Update(stack2.back().first + 1, r, v, i + 1);
            r = stack2.back().first;
        }
        stack2.emplace_back(i + 1, a[i]);

        for (; j < m && ranges[j].r == i + 1; j++) {
            result[ranges[j].i] = sgt.Query(ranges[j].l, ranges[j].r, i + 1);
        }
    }

    for (int i = 0; i < m; i++) {
        cout << result[i] << "\n";
    }
}

/*
    result = pref + val * time
    val = v1 * v2
    lazy = 0
    lazyCoef = 1
    
    # frac = new_v1 / old_v1, new_v2 / old_v2
    # new_val = old_val * frac
    Apply(frac, t):
        pref += val(time - 1)(1 - frac)
        val *= frac
        lazy += lazyCoef(time - 1)(1 - frac)
        lazyCoef *= frac

    Push(lazy, lazyCoef):
        pref += val * lazy
        val *= lazyCoef
        lazy' += lazyCoef' * lazy
        lazyCoef' *= lazyCoef
 */