#define ll long long
ll getPrime(ll n,bool vis[],ll prime[]){
    ll tot=0;
    for(ll i=1;i<=n;i++)
        vis[i]=0;
    for(ll i=2;i<=n;i++){
        if(!vis[i])
            prime[tot++]=i;
        for(ll j=0;j<tot;j++){
            if(prime[j]*i>n)
                break;
            vis[prime[j]*i]=1;
            if(i%prime[j]==0)
                break;
        }
    }
    return tot;
}