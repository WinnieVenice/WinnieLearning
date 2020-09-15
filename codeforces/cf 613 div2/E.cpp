/*
cf round #613 div.2
E:解法2: 
*/
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
#include<string>
#include<utility>
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
const int maxn=7+4e5;
int n;
pair<int,int> a[maxn];
int ans[maxn];
void solve(){
	cin>>n;
	FOR(i,1,n){
		rint l,r;
		cin>>l>>r;
		a[2*i-1]=make_pair(l,-i);//奇数装左端点 
		a[2*i]=make_pair(r,i);//偶数装右端点 
		ans[i]=0;//初始化ans 
	}
	sort(a+1,a+2*n+1);//对a排序 
	multiset<int> s;
	rint c=0;
	FOR(i,1,2*n){
		if(a[i].second<0)
			s.insert(-a[i].second);
		else
			s.erase(s.find(a[i].second));
		if(s.size()==0)
			c++;
		if(s.size()==1&&a[i].second>0&&a[i+1].second<0&&a[i+1].first>a[i].first)
			ans[*s.begin()]++;
		if(s.size()==1&&a[i].second<0&&a[i+1].second>0)
			ans[*s.begin()]--;							
	}
	rint Ans=-n;
	FOR(i,1,n)
		Ans=max(Ans,ans[i]);
	cout<<c+Ans<<endl;	
}
int main(){
	fio;
	rint t;
	cin>>t;
	while(t--)
		solve();
} 
