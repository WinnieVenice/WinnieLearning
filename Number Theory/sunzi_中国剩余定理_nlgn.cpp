/*
有方程组: x = a_i ( mod m_i)  ,其中a_i为整数,m_i为正整数
如果上述方程中的m_i两两互质,则方程组的通解为:
x=k*(m_1*m_2*...*m_n)+sum(i)(a_i*M_i*M_i^(-1))   , 其中M_i=m_1*m_2*...*m_(i-1)*m_(i+1)*...m_n
 */
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
ll sunzi(ll *m,ll *a,int len){
    ll lcm=1,ans=0;
    for(int i=0;i<len;i++){
        ll k0,ki;
        ll d=exgcd(lcm,m[i],k0,ki);
        if((a[i]-ans)%d!=0)
            return -1;
        else{
            ll t=m[i]/d;
            k0=(k0*(a[i]-ans)/d%t+t)%t;
            ans=k0*lcm+ans;
            lcm=lcm/d*m[i];
        }
    }
    return ans;
}