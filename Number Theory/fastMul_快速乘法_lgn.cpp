#define ll long long
ll fastMul(ll a,ll b,ll p){
    a%=p;
    ll ans=0;
    while(b>0){
        if(b&1)
            ans=(ans+a)%p;
        b>>=1;
        a=(a+a)%p;
    }
    return ans;
}