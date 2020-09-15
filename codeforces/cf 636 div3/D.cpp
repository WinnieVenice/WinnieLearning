#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod=7+1e9;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b,ll p){a%=p; ll ret=1;for(;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p; return ret;}
ll getInv(ll x,ll p){return qpow(x,p-2,p);}
const int N=5+2e5;
ll a[N],pf[N<<1],cnt[N<<1];
void solve(){
    int n,k; scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%lld",a+i);
    for(int i=1;i<=2*k;i++) pf[i]=0;
    for(int i=1;i<=n/2;i++) cnt[a[i]+a[n-i+1]]++;
    for(int i=1;i<=n/2;i++){
        pf[min(a[i],a[n-i+1])+1]++;
        pf[max(a[i],a[n-i+1])+k+1]--;
    }
    for(int i=1;i<=2*k;i++) pf[i]+=pf[i-1];
    ll mi=1e9L;
    for(int i=2;i<=2*k;i++) mi=min(mi,n-cnt[i]-pf[i]);
    printf("%lld\n",mi);
    for(int i=1;i<=n/2;i++) cnt[a[i]+a[n-i+1]]=0;
}
int main(){
    int t; scanf("%d",&t);
    while(t--) solve();
}