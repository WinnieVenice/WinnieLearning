#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5+1e5;
int n;
int col[maxn];
vector<int> G[maxn];
int root[maxn];
ll ans[maxn];
struct node{
    ll dep;
    int cnt,l,r;
}st[maxn*20];
int nump=0;
int init(int p,int l,int r,int deep){
    int idx=++nump;
    if(l==r){
        st[idx].dep=1ll*deep;
        st[idx].cnt=1;
    }else{
        int mid=(l+r)>>1;
        if(p<=mid)
            st[idx].l=init(p,l,mid,deep);
        else
            st[idx].r=init(p,mid+1,r,deep);
    }
    return idx;
}
pair<ll,int> merge(int x,int y,int l,int r,int deep){
    if(!x)
        return {0,y};
    if(!y)
        return {0,x};
    pair<ll,int> res={0,x};
    if(l==r){
        res.first+=1ll*st[x].cnt*st[y].dep+1ll*st[y].cnt*st[x].dep-2ll*deep*st[x].cnt*st[y].cnt;
        st[x].cnt+=st[y].cnt;
        st[x].dep+=st[y].dep;
    }else{
        int mid=(l+r)>>1;
        pair<ll,int> L=merge(st[x].l,st[y].l,l,mid,deep);
        pair<ll,int> R=merge(st[x].r,st[y].r,mid+1,r,deep);
        res.first+=L.first;
        res.first+=R.first;
        st[x].l=L.second;
        st[x].r=R.second;
    }
    return res;
}
void dfs(int cur,int fa,int dep){
    root[cur]=init(col[cur],1,n,dep);
    for(int i=0;i<G[cur].size();i++)
        if(G[cur][i]!=fa){
            dfs(G[cur][i],cur,dep+1);
            ans[cur]+=ans[G[cur][i]];//子树里面的贡献和
            pair<ll,int> tmp=merge(root[cur],root[G[cur][i]],1,n,dep);
            ans[cur]+=tmp.first;//子树间的贡献和
            root[cur]=tmp.second;
        }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>col[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,0,0);
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<' ';
}