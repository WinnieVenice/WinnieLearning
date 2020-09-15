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
    int n; cin>>n;
    vector<int> a(n+1);
    vector<array<int,2>> dp(n+2,{INT_MAX,INT_MAX});
    for(int i=1;i<=n;i++) cin>>a[i];
    dp[1][1]=0; dp[1][0]=a[1];
    for(int i=1;i<=n;i++)
        for(int who=0;who<2;who++)
            for(int fight=1;fight<=min(n+1-i,2);fight++){
                int hard=a[i]+(fight>1?a[i+1]:0);
                dp[i+fight][!who]=min(dp[i+fight][!who],dp[i][who]+who*hard);
            }
    cout<<min(dp[n+1][0],dp[n+1][1])<<'\n';
}
int main(){
     int T; cin>>T;
     while(T--) solve();
}