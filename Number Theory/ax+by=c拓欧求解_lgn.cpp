#define ll long long 
ll gcd(ll x,ll y){return y?gcd(y,x%y):x}
ll exgcd(ll a,ll b,ll &x,ll &y){
    ll d=a;
    if(!b)
        x=1,y=0;
    else{
        d=exgcd(b,a%b,y,x);
        y-=a/b*x;
    }
    return d;
}
pair<ll,ll> exgcd_solve(ll a,ll b,ll c){
    if(c%gcd(a,b)!=0)
        return {0,0};
    else{
        ll x,y;
        exgcd(a,b,x,y);
        return {x,y};
    }
}