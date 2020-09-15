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
    ll n,a,b,p,q; scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&p,&q);
    //p*(n/a)+q*(n/b)-min(p,q)*(n/lcm(a,b));
    ll ret=p*(n/a);
    ret-=min(p,q)*(n/lcm(a,b));
    ret+=q*(n/b);
    printf("%lld\n",ret);
}