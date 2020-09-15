#define ll long long
is isPrime(ll n){
    if(n==2||n==3||n==5)
        return true;
    if(n%2==0||n%3==0||n%5==0||n==1)
        return false;
    ll c=7,a[8]={4,2,4,2,4,6,2,6};
    while(c*c<=n)
        for(auto i:a){
            if(n%c==0)
                return false;
            c+=i;
        }
    return true;
}