#define ll long long
ll modMul(ll a,ll b,ll p){
    if(p<=(int)1e9)
        return a*b%p;
    else if(p<=1000000000000ll)
        return (((a*(b>>20)%p)<<20)+(a*(b&((1<<20)-1))))%p;
        else{
            ll d=(ll)floor(a*(long double)b/p+0.5);
            ll ret=(a*b-d*p)%p;
            if(ret<0)
                ret+=p;
            return ret;
        }
           
        
}