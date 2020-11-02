#include<bits/stdc++.h>
using namespace std;

namespace MR{
    // 18位素数：154590409516822759
    // 19位素数：2305843009213693951 (梅森素数)
    // 19位素数：4384957924686954497
    long long  prime[11] = {2,3,5,7,233,331,11,13,17,19,23};
    long long  mi;
    // 乘法防止溢出， 如果p * p不爆LL的话可以直接乘； O(1)乘法或者转化成二进制加法
    long long qmul(long long x,long long y,long long mod){ return (x*y-(long long)(x/(long double)mod*y+1e-3)*mod+mod)%mod; }
    long long qpow(long long a,long long b,long long mod){ long long ret=1; for(;b;a=qmul(a,a,mod),b>>=1) if(b&1) ret=qmul(ret,a,mod); return ret; }
    bool M_R(long long p){//传入值，返回0即为合数，犯为1即为质数，范围可测到ll范围
        if(p==2) return 1;
        if(p<2||!(p&1)) return 0;
        long long s=p-1;
        while(!(s&1)) s>>=1;
        for(int i=0;i<11;++i) {
            if(p==prime[i]) return 1;
            long long t=s,m=qpow(prime[i],s,p);
            while(t!=p-1&&m!=1&&m!=p-1){
                m=qmul(m,m,p);
                t<<=1;
            }
            if(m!=p-1&&!(t&1)) return 0;
        }
        return 1;
    }
    long long f(long long x,long long mod,int a){ return ((__int128)x*x+a)%mod; }
    long long find_factorplus(long long N,long long seed){
        long long a=rand(),b=a,p;
        do{
            a = f(a,N,seed);
            b = f(f(b,N,seed),N,seed);
            p = __gcd( abs( b - a ) , N);
            if( p > 1&&p<N) return p;
        }while(b!=a);
        return 0;
    }
    void p_r(vector<long long> &cnt,long long x){
        while((x&1)==0) cnt.push_back(2),x>>=1;
        if(x==1) return;
        if(M_R(x)) return cnt.push_back(x),void();
        long long p=0;
        while(p==0){
            long long seed=1+rand()%(x-1);
            p=find_factorplus(x,seed);
        }
        p_r(cnt,p),p_r(cnt,x/p);
    }
}
void solve(){
    srand((unsigned)time(NULL));
    long long n; cin>>n; 
    vector<long long> res;

    MR::p_r(res,n);
    
    map<long long,int> cnt;
    for(auto v:res) cnt[v]++;
    for(auto v:cnt)
        if(v.second>1){
            puts("yes");
            return;
        }
    puts("no");
}
int main(){
    int T; cin>>T;
    while(T--) solve();
}