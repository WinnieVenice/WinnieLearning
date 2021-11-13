# ax+by=c model exgcd

## 引入

$$
\\ 由贝祖定理有ax+by=gcd(a,b),当gcd(a,b)|k时有解,否则无解
\\ ax+by=gcd(a,b)
\\ 令a=b,b=a\%b,则有:bx+(a\%b)y=gcd(b,a\%b)=gcd(a,b)
\\ 由于a\%b=a-(a/b)b,则：
\\ bx+ay-(a/b)by=gcd(a,b)
\\ ay+b(x-(a/b)y)=gcd(a,b)
\\ 令x=y,y=x-(a/b)y.那么我们就从(b,a\%b)转移到(a,b)
\\ 边界:b=0时,gcd(a,0)=a,则:1*a+0*b=a
$$



## 通解

$$
\\ 根据引入我们找到一组(x,y)满足ax+by=gcd(a,b)
\\ 由于x,y\in Z^*, 则:y=\frac{gcd(a,b)-ax}{b}\in Z^*
\\ 假设存在另一组解x_0=x+i,则存在ax_0+by_0=gcd(a,b)
\\ 分离y_0得:y_0=\frac{gcd(a,b)-ax_0}{b}
\\ =\frac{gcd(a,b)-ax-ai}{b}
\\ =\frac{gcd(a,b)-ax}{b}+\frac{ai}{b}
\\ 由于y_0\in Z^*,则:\frac{ai}{b}\in Z^*,即:\frac{a}{b}i\in Z^*
\\ 若gcd(a,b)=1,则: i_{min}=b;
\\ 否则:\exist d=gcd(a,b)使得a=a'd,b=b'd,则:\frac{a'}{b'}i\in Z^*, 其中gcd(a',b')=1
\\ 故: x的通解为: x_i=x+ki,k\in Z,i=b'=\frac{b}{gcd(a,b)}
\\ x的最小正整数解: x_{min}=(x-\frac{x}{b'})b'=x\%b'
\\ 设k=b'=\frac{b}{gcd(a,b)},由于x可能为负,故x_{min}=(x\%k+k)\%k
$$

## Code

```C++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
 
#define INF 0x7fffffff
#define EPS 1e-12
#define MOD 1000000007
#define PI 3.141592653579798
#define N 100000
 
using namespace std;
 
typedef long long LL;
typedef double DB;
 
LL e_gcd(LL a,LL b,LL &x,LL &y)
{
    if(b==0)
    {
        x=1;
        y=0;
        return a;
    }
    LL ans=e_gcd(b,a%b,x,y);
    LL temp=x;
    x=y;
    y=temp-a/b*y;
    return ans;
}
 
LL cal(LL a,LL b,LL c)
{
    LL x,y;
    LL gcd=e_gcd(a,b,x,y);
    if(c%gcd!=0) return -1;
    x*=c/gcd;
    b/=gcd;
    if(b<0) b=-b;
    LL ans=x%b;
    if(ans<=0) ans+=b;
    return ans;
}
 
int main()
{
    LL x,y,m,n,L;
    while(scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&L)!=EOF)
    {
        LL ans=cal(m-n,L,y-x);
        if(ans==-1) printf("Impossible\n");
        else printf("%lld\n",ans);
    }
    return 0;
}
```

