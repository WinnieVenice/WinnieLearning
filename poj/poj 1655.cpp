#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod=7+1e9;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b,ll p){a%=p; ll ret=1;for(;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p; return ret;}
ll getInv(ll x,ll p){return qpow(x,p-2,p);}
const int N=5+2e4;
int n;
vector<int> G[N];
int rt,sz[N],mx[N];
void dfs(int x,int f){
    sz[x]=1;
    for(int i=0;i<(int)G[x].size();i++){
        int v=G[x][i];
        if(v!=f){
            dfs(v,x);
            sz[x]+=sz[v];
            mx[x]=max(mx[x],sz[v]);
        }
    } 
    mx[x]=max(mx[x],n-sz[x]);
    if(!rt||mx[rt]>mx[x]) rt=x;
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) G[i].clear(),mx[i]=0;
    for(int i=1;i<n;i++){
        int u,v; cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    rt=0;
    dfs(1,0);
    cout<<rt<<' '<<mx[rt]<<'\n';
}
int main(){
     int T; cin>>T;
     while(T--) solve();
}