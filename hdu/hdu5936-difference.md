# hdu5936-Difference

折半枚举、二分

## 题目

Little Ruins is playing a number game, first he chooses two positive integers y and K and calculates f(y,K), here

$$f(y,K)=\sum_{z\ in\ every\ digits\ of\ y}z^{k}$$

example:

$f(233,2)=2^2+3^2+3^2=22$

then he gets the result:

$x=f(y,K)-y$

As Ruins is forgetful, a few seconds later, he only remembers $K$, $x$ and forgets $y$. please help him find how many $y$ satisfy $x=f(y,K)−y$.

### 输入

First line contains an integer T, which indicates the number of test cases.

Every test case contains one line with two integers x, K.

Limits
$1≤T≤100$
$0≤x≤10^9$
$1≤K≤9$

### 输出

For every test case, you should output **'Case #x: y'**, where **x** indicates the case number and counts from **1** and **y** is the result.

## 分析

$$
\because x\in[0,10^9]
\\\therefore y=\begin{matrix}\underbrace{\overline{a_0a_1...a_{\lambda-1}a_{\lambda}}}\\len\end{matrix},len\in[0,10^9]
\\显然暴力枚举a_i会TLE，但是如果我们能把枚举的份数分开来，就可能ok.
\\考虑将枚举的a_i分成两份
\\\because f(y,K)=\sum_{z\ every\ digits\ of\ y}z^K
\\\therefore f(\overline{a_0a_1...a_{\lambda-1}a_{\lambda}},K)=f(\overline{a_0'a_1'...a_{\lambda-1}'a_{\lambda}'},K)
\\\Rightarrow f(\overline{a_0a_1...a_{\lambda-1}a_{\lambda}},K)=f(\overline{a_0a_1...a_{\lfloor\frac{\lambda}{2}\rfloor}},K)+f(\overline{a_{\lfloor\frac{\lambda}{2}\rfloor+1}...a_{\lambda-1}a_{\lambda}},K)
\\\Rightarrow x=f(y,K)-y\Leftrightarrow x+\overline{a_0...a_{\lfloor\frac{\lambda}{2}\rfloor}}-f(\overline{a_0...a_{\lfloor\frac{\lambda}{2}\rfloor}},K)=f(\overline{a_{\lfloor\frac{\lambda}{2}+1\rfloor}...a_{\lambda}})-\overline{a_{\lfloor\frac{\lambda}{2}+1\rfloor}...a_{\lambda}}
\\不难可以看出,对于每份我们暴力枚举10^5的量就ok,考虑下用map之类的存其中一份的答案,那总的复杂度就是O(10^5log_2(10^5))。
$$

### 注意

$$
这里有个基础的桶的思想，对于一条等式或者不等式f<=>0,假设存在f\leftrightarrow g+h,则f=0\leftrightarrow g<=>-h。
\\那么我们算出并存下所有的g，然后我们再算h，对于每个h，我们从存储g的答案中算出该h的贡献
$$



## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod=7+1e9;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b,ll p){a%=p; ll ret=1;for(;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p; return ret;}
ll getInv(ll x,ll p){return qpow(x,p-2,p);}
const int inf=1e9;
ll base[10];
void solve(){
    ll x; int k; scanf("%lld %d",&x,&k);
    for(int i=0;i<=9;i++){
        base[i]=1;
        for(int j=0;j<k;j++) base[i]*=i;
    }
    vector<ll> ck(100000);
    for(int i=0;i<100000;i++){
        ll sum=x+i;
        for(int j=i;j;j/=10) sum-=base[j%10];
        ck[i]=sum;
    }
    sort(ck.begin(),ck.end());
    ll ans=0;
    for(int i=0;i<100000;i++){
        ll sum=-i*100000;
        for(int j=i;j;j/=10) sum+=base[j%10];
        ans+=upper_bound(ck.begin(),ck.end(),sum)-lower_bound(ck.begin(),ck.end(),sum);
    }
    printf("%lld\n",ans-(x==0));
}
int main(){
    int t; scanf("%d",&t);
    for(int i=1;i<=t;i++){
        printf("Case #%d: ",i);
        solve();
    }
}
```

