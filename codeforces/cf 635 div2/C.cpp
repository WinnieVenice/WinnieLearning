#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5+2e5;
vector<int> G[N];
ll sz[N],dep[N];
void dfs(int x,ll dp,int fa){
    sz[x]=1;
    dep[x]=dp;
    for(auto v:G[x])
        if(v!=fa){
            dfs(v,dp+1,x);
            sz[x]+=sz[v];
        }
}
int main(){
    int n,k; scanf("%d %d",&n,&k);
    for(int i=1;i<n;i++){
        int u,v; scanf("%d %d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,0,0);
    priority_queue<ll,vector<ll>,greater<ll>> q;
    for(int i=1;i<=n;i++)
        if(q.size()<k) q.push(dep[i]-sz[i]+1);
        else q.push(dep[i]-sz[i]+1),q.pop();
    ll ret=0;
    for(;q.size();q.pop()) ret+=q.top();
    printf("%lld\n",ret);
}