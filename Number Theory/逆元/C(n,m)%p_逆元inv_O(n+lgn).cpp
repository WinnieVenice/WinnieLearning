//代码中用O(n)的复杂度处理了[1,n]的逆元，处理Q次n,m<=N的询问的总复杂度为O(N+Q)
//空间O(n) 
#define ll long long
const ll mo=1e9+7;
const int N=1e6;
ll inv[N],mul[N],invMul[N];
ll C(ll n,ll m){
     ll M=0;
     while(M<=n){
         if(M){
            inv[M]=M==1?1:(mo-mo/M)*inv[mo%M]%mo;
            mul[M]=mul[M-1]*M%mo;
            invMul[M]=invMul[M-1]*inv[M]%mo;
         }else{
             mul[M]=1;
             invMul[M]=1;
         }
         M++;
     }
     return mul[n]*invMul[m]%mo*invMul[n-m]%mo;
}