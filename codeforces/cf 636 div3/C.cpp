#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod=7+1e9;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b,ll p){a%=p; ll ret=1;for(;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p; return ret;}
ll getInv(ll x,ll p){return qpow(x,p-2,p);}
void solve(){
    int n; scanf("%d",&n);
    vector<ll> a(n);
    for(auto &v:a) scanf("%lld",&v);
    ll ret=0;
    for(int i=0;i<n;){
        if(a[i]>0&&i<n){
            ll mx=-1e9L;
            for(;a[i]>0&&i<n;i++) mx=max(mx,a[i]);
            ret+=mx;
        }
        if(a[i]<0&&i<n){
            ll mx=-1e9L;
            for(;a[i]<0&&i<n;i++) mx=max(mx,a[i]);
            ret+=mx;
        }
    }
    printf("%lld\n",ret);
}
int main(){
    int t; scanf("%d",&t);
    while(t--) solve();
}