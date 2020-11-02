#include<bits/stdc++.h>
using namespace std;

namespace MR{
    const int times=50;
    // 乘法防止溢出， 如果p * p不爆LL的话可以直接乘； O(1)乘法或者转化成二进制加法
    long long qmul(long long x,long long y,long long mod){ return (x*y-(long long)(x/(long double)mod*y+1e-3)*mod+mod)%mod; }
    long long qpow(long long a,long long b,long long p){a%=p; long long ret=1;for(;b;b>>=1,a=qmul(a,a,p)) if(b&1) ret=qmul(ret,a,p); return ret; }
    bool Miller_Rabin(long long n){
        if(n<3) return n==2;
        long long u=0,v=n-1;
        while(v%2==0) u++,v>>=1;
        for(int i=0;i<times;i++){
            long long w=2+rand()%(n-2),x=qpow(w,v,n);
            if(x==1||x==n-1) continue;
            int j;
            for(j=0;j<u;j++){
                x=qmul(x,x,n);
                if(x==n-1) break;
            }
            if(j>=u) return 0;
        }
        return 1;
    }
    long long f(long long x,long long c,long long mod){ return ((__int128)x*x+c)%mod; }
    long long find_factor(long long p){
        long long x,y,z,c=0,g; int i,j;
        while(1){
            y=x=rand()%p;
            z=1; c++;
            i=0,j=1;
            while(++i){
                x=f(x,c,p);
                z=(__int128)z*abs(y-x)%p;
                if(x==y||!z) break;
                if(!(i%127)||i==j){
                    g=__gcd(z,p);
                    if(g>1) return g;
                    if(i==j) y=x,j<<=1;
                }
            }
        }
    }
    void Pollard_Rho(vector<long long> &cnt,long long n){
        while(!(n&1)) cnt.push_back(2),n>>=1;
        if(n==1) return;
        if(Miller_Rabin(n)) return cnt.push_back(n),void(); 
        long long p=find_factor(n);
        Pollard_Rho(cnt,n/p),Pollard_Rho(cnt,p);
    }
}
void solve(){
    srand((unsigned)time(NULL));
    long long n; cin>>n;
    vector<long long> res;

    MR::Pollard_Rho(res,n);
    
    map<long long,int> cnt;
    for(auto v:res) cnt[v]++;
    for(auto v:cnt)
        if(v.second>1){
            cout<<"yes\n";
            return;
        }
    puts("no");
}
int main(){
    int T; cin>>T;
    while(T--) solve();
}