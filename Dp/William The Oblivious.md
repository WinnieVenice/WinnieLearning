# William The Oblivious

## 题目

给定只含"a","b","c"的字符串s，有q次操作，每次操作一个数p和字符c，表示将位置p的字符改为c。对每个操作，输出最少需要改变多少个字符，才能让数组中不存在子序列"abc"

## 做法

状态机dp+线段树

匹配"abc"序列的状态机图示：

![image-20211209221347507](https://raw.githubusercontent.com/WinnieVenice/PicBed/main/image-20211209221347507.png)

两种写法

### 写法1：用不可达状态进行转移

使用线段树维护使状态x不可达，最小需要修改多少个字符。为了进行区间合并，除了上面的状态外，还需要状态b、c、bc。每个节点维护以下几种状态a、b、c、ab、bc、abc，分别是使节点对应的区间对状态a,b,c,ab,bc,abc不可达最小的修改次数。

考虑状态转移：

​		要使得abc状态不可达：$\begin{cases}\ 左区间有a\begin{cases}\ 左区间有ab:左区间没有abc，且右区间没有c\\\ 左区间无ab:右区间没有bc\end{cases}\\\ 左区间无a:右区间没有abc \end{cases}$

即：
$$
\\ f_{cur}(abc)\leftarrow min\{f_l(abc)+f_r(c)\}
\\ f_{cur}(abc)\leftarrow min\{f_l(ab)+f_r(bc)\}
\\ f_{cur}(abc)\leftarrow min(f_l(a)+f_r(abc))
$$
​		要使得ab状态不可达：$\begin{cases}\ 左区间有a:左区间没有ab,且右区间没有b\\\ 左区间无a:右区间没有ab \end{cases}$

​		要使得bc状态不可达：$\begin{cases}\ 左区间有b:左区间没有bc,且右区间没有c\\\ 左区间无b:右区间无bc \end{cases}$

```c++
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LL __int128
using namespace std;
int qpow(int a, int b, int p) {int ret = 1; for(a %= p; b; b >>= 1, a = a * a % p) if(b & 1) ret = ret * a % p; return ret; }
int qpow(int a,int b) {int ret = 1; for(; b; b >>= 1, a *= a) if(b & 1) ret *= a; return ret; }
int gcd(int x,int y) {return y ? gcd(y, x % y) : x; }
pair<int,int> exgcd(int a,int b) { if(!b) return {1, 0}; pair<int,int> ret = exgcd(b, a % b); return {ret.second, ret.first - a / b * ret.second }; }
int lcm(int x,int y){ return x / gcd(x, y) * y; }
const int N = 5 + 1e5;
const int inf = 1e9;
int n, q;
int f[N << 2][6]; // a = 0, b = 1, c = 2, ab = 3, bc = 4, abc = 5
int ch[100];
void pb(int x) {
    for (int i = 0; i < 3; i++) {
        f[x][i] = f[x << 1][i] + f[x << 1| 1][i];
    }
    // ab = ab + b/ a + ab
    f[x][3] = min(f[x << 1][3] + f[x << 1| 1][1], f[x << 1][0] + f[x << 1| 1][3]);
    // bc = bc + c/ b + bc
    f[x][4] = min(f[x << 1][4] + f[x << 1| 1][2], f[x << 1][1] + f[x << 1| 1][4]);
    // abc = abc + a/ abc + c/ ab + bc
    f[x][5] = min({f[x << 1][0] + f[x << 1| 1][5], f[x << 1][5] + f[x << 1| 1][2], f[x << 1][3] + f[x << 1| 1][4]});
}
void upd(int x, int l, int r, int p, char c, int t) {
    if (l == r) {
        f[x][ch[c]] += t;
        return;
    }
    int mid = l + r >> 1;
    if (p <= mid) upd(x << 1, l, mid, p, c, t);
    else upd(x << 1| 1, mid + 1, r, p, c, t);
    pb(x);
}
signed main() {
    ch['a'] = 0; ch['b'] = 1; ch['c'] = 2;
    cin >> n >> q;
    string s; cin >> s; s = ' ' + s;   
    for (int i = 1; i <= n; i++) {
        upd(1, 1, n, i, s[i], 1);
    } 
    while (q--) {
        int p; char c; cin >> p >> c;
        upd(1, 1, n, p, s[p], -1);
        s[p] = c;
        upd(1, 1, n, p, s[p], 1);
        cout << f[1][5] << endl;
    }
}
```

#### 写法2：用最终到达状态为x的最少修改次数

要维护两个状态机的到达状态的最小修改代价，即除了上面那个状态机还有$0\rightarrow b\rightarrow bc$的状态机

![image-20211210032854802](https://raw.githubusercontent.com/WinnieVenice/PicBed/main/image-20211210032854802.png)

最小修改代价显然能够类似于floyd算法求:枚举起点状态i和最终到达状态j,再枚举中间转移的状态k来求得从i$\rightarrow$j的最小代价，即：$f_{cur}(i\rightarrow j)\leftarrow min\{f_l(i\rightarrow k)+f_r(k\rightarrow j)\}$

单点更新的时候初始化状态机:$f(i\rightarrow i)=0,f(i\rightarrow i_{next})=1$,f(其他)=inf

对当前修改的字符c来说,最小修改代价即:$f(c\rightarrow c)=1,f(c\rightarrow c+1)=0$

```C++
#include<bits/stdc++.h>
#define LL __int128
#define endl '\n'
#define int long long 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b,ll p){a%=p; ll ret=1;for(;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p; return ret;}
ll qpow(ll a,ll b){ll ret=1; for(;b;b>>=1,a*=a) if(b&1) ret*=a; return ret;}
ll getInv(ll x,ll p){return qpow(x,p-2,p);}
const int inf = 1e9;
const int N = 5 + 1e5;
int n, q;
string s; 
int f[N << 2][5][5];
void poll(int x) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            f[x][i][j] = inf;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = i; k <= j; k++) {
                f[x][i][j] = min(f[x][i][j], f[x << 1][i][k] + f[x << 1| 1][k][j]);
            }
        }
    }
}
void upd(int x, int l, int r, int p, int c) {
    if (l == r) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                f[x][i][j] = inf;
                if (i == j) f[x][i][j] = 0;
                if (i + 1 == j) f[x][i][j] = 1;
            }
        }
        f[x][c][c] = 1; 
        f[x][c][c + 1] = 0;
        return;
    }
    int mid = l + r >> 1;
    if (p <= mid) upd(x << 1, l, mid, p, c);
    else upd(x << 1| 1, mid + 1, r, p, c);
    poll(x);
}
signed main(){
    cin >> n >> q >> s; s = ' ' + s;
    for (int i = 1; i <= n; i++) upd(1, 1, n, i, s[i] - 'a');
    while (q--) {
        int p; char c; cin >> p >> c;
        upd(1, 1, n, p, c - 'a');
        cout << min({f[1][0][0], f[1][0][1], f[1][0][2]}) << endl;
    }
}
```

