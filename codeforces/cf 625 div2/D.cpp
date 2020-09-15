#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5+2e5;
int n,m,k;
vector<int> G[maxn];
int p[maxn];
int d[maxn];
int cnt[maxn];
map<int,bool> ck[maxn];
bool vis[maxn];
void dijstra(int root){
    for(int i=1;i<=n;i++)
        d[i]=1e9L;
    memset(cnt,0,n*sizeof(int));
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    d[root]=0;
    q.push({0,root});
    while(q.size()){
        int cur=q.top().second;
        q.pop();
        for(int i=0;i<G[cur].size();i++){
            if(d[G[cur][i]]>=d[cur]+1){
                d[G[cur][i]]=d[cur]+1;
                cnt[G[cur][i]]++;
                if(ck[G[cur][i]].find(cur)==ck[G[cur][i]].end())
                    ck[G[cur][i]].insert({cur,1});
                if(!vis[G[cur][i]]){
                    vis[G[cur][i]]=1;
                    q.push({d[G[cur][i]],G[cur][i]});
                }            
            }
        }
    }
}
/*
p1->pk 最短路:
每次地图更新为当前点x->pk的最短路,所以我们可以转换思想pk->p1最短路
维护每个点p[x]到pk的最短距离:d[x]
同时我们还要维护每个点p[x]在最短路更新下会被考虑的次数:cnt[x]
也就是对于从每个点p[x]更新的最短路一共有多少条
考虑答案最小的情况:
    显然要尽可能走最短路,当前在p[x]上,如果是p[x+1]属于最短路上的点,否则mi++
考虑答案最大的情况：
    考虑p[x]是最短路上的点,然后下一个点是最短路的点有多少个,如果数量超过2个且p[x+1]是最短路上的点或者p[x+1]不是最短路的点,则mx++
因此我们要维护每个p[x+1]是不是p[x]最短路上的点,也就是在更新最短路的时候更新点: map<int,bool> ck
*/
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        G[v].push_back(u);
    }
    cin>>k;
    for(int i=1;i<=k;i++)
        cin>>p[i];
    dijstra(p[k]);
    int mi=0,mx=0;
    for(int i=1;i<k;i++){
        if(ck[p[i]][p[i+1]]&&cnt[p[i]]>1)
            mx++;
        else if(!ck[p[i]][p[i+1]]){
            mi++;
            mx++;
        }
    }
    cout<<mi<<' '<<mx<<endl;
}
