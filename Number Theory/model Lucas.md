# model Lucas 

```C++
#define ll long long
const int mo=7+1e9;
const int N=5+1e5;
ll fac[N];
ll qpow(ll a,ll b,ll p){a%=p;ll ans=1;for(;b;b>>1){if(b&1)ans=ans*a%p;a=a*a%p;}return ans;}
void getFac(){
    fac[0]=1;
    for(int i=1;i<=mo;i++)
        fac[i]=(fac[i-1]*i)%mo;
}
ll Lucas(ll n,ll m,ll p){
    ll ans=1;
    while(n&&m){
        ll a=n%mo,b=m%mo;
        if(a<b)
            return 0;
        ans=(ans*fac[a]*qpow(fac[b]*fac[a-b]%mo,mo-2,mo))%mo;
        n/=mo;
        m/=mo;
    }
    return ans;
}
```

