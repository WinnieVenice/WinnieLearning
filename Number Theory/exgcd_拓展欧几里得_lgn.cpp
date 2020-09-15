#define ll long long
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