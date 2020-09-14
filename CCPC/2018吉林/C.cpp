#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod=7+1e9;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b,ll p){a%=p; ll ret=1;for(;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p; return ret;}
ll getInv(ll x,ll p){return qpow(x,p-2,p);}
const int N=5+1e5;
ll a[N];
int main(){
    int T; cin>>T;
    for(int o=1;o<=T;o++){
        map<ll,int> k;
        map<ll,int> ans1;
        int n; cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            k[a[i]]++;
        }
        ll tot=n;
        bool ok1=0,ok2=0;
        ll cnt1=1;
        for(int i=1;i<N;i++){
            if(tot<cnt1||tot<=0) break;
            if(k[i]>=cnt1){
                ok1=1;
                k[i]-=cnt1;
                ans1[i]+=cnt1;
                tot-=cnt1;
                break;
            }else{
                cnt1-=k[i];
                cnt1*=2;
                ans1[i]+=k[i];
                k[i]=0;
                tot-=k[i];
            }
        }
        ll cnt2=1;
        for(int i=1;i<N;i++){
            if(tot<cnt2||tot<=0) break;
            if(k[i]>=cnt2){
                ok2=1;
                k[i]-=cnt2;
                tot-=cnt2;
                break;
            }else{
                cnt2-=k[i];
                cnt2*=2;
                k[i]=0;
                tot-=k[i];
            }
        }
        cout<<"Case "<<o<<": ";
        if(!ok1||!ok2) cout<<"NO\n";
        else{
            cout<<"YES\n";
            for(int i=1;i<=n;i++){
                if(ans1[a[i]]){
                    ans1[a[i]]--;
                    cout<<"1";
                }else cout<<"0";   
            }
            cout<<'\n';
        }
    }
}