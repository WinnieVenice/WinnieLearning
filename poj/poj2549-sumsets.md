# poj2549-Sumsets

折半枚举、二分

## 题目

Given S, a set of integers, find the largest d such that $a + b + c = d$ where a, b, c, and d are distinct elements of S.

Input

Several S, each consisting of a line containing an integer 1 <= n <= 1000 indicating the number of elements in S, followed by the elements of S, one per line. Each element of S is a distinct integer between -536870912 and +536870911 inclusive. The last line of input contains 0.

Output

For each S, a single line containing d, or a single line containing "no solution".

## 分析

$$
\because n\leq10^3
\\\therefore a+b+c=d
\\=>a+b=d-c
\\暴力枚举左右两边然后统计答案
$$



## 代码

```c++
#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<cstring>
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
	int n;
	while(~scanf("%d",&n)&&n){
		vector<ll> a(n);
		for(int i=0;i<n;i++) scanf("%lld",&a[i]);
		sort(a.begin(),a.end());
		vector<pair<ll,ll> > ck;
		int tot=0;
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++){
					ck.push_back({a[i]+a[j],a[i]});
			}
		sort(ck.begin(),ck.end());
		ll ans=-1e18L;
		bool ok=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(i!=j){
					ll sum=a[i]-a[j];
					for(vector<pair<ll,ll> >::iterator k=lower_bound(ck.begin(),ck.end(),pair<ll,ll> (sum,-1e18L));k!=upper_bound(ck.begin(),ck.end(),pair<ll,ll> (sum,1e18L));k++){
						ll l=k->first-k->second,r=k->second;
						if(k->first==sum&&l!=a[i]&&l!=a[j]&&r!=a[i]&&r!=a[j]) ans=max(ans,a[i]),ok=1;
					}
				}
		if(!ok) puts("no solution");
		else printf("%lld\n",ans);
	}
}
```

