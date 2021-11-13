# model get_euler

```C++
//getEuler
#include<bits/stdc++.h>
using namespace std;
struct Euler{
    int n;
    ll ret;
    Euler(int x): n(x),ret(n){solve();}
    inline void solve(){
        int cur=n;
        for(int i=2;i*i<=cur;i++){
            if(cur%i==0){
                (ret/=i)*=i-1;
                while(cur%i==0)
                    cur/=i;
            }
        }
        if(cur>1)
            (ret/=cur)*=cur-1;
    }
};
int main(){
    int n; scanf("%d",&n);
    Euler el(n);
    printf("%lld\n",el.ret);
}
```

