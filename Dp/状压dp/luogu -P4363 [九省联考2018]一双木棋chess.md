# luogu -P4363 [九省联考2018]一双木棋chess

## 题意

$$
\\\begin{align}
\\&菲菲和牛牛在一块 n 行 m 列的棋盘上下棋，菲菲执黑棋先手，牛牛执白棋后手。
\\&棋局开始时，棋盘上没有任何棋子，两人轮流在格子上落子，直到填满棋盘时结束。
\\&落子的规则是：一个格子可以落子当且仅当这个格子内没有棋子且这个格子的左侧及上方的所有格子内都有棋子。
\\&棋盘的每个格子上，都写有两个非负整数，从上到下第 i 行中从左到右第 j 列的格子上的两个整数记作 a_{i,j}和 b_{i,j}。
\\&在游戏结束后，菲菲和牛牛会分别计算自己的得分：菲菲的得分是所有有黑棋的格子上的 a_{i,j}之和，牛牛的得分是所有有白棋的格子上的 b_{i,j}的和。
\\&菲菲和牛牛都希望，自己的得分减去对方的得分得到的结果最大。
\\&现在他们想知道，在给定的棋盘上，如果双方都采用最优策略且知道对方会采用最优策略，那么，最终的结果如何？
\\\end{align}
$$

## 分析

$$
\\\begin{align}
\\&一方要max,一方要min，显然是对抗博弈
\\&所以dp转移上:
\\&先手A应该是now_state_A=max(next_state_B+a_{i,j})
\\&后手B应该是now_state_B=min(next_state_A-b_{i,j})
\\&其正确性显然:考虑所有状态都+b_{i,j},最后再减去\sum B
\\&暴力搜索O(3^{10})肯定会爆,考虑剪枝。
\\&因为是对抗博弈,所以常用剪枝方法有:记忆化搜索和\alpha-\beta剪枝(最优剪枝)
\\&先考虑记忆化搜索:
\\&考虑如何记录局面的状态,显然要状压.
\\&根据题目落子限制我们不难知道,对于每个最终局面,是个倒的直角三角形
\\&那么显然可以选择通过hash的方法来记录局面:
\\&我们记录每一行的长度,然后hash一下成(m+1)进制数作为状态即可,状态转移显而易见
\\&或者因为是倒着的三角形,所以我们可以考虑用轮廓线进行状压(插头dp)
\\&即:对于竖着的每一段我们用二进制里的1表示,横着的每一段用0表示,那么每个局面就是一个n+m位的二进制数.那么初始状态就是(1<<n)-1\Big(\begin{matrix}\underbrace{0\dots0}\\m\end{matrix}\begin{matrix}\underbrace{1\dots1}\\n\end{matrix}\Big),最终状态就是(1<<m)-1)<<n\Big(\begin{matrix}\underbrace{1\dots1}\\m\end{matrix}\begin{matrix}\underbrace{0\dots0}\\n\end{matrix}\Big)
\\&想一下如何进行状态转移,不难从第一步落子归纳出,每落一个子,在二进制上就是01\rightarrow10,那么就可以:next\_state=now\_state\oplus(3<<i),这里我们枚举i
\\&考虑\alpha-\beta剪枝(最优剪枝)怎么做
\\&有一个显然的思想就是在搜索的时候,如果当前阶段我们能判断出继续往下搜索的答案不可能超过当前得到的答案,那我们就没必要继续往下搜了
\\&具体来说:先往下搜,搜到一个当前最优答案\alpha，然后回溯到某个节点后继续往下搜的时候。
\\&假如当前节点是选max,那么其孩子节点就是选min
\\&假如下面搜到一个答案是\beta,且此时\alpha\geq\beta,那么不难知道,该分支的其他答案没有贡献,不需要往下搜了
\\\end{align}
$$

## 代码

### 记忆化：哈希

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 15;
int n, m;
int a[N][N], b[N][N];
map<pair<int,int>,int> mp;
int Hash(int *w) {
    int s = 0;
    for (int i = 0; i < n; i++){
        s = s * 15 + w[i];
    }
    return s;
}
int dfs(int *w, int z) {
    int s = Hash(w);
    if (mp[{s, z}]) return mp[{s, z}];
    mp[{s, z}] = (z ? 1 : -1) * INT_MAX;
    bool ok = 0;
    for (int i = 0; i < n; i++) {
        if ((!i || w[i] < w[i - 1]) && w[i] < m) {
            ok = 1;
            auto &x = mp[{s, z}];
            w[i]++;
            if (z) {    
                x = min(x, - b[i][w[i] - 1] + dfs(w, !z));
            } else {
                x = max(x, + a[i][w[i] - 1] + dfs(w, !z));
            }
            w[i]--;
        }
    }
    if (!ok) mp[{s, z}] = 0;
    return mp[{s, z}];
}
int w[N];
signed main() {
    cin >> n >> m;
    for (int i = 0; i < n + n; i++) {
        for (int j = 0; j < m && i < n; j++) {
            cin >> a[i][j];
        }
        for (int j = 0; j < m && i >= n; j++) {
            cin >> b[i - n][j];
        }
    }
    cout << dfs(w, 0) << endl;
}
```

### 记忆化：轮廓线

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 15;
int n, m;
int a[N][N], b[N][N];
map<pair<int,int>,int> mp;

int dfs(int x, int y) {
    if (mp[{x, y}]) return mp[{x, y}];
    mp[{x, y}] = (y ? 1 : -1) * INT_MAX;
    int u = n - 1 + 1, v = 0;
    bool ok = 0;
    for (int i = 0; i < n + m - 1; i++) {
        if ((x >> i) & 1) u--;
        else v++;
        if (((x >> i) & 3) == 1) {
            ok = 1;
            auto &f = mp[{x, y}];
            if (y) {
                f = min(f, - b[u][v] + dfs(x ^ (3 << i), !y));
            } else {
                f = max(f, + a[u][v] + dfs(x ^ (3 << i), !y));
            } 
        }
    }
    if (!ok) mp[{x, y}] = 0;
    return mp[{x, y}];
}
signed main() {
    cin >> n >> m;
    for (int i = 0; i < n + n; i++) {
        for(int j = 0; j < m && i < n; j++) cin >> a[i][j];
        for(int j = 0; j < m && i >= n; j++) cin >> b[i - n][j];
    }
    cout << dfs((1 << n) - 1, 0) << endl;
}
```

### $\alpha-\beta$

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 15;
int n, m;
int a[N][N], b[N][N];
int dfs(int *w, int alpha, int beta, int v, int z) {
    bool ok = 0;
    for (int i = 0; i < n; i++) {
        if ((!i || w[i] < w[i - 1]) && w[i] < m) {
            ok = 1;
            w[i]++;
            int res = dfs(w, alpha, beta, v + (z ? -b[i][w[i] - 1] : a[i][w[i] - 1]), !z);
            if (z) {
                beta = min(beta, res);
            } else {
                alpha = max(alpha, res);
            }
            w[i]--;
            if (alpha >= beta) break;
        }
    }
    if (!ok) return v;
    return z ? beta : alpha;
}
int w[N];
signed main() {
    cin >> n >> m;
    for (int i = 0; i < n + n; i++) {
        for (int j = 0; j < m && i < n; j++) {
            cin >> a[i][j];
        }
        for (int j = 0; j < m && i >= n; j++) {
            cin >> b[i - n][j];
        }
    }
    cout << dfs(w, -INT_MAX, INT_MAX, 0, 0) << endl;
}
```

### 记忆化 +$\alpha-\beta$

#### 注意：两者结合后的一些判断条件不一样

```C++
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 15;
int n, m;
int a[N][N], b[N][N];
map<pair<int,int>,pair<int,int>> mp;
int Hash(int *w) {
    int s = 0;
    for (int i = 0; i < n; i++){
        s = s * 15 + w[i];
    }
    return s;
}
pair<int, int> dfs(int *w, int alpha, int beta, int v, int z) {
    int s = Hash(w);
    auto &f = mp[{s, z}];
    if (f.second) return f;
    f.second = z ? INT_MAX : -INT_MAX;
    bool ok = 0;
    for (int i = 0; i < n; i++) {
        if ((!i || w[i] < w[i - 1]) && w[i] < m) {
            ok = 1;
            w[i]++;
            auto res = dfs(w, alpha, beta, v + (z ? -b[i][w[i] - 1] : a[i][w[i] - 1]), !z);
            if (z) {
                beta = min(beta, res.first);
                f.second = min(f.second, - b[i][w[i] - 1] + res.second);
            } else {
                alpha = max(alpha, res.first);
                f.second = max(f.second, + a[i][w[i] - 1] + res.second);
            }
            w[i]--;
            if (alpha > beta) break; //******************************不一样了
        }
    }
    f.first = z ? beta : alpha;
    if (!ok) return f = make_pair(v, 0);
    return f;
}
int w[N];
signed main() {
    cin >> n >> m;
    for (int i = 0; i < n + n; i++) {
        for (int j = 0; j < m && i < n; j++) {
            cin >> a[i][j];
        }
        for (int j = 0; j < m && i >= n; j++) {
            cin >> b[i - n][j];
        }
    }
    cout << dfs(w, -INT_MAX, INT_MAX, 0, 0).second << endl;
}
```

