#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    static int a[300005];

    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }

    for (int i = 1; i <= q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);

        int64_t ans = 0;
        const int MOD = 998244353;

        for (int j = l; j <= r; j++) {
            int Max = INT_MIN, Min = INT_MAX;
            for (int k = j; k <= r; k++) {
                Min = min(Min, a[k]);
                Max = max(Max, a[k]);

                ans = (ans + int64_t(Min) * Max) % MOD;
            }
        }

        printf("%ld\n", ans);
    }
}