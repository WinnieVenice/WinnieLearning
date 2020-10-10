#include<bits/stdc++.h>
#define LL __int128
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod=7+1e9;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b,ll p){a%=p; ll ret=1;for(;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p; return ret;}
ll qpow(ll a,ll b){ll ret=1;for(;b;b>>=1,a=a*a) if(b&1) ret=ret*a; return ret;}
ll getInv(ll x,ll p){return qpow(x,p-2,p);}
class BigInt{
    public:
        string v;
        int len;
        bool Sign;
        inline BigInt(){v.clear(); len=0; Sign=0;}
        inline BigInt(string s){
            v.clear();
            Sign=0;
            if(*s.begin()=='-') Sign=1,s.erase(s.begin());
            while(*s.begin()=='0'&&s.length()>1) s.erase(s.begin());
            reverse(s.begin(),s.end());
            v=s;
            len=(int)v.length();
        }
        inline BigInt(string s,bool sign){
            v.clear();
            Sign=sign;
            if(*s.begin()=='-') Sign=1,s.erase(s.begin());
            while(*s.begin()=='0'&&s.length()>1) s.erase(s.begin());
            reverse(s.begin(),s.end());
            v=s;
            len=(int)v.length();
        }
        inline BigInt(long long x){
            v.clear();
            Sign=0;
            if(x<0) Sign=1,x=-x; 
            for(;x;x/=10) v+=x%10+'0';
            len=(int)v.length();
        }
        inline BigInt(const BigInt &x){
            v=x.v;
            len=x.len;
            Sign=x.Sign;
        }
        inline BigInt(const BigInt &x,bool sign){
            v=x.v;
            len=x.len;
            Sign=x.Sign^sign;
        }
        inline void init(long long x){
            v.clear();
            Sign=0;
            if(x<0) Sign=1,x=-x;
            for(;x;x/=10) v+=x%10+'0';
            len=(int)v.length();
        }
        inline const BigInt operator-()const{ return BigInt(v,!Sign);}
        inline void operator=(const BigInt &x){
            v=x.v;
            len=x.len;
            Sign=x.Sign;
        }
        inline void operator=(const long long &x){ init(x);}
        inline bool operator>(const BigInt &x)const {
            if(x.Sign!=Sign) return Sign>x.Sign;
            if(Sign<0) return (*this<x);
            if(x.len!=len) return len>x.len;
            for(int i=len-1;i>=0;i--)
                if(x.v[i]!=v[i]) return v[i]>x.v[i];
            return 0;
        }
        inline bool operator<(const BigInt &x)const {
            if(x.Sign!=Sign) return Sign<x.Sign;
            if(Sign<0) return (*this>x);
            if(x.len!=len) return len>x.len;
            for(int i=len-1;i>=0;i--)
                if(x.v[i]!=v[i]) return v[i]<x.v[i];
            return 0;
        }
        inline bool operator==(const BigInt &x)const {
            if(x.Sign!=Sign) return 0;
            if(x.len!=len) return 0;
            for(int i=0;i<len;i++)
                if(x.v[i]!=v[i]) return 0;
            return 1;
        }
        friend BigInt max(const BigInt &x,const BigInt &y){
            if(x>y) return x;
            else return y;   
        }
        friend BigInt min(const BigInt &x,BigInt &y){
            if(x<y) return x;
            else return y;
        }
        friend BigInt operator+(const BigInt &x,const BigInt &y){
            if(x.Sign!=y.Sign) return BigInt(x-(-y),x.Sign);
            string s;
            int len=std::min(x.len,y.len);
            int j=0;
            for(int i=0;i<len;i++){
                int cur=x.v[i]+y.v[i]-2*'0';
                s+=(cur+j)%10+'0';
                j=(cur+j)/10;
            }
            BigInt mx(max(x,y));
            for(int i=len;i<mx.len;i++){
                s+=(mx.v[i]-'0'+j)%10+'0';
                j=(mx.v[i]-'0'+j)/10;
            }
            for(;j;j/=10) s+=j%10+'0';
            reverse(s.begin(),s.end());
            return BigInt(s,x.Sign);
        }
        friend BigInt operator-(const BigInt &x,const BigInt &y){
            if(x.Sign!=y.Sign) return BigInt(x+(-y),x.Sign);
            //if(x<y) return BigInt((-y)-x,!y.Sign);
            if(x<0&&y<0) return BigInt(x-y,1);
            int len=std::min(x.len,y.len);
            string s;
            int j=0;
            for(int i=0;i<len;i++){
                if(x.v[i]-j>=y.v[i]) s+=x.v[i]-j-y.v[i]+'0',j=0;
                else s+=10+x.v[i]-j-y.v[i]+'0',j=1;
            }
            BigInt mx(max(x,y));
            for(int i=len;i<mx.len;i++){
                s+=(mx.v[i]-'0'-j)%10+'0';
                j=(mx.v[i]-'0'+j)/10;
            }
            reverse(s.begin(),s.end());
            return BigInt(s);
        }
        friend BigInt operator*(const BigInt &x,const BigInt &y){
            int len=2*std::max(x.len,y.len);
            string s(len,(char)0);             
            for(int i=0;i<x.len;i++) 
                for(int j=0;j<y.len;j++)
                    s[i+j]+=(char)0+(x.v[i]-'0')*(y.v[j]-'0'); 
            for(int i=0;i<len;i++){
                if(s[i]>=10){
                    s[i+1]+=s[i]/10;
                    s[i]=s[i]%10;
                }
                s[i]+='0';
            }
            reverse(s.begin(),s.end()); 
            return BigInt(s,x.Sign^y.Sign);
        }
        friend BigInt operator%(const BigInt &x,const long long &p){
            long long res=0;
            for(int i=0;i<x.len;i++) res=(res*10+x.v[i]-'0')%p;
            return BigInt(res);
        }
        friend BigInt qpow(BigInt a,long long b){
            BigInt res(1);
            for(;b;b>>=1,a=a*a)
                if(b&1) res=res*a;
            return res;
        }
        friend void print(const BigInt &x){ if(x.Sign) cout<<'-'; for(int i=x.len-1;i>=0;i--) cout<<x.v[i];}
        friend ostream &operator<<(ostream &cout,const BigInt &x){ print(x); return cout;}
        friend istream &operator>>(istream &cin,BigInt &x){
            string s; cin>>s;
            x=BigInt(s);
            return cin;
        }
};
void solve(){
    BigInt a,b; cin>>a>>b;
    cout<<a+b<<'\n';
    cout<<a-b<<'\n';
    cout<<-a<<'\n';
    cout<<-b<<'\n';
}
int main(){
    int T; cin>>T;
    while(T--) solve();
}