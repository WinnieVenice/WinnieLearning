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
const int inf=1e9,maxn=5+3e5;
int a[maxn][10];
int idx[10000];
int L,R;
int n,m;
bool check(int ans){
	mem(idx);
	FOR(i,1,n){
		int tmp=0;
		FOR(j,1,m)
			if(a[i][j]>=ans)
				tmp+=(1<<(j-1));
		idx[tmp]=i;
	}
	/*
	FOR(i,0,10000)
		if(idx[i])
			cout<<"idx["<<i<<"]="<<idx[i]<<' ';
	cout<<endl;		
	*/
	int pans=(1<<m)-1;
	FOR(i,0,(1<<m))
		FOR(j,0,(1<<m))
			if(idx[i]&&idx[j]&&(i|j)==pans){
				L=idx[i],R=idx[j];
				return true;
			}		
	return false;		
}
int main(){
	fio;
	cin>>n>>m;
	int l=inf,r=-inf;
	FOR(i,1,n)
		FOR(j,1,m){
			cin>>a[i][j];
			l=min(l,a[i][j]);
			r=max(r,a[i][j]);
		}	
	int ans=l;	
	while(r>=l){
		int mid=(r+l)>>1;
		if(check(mid))
			l=mid+1;
		else
			r=mid-1;
	}
	cout<<L<<' '<<R<<endl;				
} 