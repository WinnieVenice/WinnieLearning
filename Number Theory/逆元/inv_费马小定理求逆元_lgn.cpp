#define ll long long 
ll qpow(ll a,ll p,ll mod){ll res=1;a%=mod;assert(p>=0);for(;p;p>>=1){if(p&1) res=res*a%mod;a=a*a%mod;}return res;}
ll inv(ll a,ll p){return qpow(a,p-2,p);}