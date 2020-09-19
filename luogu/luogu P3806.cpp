#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod=7+1e9;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b){ll ret=1;for(;b;b>>=1,a=a*a) if(b&1) ret=ret*a; return ret;}
const int N=5+1e4;
int n,m; 
vector<pair<int,int>> G[N];
int rt,sz[N],mx[N];
void cenceit(int x,int f){
    sz[x]=1;
    mx[x]=0;
    for(auto v:G[x])
        if(v.first!=f){
            cenceit(v.first,x);
            sz[x]+=sz[v.first];
            mx[x]=max(mx[x],sz[v.first]);
        }
    mx[x]=max(mx[x],n-sz[x]);
    if(mx[rt]>mx[x]) rt=x;
}
int tot,d[N],dis[N];
bool vis[N];
void path(int x,int f){
    d[++tot]=dis[x];
    for(auto v:G[x])
        if(v.first!=f&&!vis[v.first]){
            dis[v.first]=dis[x]+v.second;
            path(v.first,x);
        }
}
map<int,bool> ck;
queue<int> del;
bool ans[105];
int q[105];
void dfs(int x,int f){
    ck[0]=1;
    del.push(0);
    vis[x]=1;
    for(auto v:G[x])
        if(v.first!=f&&!vis[v.first]){
            dis[v.first]=v.second;
            path(v.first,x);
            for(int i=1;i<=tot;i++)
                for(int j=1;j<=m;j++){
                    if(q[j]>=d[i]) ans[i]|=ck[q[j]-d[i]];
                }
            for(int i=1;i<=tot;i++)        
                if(d[i]<=10000010) ck[d[i]]=1,del.push(d[i]);
        }
    while(del.size()) ck[del.front()]=0,del.pop();
    for(auto v:G[x])
        if(v.first!=f){
            rt=0;
            mx[rt]=INT_MAX;
            cenceit(v.first,x);
            cenceit(rt,-1);
            dfs(rt,x);
        }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v,w; cin>>u>>v>>w;
        G[u].push_back({v,w});
        G[v].push_back({u,w});
    } 
    for(int i=1;i<=m;i++) cin>>q[i];
    rt=0; mx[rt]=INT_MAX;
    cenceit(1,-1);
    cenceit(rt,-1);
    dfs(rt,-1);
    for(int i=1;i<=m;i++)
        cout<<(ans[i]?"AYE":"NAY")<<'\n';
}