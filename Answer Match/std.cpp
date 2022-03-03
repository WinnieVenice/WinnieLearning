#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
void debug() { cerr << endl; } template <typename T, typename... Ts> void debug(T x, Ts... y) { cerr << "\033[31m" << x << "\033[0m"; if (sizeof...(y) > 0) cerr << ' '; debug(y...); } template <typename T> void debug(const T& a, int l, int r, char c) { for (int i = l; i <= r; ++i) cerr << "\033[31m" << a[i] << "\033[0m" << (i == r ? '\n' : c); } template <typename T> void debug(vector<T> a) { for (int i = 0; i < (int)a.size(); ++i) cerr << "\033[31m" << a[i] << "\033[31m" << " \n"[i == ((int)a.size() - 1)]; }


const int N=5e5+5;
const int M=26;
int tr[N][M],tot;
int cnt[N],fail[N];
int id[N];
vector<int>e[N];
void trie(string s,int i){
  int u=0;
  for(auto it:s){
    int c=it-'a';
    if(!tr[u][c])tr[u][c]=++tot;
    u=tr[u][c];
  }
  ++cnt[u];
  id[i]=u;
}
void BF(){
  queue<int>q;
  for(int i=0;i<M;++i)if(tr[0][i])q.push(tr[0][i]);
  while(!q.empty()){
    int u=q.front();q.pop();
    for(int i=0;i<M;++i){
      if(tr[u][i]){
        fail[tr[u][i]]=tr[fail[u]][i];
        q.push(tr[u][i]);
      }else{
        tr[u][i]=tr[fail[u]][i];
      }
    }
    e[fail[u]].emplace_back(u);
  }
}
int sz[N],son[N];
void dfs(int u,int fa){
  sz[u]=1;
  for(auto v:e[u]){
    if(v==fa)continue;
    dfs(v,u);
    sz[u]+=sz[v];
    if(son[u]==0||sz[v]>sz[son[u]])son[u]=v;
  }
}
int col[N],ccol[N];
int ans[N];
int ma,BS;
void cal(int u,int fa,int f){
  ccol[col[u]]+=f*cnt[u];
  if(ccol[col[u]]>ma)ma=ccol[col[u]];
  for(auto v:e[u]){
    if(v!=fa&&v!=BS)cal(v,u,f);
  }
}
void dsu(int u,int fa,int op){
  for(auto v:e[u])
    if(v!=fa&&v!=son[u])dsu(v,u,0);
  if(son[u]){
    dsu(son[u],u,1);
    BS=son[u];
  }
  cal(u,fa,1);
  BS=0;
  ans[u]=ma;
  if(!op){
    cal(u,fa,-1);
    ma=0;
  }
}
signed main() {
  #ifdef BADDOG_LOCAL
    ofstream cout("E:\\acm dream\\2022 contest\\kizuna\\data\\10.out");
    ifstream cin("E:\\acm dream\\2022 contest\\kizuna\\data\\10.in");
  #endif
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  #ifdef BADDOG_LOCAL
  double be = clock();
  #endif

  int n;cin>>n;
  vector<string>s(n);
  for(auto &it:s)cin>>it;
  for(int i=0;i<n;++i)trie(s[i],i);
  for(int i=0;i<n;++i)cin>>col[id[i]];
  BF();
  dfs(0,-1);
  dsu(0,-1,1);
  for(int i=0;i<n;++i)cout<<ans[id[i]]<<endl;

  #ifdef BADDOG_LOCAL
  double en = clock();
  //cout<<"\ntime: "<<fixed<<setprecision(8)<<en-be;
  #endif
  return 0;
}
// init?
// var->0?
// infinite dfs?
// out of bound?
// max_element / min_element?