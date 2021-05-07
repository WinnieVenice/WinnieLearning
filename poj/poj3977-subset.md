# poj3977-subset

折半枚举

## 题目

Given a list of N integers with absolute values no larger than $10^{15}$, find a non empty subset of these numbers which minimizes the absolute value of the sum of its elements. In case there are multiple subsets, choose the one with fewer elements.

Input

The input contains multiple data sets, the first line of each data set contains N <= 35, the number of elements, the next line contains N numbers no larger than 1015 in absolute value and separated by a single space. The input is terminated with N = 0

Output

For each data set in the input print two integers, the minimum absolute sum and the number of elements in the optimal subset.

## 分析

$$
answer=|\sum_{x\in S}x|_{min}=|\sum_{x\in S}x+\sum_{y\in S}y|_{min}
\\\because |a|-|b|\leq|a+b|\leq|a|+|b|
\\\therefore上式=(|\sum_{x\in S}x|-|\sum_{y\in S}y|)_{min}
\\所以我们分开两半枚举，贪心处理每份枚举的贡献，再贪心处理两份枚举之间产生的贡献
$$



## 代码

```C++
#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod=7+1e9;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b,ll p){a%=p; ll ret=1;for(;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p; return ret;}
ll getInv(ll x,ll p){return qpow(x,p-2,p);}
ll ABS(ll x){return x<0?-x:x;}
int main(){
    int n;
    while(~scanf("%d",&n)&&n){
        vector<ll> a(n);
        for(int i=0;i<n;i++) scanf("%lld",&a[i]);
        map<ll,int> ck;
        pair<ll,int> ans=make_pair(ABS(a[0]),1);
        for(int i=1;i<1<<(n/2);i++){
            ll sum=0;
            int cnt=0;
            for(int j=0;j<n/2;j++)
                if((i>>j)&1){   
                    sum+=a[j];
                    cnt++;
                }
            ans=min(ans,{ABS(sum),cnt});
            if(ck[sum]) ck[sum]=min(ck[sum],cnt);
            else ck[sum]=cnt;
        }
        for(int i=1;i<1<<(n-n/2);i++){
            ll sum=0;
            int cnt=0;
            for(int j=0;j<n-n/2;j++)
                if((i>>j)&1){
                    sum+=a[n/2+j];
                    cnt++;
                }
            ans=min(ans,{ABS(sum),cnt});
            map<ll,int>::iterator p=ck.lower_bound(-sum);
            if(p!=ck.end()) ans=min(ans,{ABS(sum+p->first),cnt+p->second});
            if(p!=ck.begin()){
                p--;
                ans=min(ans,{ABS(sum+p->first),cnt+p->second});
            }
        }
        printf("%lld %d\n",ans.first,ans.second);
    }
}
```

