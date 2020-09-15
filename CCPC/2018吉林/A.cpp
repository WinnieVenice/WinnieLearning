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
    ll n; cin>>n;
    ll ans=0;
    for(ll l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        ans+=1ll*(r-l+1)*(n/l);
    }
    cout<<(ans%2==0?"even":"odd")<<'\n';
}
int main(){
     int T; cin>>T;
     for(int i=1;i<=T;i++){
         cout<<"Case "<<i<<": ";
         solve();
     }
}