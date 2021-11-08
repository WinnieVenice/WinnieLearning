# Miu(n)

## Solution

$$
F(n) = \sum_{i=1}^n\mu(i)
\\\because \sum_{d|n}\mu(d)=\begin{cases}\ 1, n=1\\\ 0,others\end{cases}
\\n>1,0=\sum_{d|n}\mu(d)=\sum_{d|n}\mu(n/d)
\\n>1,\mu(n)=-\sum_{d|n,d>1}\mu(d)
\\\therefore F(n)=\sum_{i=1}^n\mu(i)=1-\sum_{i=1}^n\sum_{d|i,d>1}\mu(d)
\\\Rightarrow=1-\sum_{i=1}^n\sum_{d=2}^n\mu(d)[d|i]
\\=1-\sum_{d=2}^n\mu(d)\sum_{i=1}^n[d|i]
\\=1-\sum_{d=2}^n\mu(d)\lfloor\frac{n}{d}\rfloor
\\=1-\sum_{l=2,r=n/(n/l)}^{l<=n}\mu(n/l)*(r-l+1)
$$

## Code

```
#include<bits/stdc++.h>
using namespaces std;
const int N = 5 + 1e6; //sqrt_n~n^{2/3}
bool np[N];
int tot, pri[N];
int miu[N];
void seive(int n) {
	np[1] = 1;
	miu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!np[i]) {
			pri[++tot] = i;
			miu[i] = -1;
		}
		for (int j = 1; j <= tot && i * pri[j] <= n; j++) {
			np[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				break;
			}
			miu[i * pri[j]] = -miu[i];
		}
	}
	for (int i <= 2; i <= n; i++) {
		miu[i] += miu[i - 1];
	}
}
int sqrt_n;
unordered_map<long long, int> s_m;
int djs_miu(long long x) {
	if (x < sqrt_n) return miu[x];
	if (s_m[x]) return s_m[x];
	int res = 1;
	for (long long l = 2, r; l <= x; l = r + 1) {
		long long d = x / l; r = x / d;
		res -= (r - l + 1) * djs_miu(d);
	}
	return s_m[x] = res;
}
```

