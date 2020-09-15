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
using namespace std;
const int maxn=5+1e5;
vector<ll> a;
ll dp(vector<ll> p,int bit){
	if(p.size()==0||bit<0)
		return 0;
	else{
		vector<ll> zero,one;
		For(i,0,p.size())
			if((p[i]>>bit)&1)
				one.push_back(p[i]);
			else
				zero.push_back(p[i]);
		if(!one.size())
			return dp(zero,bit-1);
		if(!zero.size())
			return dp(one,bit-1);
		return (1<<bit)+min(dp(one,bit-1),dp(zero,bit-1));					
	}
}
int main(){
	fio;
	rint n;
	cin>>n;
	FOR(i,1,n){
		ll x;
		cin>>x;
		a.push_back(x);
	}
	cout<<dp(a,30)<<endl;		
}