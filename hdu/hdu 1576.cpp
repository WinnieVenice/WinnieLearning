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
#define mkp(a,b) make_pair(a,b)
#define inthis cout<<"--------this\n"
#define pr(a,b) pair(a,b)
#define iset(a) set<a>::iterator 
#define imap(a,b) map<a,b>::iterator 
#define vec vector
#define fi first
#define se second
#define _vec vector<int>
#define __vec vector<vector<int>> 
#define pb push_back
#define mp map
#define _pr pair<int,int>
#define ins insert
#define era erase
#define fin find
#define EXIT exit(0)
#define all(a) a.begin(),a.end()
using namespace std;
const int inf=9973;
ll qpow(ll a,ll p,ll MOD){
	ll ans=1,tmp=a;
	while(p){
		if(p&1)
			ans=ans*tmp%MOD;
		tmp=tmp*tmp%MOD;	
		p>>=1;
	}
	return ans; 
}
void solve(){
	int z,y;
	cin>>z>>y;
	cout<<z*qpow(y%inf,inf-2,inf)%inf<<endl;	
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
		solve();
}
