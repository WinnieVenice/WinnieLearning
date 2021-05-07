# poj2785-4values who sum is 0

折半枚举

## 题目

The SUM problem can be formulated as follows: given four lists A, B, C, D of integer values, compute how many quadruplet $(a, b, c, d ) ∈ A*B*C*D$ are such that $a + b + c + d = 0$ . In the following, we assume that all lists have the same size n .

## 分析

$$
a+b+c+d=0
\\=>a+b=-(c+d)
$$



## 代码

```c++
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod=7+1e9;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b,ll p){a%=p; ll ret=1;for(;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p; return ret;}
ll getInv(ll x,ll p){return qpow(x,p-2,p);}

int main(){
    int n; scanf("%d",&n);
    vector<ll> a(n),b(n),c(n),d(n);
    for(int i=0;i<n;i++) scanf("%lld%lld%lld%lld",&a[i],&b[i],&c[i],&d[i]);
    vector<ll> f(n*n);
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) f[i*n+j]=a[i]+b[j];
    sort(f.begin(),f.end());
    ll cnt=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            ll x=-(c[i]+d[j]);
            cnt+=upper_bound(f.begin(),f.end(),x)-lower_bound(f.begin(),f.end(),x);
        }    
    printf("%lld",cnt);
}
```

