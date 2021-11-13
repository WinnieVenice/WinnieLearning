# model_getMiu

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Miu{
    int n;
    ll ret;
    Miu(int x):n(x),ret(0){solve();}
    inline void solve(){
        if(n==1) return ret=1,void();
        int x=n;
        int count=0;
        for(int i=2;i*i<=x;i++){
            int cnt=0;
            while(x%i==0){
                cnt++;
                x/=i;
            }
            if(cnt>1) return;
            count+=cnt;
        }
        if(x>1) count++;
        if(count&1) ret=-1;
        else ret=1;
    }
};
int main(){
    int n; scanf("%d",&n);
    Miu miu(n);
    printf("%lld\n",miu.ret);
}
```

