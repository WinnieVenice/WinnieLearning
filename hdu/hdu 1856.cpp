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
const int maxn=5+1e7;
int pa[maxn]; 
int find(int x){
	if(x==pa[x])
		return x;
	return pa[x]=find(pa[x]);	
}
void merge(int x,int y){
	int pax=find(x),pay=find(y);
	if(pax!=pay)
		pa[pax]=pay;
}
mp<int,int> cnt;
mp<int,bool> nod;
int main(){
	fio;
	int n;
	while(cin>>n){
		cnt.clear();
		nod.clear();
		For(i,0,n){
			int x,y;
			cin>>x>>y;
			if(nod.fin(x)==nod.end()){
				pa[x]=x;
				nod.ins(mkp(x,1));
			}
			if(nod.fin(y)==nod.end()){
				pa[y]=y;
				nod.ins(mkp(y,1));
			}
			merge(x,y);
		}
		for(mp<int,bool>::iterator i=nod.begin();i!=nod.end();i++)
			find(i->fi);
		for(mp<int,bool>::iterator i=nod.begin();i!=nod.end();i++){
				if(cnt.fin(pa[i->fi])!=cnt.end())
					cnt.fin(pa[i->fi])->se+=1;
				else
					cnt.ins(mkp(pa[i->fi],1));
		}
		int mx=1;
		for(mp<int,int>::iterator i=cnt.begin();i!=cnt.end();i++)
			mx=max(mx,i->se);
		cout<<mx<<endl;			
	} 
}
