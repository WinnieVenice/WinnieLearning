/*
 * O(n log(n) log(MOD))
 ! 求逆元需O(log(MOD))的时间，可优化至O(1)
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

template <int P>
struct mod_int {

    mod_int& operator += (const mod_int& x) {
        val += x.val;
        if (val >= P) {
            val -= P;
        }
        return *this;
    }
    mod_int& operator -= (const mod_int& x) {
        val -= x.val;
        if (val < 0) {
            val += P;
        }
        return *this;
    }
    mod_int& operator *= (const mod_int& x) {
        val = int(int64_t(val) * x.val % P);
        return *this;
    }
    mod_int& operator /= (const mod_int& x) {
        (*this) *= x.inv();
        return *this;
    }

    mod_int& operator ++ () {
        val = (val == P - 1) ? 0 : (val + 1);
        return *this;
    }
    mod_int& operator -- () {
        val = (val == 0) ? (P - 1) : (val - 1);
        return *this;
    }

    mod_int operator ++ (int) {
        mod_int res = *this;
        ++(*this);
        return res;
    }
    mod_int operator -- (int) {
        mod_int res = *this;
        --(*this);
        return res;
    }

    mod_int operator - () const {
        return mod_int((val == 0) ? 0 : (P - val));
    }

    friend mod_int operator + (mod_int x, const mod_int& y) {
        return x += y;
    }
    friend mod_int operator - (mod_int x, const mod_int& y) {
        return x -= y;
    }
    friend mod_int operator * (mod_int x, const mod_int& y) {
        return x *= y;
    }
    friend mod_int operator / (mod_int x, const mod_int& y) {
        return x /= y;
    }

    friend std::ostream& operator << (std::ostream& out, const mod_int& x) {
        return out << x.val;
    }

    static int inverse(int v) {
        int64_t res = 1;
        while (v > 1) {
            res = res * (P - P / v) % P;
            v = P % v;
        }
        return int(res * v % P);
    }

    mod_int inv() const {
        return mod_int(inverse(val));
    }

    mod_int pow(int64_t t) const {
        mod_int res = 1, v = *this;
        for (; t > 0; t /= 2, v *= v) {
            if (t % 2) {
                res *= v;
            }
        }
        return res;
    }

    mod_int() : val(0) {}
    mod_int(int v) : val(v % P) {
        if (val < 0) val += P;
    }
    mod_int(int64_t v) : mod_int(int(v % P)) {}
    mod_int(unsigned v) : val(v % P) {}
    mod_int(uint64_t v) : mod_int(v % P) {}

    template <typename T>
    explicit operator T() const {
        return T(val);
    }

    int val;
};

using mint = mod_int<MOD>;

struct segment_tree {

    void apply(int i, const mint& v, const mint& nv, const int& t) {
        A[i] += B[i] * (1 - nv / v) * (t - 1);
        B[i] *= nv / v;

        lazy_sum[i] += lazy_prod[i] * (1 - nv / v) * (t - 1);
        lazy_prod[i] *= nv / v;
    }

    void push(int i) {
        A[i * 2] += B[i * 2] * lazy_sum[i];
        A[i * 2 + 1] += B[i * 2 + 1] * lazy_sum[i];
        B[i * 2] *= lazy_prod[i];
        B[i * 2 + 1] *= lazy_prod[i];

        lazy_sum[i * 2] += lazy_sum[i];
        lazy_sum[i * 2 + 1] += lazy_sum[i];
        lazy_sum[i] = 0;

        lazy_prod[i * 2] *= lazy_prod[i];
        lazy_prod[i * 2 + 1] *= lazy_prod[i];
        lazy_prod[i] = 1;
    }

    template <class... T>
    void update(int low, int high, int i, int l, int r, const T&... args) {
        if (high < l || r < low) {
            return;
        }
        if (low <= l && r <= high) {
            apply(i, args...);
            return;
        }
        push(i);
        int m = (l + r) / 2;
        update(low, high, i * 2, l, m, args...);
        update(low, high, i * 2 + 1, m + 1, r, args...);
        A[i] = A[i * 2] + A[i * 2 + 1];
        B[i] = B[i * 2] + B[i * 2 + 1];
    }

    mint query(int low, int high, int i, int l, int r, mint t) {
        if (high < l || r < low) {
            return 0;
        }
        if (low <= l && r <= high) {
            return A[i] + B[i] * t;
        }
        push(i);
        int m = (l + r) / 2;
        return query(low, high, i * 2, l, m, t) + query(low, high, i * 2 + 1, m + 1, r, t);
    }

    void build(int i, int l, int r, const vector<mint>& arr) {
        lazy_sum[i] = 0, lazy_prod[i] = 1;
        if (l == r) {
            A[i] = -arr[l] * arr[l] * (r - 1);
            B[i] = arr[l] * arr[l];
            return;
        }
        int m = (l + r) / 2;
        build(i * 2, l, m, arr);
        build(i * 2 + 1, m + 1, r, arr);
        A[i] = A[i * 2] + A[i * 2 + 1];
        B[i] = B[i * 2] + B[i * 2 + 1];
    }

    segment_tree(int n) {
        A.assign(4 * n, 0);
        B.assign(4 * n, 0);
        lazy_sum.assign(4 * n, 0);
        lazy_prod.assign(4 * n, 0);
    }

    vector<mint> A, B, lazy_sum, lazy_prod;
};

struct Query {
    int l, r, i;
};

int main(int argc, char **argv) {
    cin.sync_with_stdio(false), cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<mint> a(n);

    for (int i = 0, x; i < n; i++) {
        cin >> x, a[i] = x;
    }

    vector<Query> query(m);

    for (int i = 0; i < m; i++) {
        cin >> query[i].l >> query[i].r;
        --query[i].l, --query[i].r;
        query[i].i = i;
    }

    sort(query.begin(), query.end(), [&](const auto& x, const auto& y) {
        return x.r < y.r;
    });

    vector<mint> ans(m);
    vector<pair<int, int>> min_stack, max_stack;
    segment_tree sgt(n);

    sgt.build(1, 0, n - 1, a);

    for (int r = 0, i = 0; r < n; r++) {
        while (!min_stack.empty() && min_stack.back().first >= int(a[r])) {
            int high = min_stack.back().second;
            for (auto v: min_stack) cout << "->" << v.first << "," << v.second; cout << endl;
            min_stack.pop_back();
            int low = min_stack.empty() ? 0 : (min_stack.back().second + 1);
            cout << "min:" << low << "," << high << endl;
            const mint& old_val = a[high], new_val = a[r];
            sgt.update(low, high, 1, 0, n - 1, old_val, new_val, r);
        }
        min_stack.push_back({ int(a[r]), r });
        while (!max_stack.empty() && max_stack.back().first <= int(a[r])) {
            for (auto v: max_stack) cout << "->" << v.first << "," << v.second; cout << endl;
            int high = max_stack.back().second;
            max_stack.pop_back();
            int low = max_stack.empty() ? 0 : (max_stack.back().second + 1);
            const mint& old_val = a[high], new_val = a[r];
            cout << "max:" << low << "," << high << endl;
            sgt.update(low, high, 1, 0, n - 1, old_val, new_val, r);
        }
        max_stack.push_back({ int(a[r]), r });

        while (i < m && query[i].r == r) {
            ans[query[i].i] = sgt.query(query[i].l, query[i].r, 1, 0, n - 1, r);
            ++i;
        }
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
}
/*
5 4
3 1 2 5 4
1 5
2 4
1 3
1 4
*/