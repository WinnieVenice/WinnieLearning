#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mi;
ll f(ll x,ll y,ll z){return (x-y)*(x-y)+(y-z)*(y-z)+(z-x)*(z-x);}
void ans(vector<int> y,vector<int> x,vector<int> z){
    for(auto v:y){
        int r=lower_bound(z.begin(),z.end(),v)-z.begin();
        if(r==z.size()) return;
        int l=lower_bound(x.begin(),x.end(),v)-x.begin();
        while(l==x.size()||x[l]>v&&l) l--;
        if(!l&&x[l]>v) continue;
        mi=min(mi,f(v,x[l],z[r]));
    }
}
void solve(){
    mi=9e18L;
    int n,m,k; scanf("%d %d %d",&n,&m,&k);
    vector<int> r(n),g(m),b(k);
    for(auto &v:r) scanf("%d",&v);
    for(auto &v:g) scanf("%d",&v);
    for(auto &v:b) scanf("%d",&v);
    sort(r.begin(),r.end());
    sort(g.begin(),g.end());
    sort(b.begin(),b.end());
    ans(r,g,b);
    ans(r,b,g);
    ans(g,r,b);
    ans(g,b,r);
    ans(b,r,g);
    ans(b,g,r);
    printf("%lld\n",mi);
}
int main(){
    int t; scanf("%d",&t);
    while(t--) solve();
}