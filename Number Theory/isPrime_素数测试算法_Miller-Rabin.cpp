/*
如果n极大,可以使用素数测试算法,素数测试算法可以通过控制迭代次数来间接控制正确率,常用的有下面的Miller-Rabin方法
当然Rand()可以自由发挥,会影响性能 
*/
#define ll long long
ll qpow(ll a,ll b,ll p){a%=p;ll ans=1;for(;b;b>>=1){if(b&1)ans=ans*a%p;a=a*a%p;}return ans;}
ll Rand(){
    static ll x=(srand((int)time(0)),rand());
    x+=1000003;
    if(x>1000000007)x-=1000000007;
    return x;
}
bool Witness(ll a,ll n){
    ll t=0,u=n-1;
    while(!(u&1)){
        u>>=1;
        t++;
    }
    ll x=qpow(a,u,n),y;
    while(t--){
        y=x*x%n;
        if(y==1&&x!=1&&x!=n-1)
            return true;
        x=y;
    }
    return x!=1;
}