# ST表

## ST维护极值

```C++
namespace ST {
    #define T int
    vector<int> lg;
    vector<vector<T>> mx, mi;
    void init(vector<T> &a) {	//{a} in [1, n]
       	int n = a.size() - 1, lgn = int(log2(n));
        lg.resize(n + 1); mx.resize(n + 1, vector<int>(lgn + 1)); mi.resize(n + 1, vector<int>(lgn + 1));
        lg[0] = -1;
        for (int i = 1; i <= n; i++) { mx[i][0] = mi[i][0] = a[i]; lg[i] = lg[i >> 1] + 1; }
        for (int i = 1; i <= lg[n]; i++) {
            for (int j = 1; j + (1 << i) - 1 <= n; j++) {
                mx[j][i] = max(mx[j][i - 1], mx[j + (1 << (i - 1))][i - 1]);
                mi[j][i] = min(mi[j][i - 1], mi[j + (1 << (i - 1))][i - 1]);
            }
        }
    }
    T quemx(int l, int r) { int k = lg[r - l + 1]; return max(mx[l][k], mx[r - (1 << k) + 1][k]); }
    T quemi(int l, int r) { int k = lg[r - l + 1]; return min(mi[l][k], mi[r - (1 << k) + 1][k]); }
    #undef T
}
```

## ST维护区间和

```c++

```

