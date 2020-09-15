/*
gcd(a,b)==gcd(b,a)
gcd(a,b)==gcd(a-b,b) (a>=b)
gcd(a,b)==gcd(a%b,b)
gcd(a,b,c)==gcd(gcd(a,b),c)
gcd(k*a,k*b)=k*gcd(a,b)
*/
#define ll long long
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}