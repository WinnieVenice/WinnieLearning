# luogu-p1291

期望dp

## 题意

有n个不同的名字，抽到每个名字出现的概率相同，问平均要多少次才能抽到所有名字。

## 分析

$$
显然是道求期望的题。
\\期望的原式不难知为=\sum_{i=0}^{\infty}{C_i^n*(\frac{1}{n})^n*(1-\frac{1}{n})^{i-n}}
\\很难求，所以考虑dp
\\由于期望dp一般逆推，所以我们设f_i=还差i个不同的名字的期望答案
\\显然f_n=0,考虑f_i:有两部分组成，一部分是刚好抽一次抽到转移过来，另一部分是刚好抽一次没有抽到
\\显然其他情况能通过有序化，划分到这两种情况，比如抽两次才抽到，则可以变成10、01，10就是第二情况，01就是第一情况（1=抽到，0=没抽到)
\\故：f_i=\left[(\frac{i+1}{n}）*(f_{i+1}+1)\right]+\left[(1-\frac{i+1}{n})*(f_i+1)\right]
\\\Rightarrow f_i=f_{i+1}+\frac{n}{i+1}
\\-----------------------------------------------------
\\考虑一下顺推,由于上面有了逆推，所以顺推的方式和逆推的有点像，设f_i=已经抽到了i个不同的名字的期望,则:
\\f_i=\left[(1-\frac{i-1}{n})*(f_{i-1}+1)\right]+\left[(\frac{i-1}{n})*(f_i+1)\right]
\\\Rightarrow f_i=f_{i-1}+\frac{n}{n-i+1}
\\-----------------------------------------------------
\\事实上还有更宽泛一点的推法:一样的f_i定义
\\考虑f_{i-1}\rightarrow f_i是第k次才抽到第i个不同名字的，则：
\\由于期望是线性函数,即：E(a+b)=E(a)+E(b),则：
\\\begin{align}
\\f_i&=f_{i-1}+\sum_{k=1}^{\infty}{(1-\frac{i-1}{n})*(\frac{i-1}{n})^{k-1}*k}
\\(\frac{i-1}{n})*f_i&=(\frac{i-1}{n})*f_{i-1}+\sum_{k=1}^{\infty}{(1-\frac{i-1}{n})*(\frac{i-1}{n})^k*k}
\\错位相减:(1-\frac{i-1}{n})*f_i&=(1-\frac{i-1}{n})*f_{i-1}+(1-\frac{i-1}{n})*(\frac{i-1}{n})^0*1+(1-\frac{i-1}{n})*\sum_{k=2}^{\infty}{(\frac{i-1}{n})^{k-1}*[k-(k-1)]}
\\\Rightarrow f_i&=f_{i-1}+1+\sum_{k=1}^{\infty}{(\frac{i-1}{n})^{k}}
\\ f_i&=f_{i-1}+1+\frac{(\frac{i-1}{n})*\left[1-(\frac{i-1}{n})^{\infty}\right]}{1-\frac{i-1}{n}}
\\ f_i&=f_{i-1}+\frac{n}{n-i+1}
\\\end{align}
$$

## 代码

```C++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll gcd(ll x,ll y){ return y?gcd(y,x%y):x; }
ll lcm(ll x,ll y){ return x/gcd(x,y)*y; }
pair<ll,ll> mul(pair<ll,ll> x,pair<ll,ll> y){
    ll l=lcm(x.second,y.second);
    return {l/x.second*x.first+l/y.second*y.first,l};
}
const int N=35;
pair<ll,ll> f[N];

int main(){
	ll n; cin>>n;
    for(int i=0;i<=n;i++){
        f[i]=make_pair(0,1);
    }
    for(int i=n-1;i>=0;i--){
        f[i]=mul(f[i+1],{n,i+1});
    }
    ll g=gcd(f[0].first,f[0].second);
    ll a=f[0].first/g,b=f[0].second/g;
    if(b==1){
        cout<<a<<endl;
    }else{
        int cnt[2]={0,0};
        for(ll i=b;i;i/=10){ cnt[0]++; }
        for(ll i=a/b;i;i/=10){ cnt[1]++; }
        for(int i=0;i<cnt[1];i++){ cout<<' '; }
        cout<<a%b<<endl;
        cout<<a/b;
        for(int i=0;i<cnt[0];i++){ cout<<'-'; }
        cout<<endl;
        for(int i=0;i<cnt[1];i++){ cout<<' '; }
        cout<<b<<endl;
    }
}
```

