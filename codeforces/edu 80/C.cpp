#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<map>
#include<ctime>
#include<algorithm>
#include<cmath>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<bitset>
#define ll long long 
#define ull unsigned long long 
#define mem(a) memset(a,0,sizeof(a))
#define rint register int 
#define rll register long long 
#define rull register unsigned long long 
#define rchar register char
#define rstring register string 
#define rfloat register float
#define rdouble register double 
#define fio ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define For(i,a,b) for(int i=a;i<b;i++)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define cFor(i,a,b) for(int i=a;i>b;i--)
#define cFOR(i,a,b) for(int i=a;i>=b;i--)
#define lFor(i,a,b) for(ll i=a;i<b;i++)
#define lFOR(i,a,b) for(ll i=a;i<=b;i++)
#define lcFor(i,a,b) for(ll i=a;i>b;i--)
#define lcFOR(i,a,b) for(ll i=a;i>=b;i--)
#define watch(a) cout<<#a<<"="<<a<<endl
using namespace std;

const int inf=7+1e9,maxn=5000;
ll dp[maxn];
ll qpow(ll a,ll p,int mod){
	ll tmp=a,res=1;
	while(p){
		if(p&1)
			res=res*tmp%mod;
		tmp=tmp*tmp%mod;
		p>>=1;	
	}
	return res;
}
ll c(int n,int m){
	return dp[n]*qpow(dp[m]*dp[n-m]%inf,inf-2,inf)%inf; 
}
int main(){
	fio;
	int n,m;
	cin>>n>>m;
	dp[0]=dp[1]=1;
	FOR(i,2,maxn)
		dp[i]=dp[i-1]*i%inf;
	cout<<c(n+2*m-1,2*m)<<endl;
} 