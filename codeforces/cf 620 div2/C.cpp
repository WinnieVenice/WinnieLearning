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
#define fio ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define EXIT exit(0)
#define all(a) (a).begin(),(a).end()
//loop 
#define For(i,a,b) for(int i=(a);i<(b);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define cFor(i,a,b) for(int i=(a);i>(b);i--)
#define cFOR(i,a,b) for(int i=(a);i>=(b);i--)
#define lFor(i,a,b) for(ll i=(a);i<(b);i++)
#define lFOR(i,a,b) for(ll i=(a);i<=(b);i++)
#define lcFor(i,a,b) for(ll i=(a);i>(b);i--)
#define lcFOR(i,a,b) for(ll i=(a);i>=(b);i--)
//debug
#define dbg(a) cout<<#a<<"="<<a<<endl
#define inthis cout<<"--------this\n"
//operator
#define pb push_back
#define ins insert
#define era erase
#define fin find 
//pair
#define pr pair
#define mkp(a,b) make_pair(a,b)
#define fi first
#define se second
//vector
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
//map
#define mp map
////map int
#define mpii map<int,int>
#define mpib map<int,bool>
#define mpic map<int,char>
#define mpis map<int,string>
#define mpil map<int,long long>
////map long long 
#define mpll map<long long,long long>
#define mplb map<long long,bool>
#define mplc map<long long,bool>
#define mpls map<long long,string>
#define mpli map<long long,int>
////map char
#define mpci map<char,int>
#define mpcb map<char,bool>
#define mpcl map<char,long long>
////map string
#define mpsi map<string,int>
#define mpsb map<string,bool>
#define mpsl map<string,long long>
//iterator
#define ivec(a) vector<a>::iterator
#define iset(a) set<a>::iterator 
#define imp(a,b) map<a,b>::iterator

using namespace std;
/*
const int maxsize=
struct edge{
	int nod,nxt;
			
}e[maxsize<<1];
int nume=0,pa[maxsize],head[maxsize];
void add(int u,int v){
	e[++nume].nod=v;
	e[nume].nxt=head[u];
	head[u]=nume;
}
void init(){
	
}
bool vis[maxsize];
void bfs(){
	
}
void dfs(){

}
*/
const int maxn=5+1e2;
vec<pr<int,pr<int,int>>> a;
int dp[maxn][2];
void solve(){
	a.clear();
	int n,m;
	cin>>n>>m;
	//当前最多能高到多少度，最低能低到多少度
	//每次判断都只用O(1)check一下,行就继续,不行直接break,Prin NO 
	//dp[idx][lower/higher]=temperture
	//d=(t[i]-t[i-1]) 
	//转移方程:dp[i][0]=dp[i-1][2]-d ; dp[i][1]=dp[i-1][2]+d 
	//check:lower=dp[i-1][2]-d,higher=dp[i][2]+d
	//
	//if(dp[])
	a.pb(mkp(0,mkp(m,m)));
	For(i,0,n){
		int t,l,h;
		cin>>t>>l>>h;
		a.pb(mkp(t,mkp(l,h))); 
	} 
	sort(all(a));
	dp[0][0]=dp[0][1]=m;
	For(i,1,a.size()){
		int d=a[i].fi-a[i-1].fi;
		if(dp[i-1][1]+d<a[i].se.fi||dp[i-1][0]-d>a[i].se.se){
			cout<<"NO\n";
			return;
		}
		dp[i][0]=max(dp[i-1][0]-d,a[i].se.fi);
		dp[i][1]=min(dp[i-1][1]+d,a[i].se.se);
		if(dp[i][1]<dp[i][0])
			dp[i][1]=dp[i][0];
	}
	cout<<"YES\n";
}
int main(){
	fio;
	int q;
	cin>>q;
	while(q--)
		solve();
}