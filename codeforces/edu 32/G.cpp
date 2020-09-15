#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod=7+1e9;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b,ll p){a%=p; ll ret=1;for(;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p; return ret;}
ll getInv(ll x,ll p){return qpow(x,p-2,p);}
int main(){
    int n; ll m; scanf("%d%lld",&n,&m);
    vector<ll> a(n);
    for(auto &v:a) scanf("%lld",&v);
    ll ans=-1;
    vector<ll> ck(1<<(n/2));
    int tot=0;
    for(int i=1;i<1<<(n/2);i++){
        ll sum=0;
        for(int j=0;j<n/2;j++){
            if((i>>j)&1){
                (sum+=a[j])%=m;
            }
        }
        ans=max(ans,sum);
        ck[tot++]=sum;
    }
    sort(ck.begin(),ck.end());
    for(int i=0;i<1<<(n-n/2);i++){
        ll sum=0;
        for(int j=0;j<(n-n/2);j++){
            if((i>>j)&1){
                (sum+=a[n/2+j])%=m;
            }
        }
        ans=max(ans,sum);
        auto p=lower_bound(ck.begin(),ck.end(),m-1-sum);
        if(p!=ck.end()) ans=max(ans,(sum+*p)%m);
        if(p!=ck.begin()){
            p--;
            ans=max(ans,(sum+*p)%m);
        }
    }
    printf("%lld\n",ans);
}