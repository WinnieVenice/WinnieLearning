#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

const int N = 3;
int st, ed;
void input(int &x) {
    x = 0;
    vector<int> rd;
    for (int i = 0; i < N * N; i++) rd.push_back(i);
    shuffle(rd.begin(), rd.end(), default_random_engine(rand()));
    for (int i = 0, j = 0; i < N * N; i++) {
        /*
        int v; cin >> v;    // 手动输入
        x = x * 10 + v;
        */
        int v = rd[i];   //随机生成
        x = x * 10 + v;
        cout << v << " ";
        if (++j == 3) {
            j = 0;
            cout << endl;
        }
    }
}
/*
1 2 3
4 5 6
7 8 0

1 2 3
4 5 6
7 0 8
*/
/*
0 2 3
4 5 6
7 8 9

2 3 6
4 5 9
7 8 0
*/
int fac10[20];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
map<int, bool> vis;
map<int, int> fa;
bool check_edge(int x) {
    return x < 0 || x >= N;
}
int swap(int u, int p, int cp) {
    int v = u;
    int w = u / fac10[cp] % 10;
    v -= w * fac10[cp];
    v += w * fac10[p];
    return v;
}
void print_way() {
    vector<int> trace;
    for (int x = ed; x != st; x = fa[x]) {
        trace.push_back(x);
    }
    trace.push_back(st);
    for (int i = trace.size() - 1; i >= 0; i--) {
        string s = "";
        for (int j = 0, x = trace[i]; j < N * N; j++, x /= 10) {
            s += x % 10 + '0';
        }
        reverse(s.begin(), s.end());
        cout << "->" << endl;
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                cout << s[j * N + k] << " ";
            }
            cout << endl;
        }
    }
}
void bfs() {
    vis.clear();
    fa.clear();
    queue<int> q;
    q.push(st);
    while (q.size()) {
        int u = q.front(); q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        if (u == ed) {
            cout << "find the solution" << endl;
            print_way();
            return;
        }
        int p = 0;
        for (int i = u; i % 10; i /= 10) p++;
        int x = p % N, y = p / N;
        for (int i = 0; i < 4; i++) {
            int cx = x + dx[i], cy = y + dy[i];
            if (check_edge(cx) || check_edge(cy)) continue;
            int cp = cy * N + cx;
            int cu = swap(u, p, cp);
            if (vis[cu]) continue;
            fa[cu] = u;
            q.push(cu);
        }
    }
    cout << "no solution" << endl;
}
int step = 1e3, cur_step = 0;   //限定1e3步,超过这个步数判定无解
bool dfs(int u) {
    if (++cur_step >= step) return 0;
    if (vis[u]) return 0;   //记忆化处理
    vis[u] = 1;
    if (u == ed) {
        return 1;
    }
    int p = 0;
    for (int i = u; i % 10; i /= 10) p++;
    int x = p % N, y = p / N;
    for (int i = 0; i < 4; i++) {
        int cx = x + dx[i], cy = y + dy[i];
        if (check_edge(cx) || check_edge(cy)) continue;
        int cp = cy * N + cx;
        int cu = swap(u, p, cp);
        if (vis[cu]) continue;
        fa[cu] = u;
        bool f = dfs(cu);
        if (f) return 1;
    }
    return 0;
}
void dfs() {
    vis.clear();
    fa.clear();
    cur_step = 0;
    if (dfs(st)) {
        cout << "find the solution" << endl;
        print_way();
    } else {
        cout << "no solution" << endl;
    }
}
void Astar() {
    vis.clear();
    fa.clear();
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int,int,int>>> q;
    map<int, int> mp;
    for (int i = 0, x = ed; i < N * N; x /= 10, i++) {
        mp[x % 10] = i;
    }
    int _h = 0;
    for (int i = 0, x = st; i < N * N; x /= 10, i++) {  //预处理每个点的估值函数值,即：每个点到它目标点坐标的x,y差值之和
        _h += abs(mp[x % 10] % N - i % N) + abs(mp[x % 10] / N - i / N);
    }
    q.push({_h, _h, st});
    while (q.size()) {
        auto [tot, h, u] = q.top(); q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        if (u == ed) {
            cout << "find the solution" << endl;
            print_way();
            return;
        }
        int g = tot - h;
        int p = 0;
        for (int i = u; i % 10; i /= 10) p++;
        int x = p % N, y = p / N;
        for (int i = 0; i < 4; i++) {
            int cx = x + dx[i], cy = y + dy[i];
            if (check_edge(cx) || check_edge(cy)) continue;
            int cp = cy * N + cx;
            int cu = swap(u, p, cp);
            int hu = u / fac10[cp] % 10, hv = u / fac10[p] % 10;
            int ch = abs(mp[hu] % N - x) + abs(mp[hu] / N - y) + abs(mp[hv] % N - cx) + abs(mp[hv] - cy);
            ch -= abs(mp[hu] % N - cx) + abs(mp[hu] / N - cy) + abs(mp[hv] % N - x) + abs(mp[hv] - y);
            if (vis[cu]) continue;
            fa[cu] = u;
            q.push({g + 1 + h + ch, h + ch, cu});
        }
    }
    cout << "no solution" << endl;
}
signed main() {
    srand((unsigned)time(NULL));
    fac10[0] = 1;
    for (int i = 1; i < 19; i++) {
        fac10[i] = fac10[i - 1] * 10;
    }
    printf("init\n");
    input(st);
    int tmp_st = st;
    printf("target\n");
    input(ed);
    printf("BFS:\n");
    bfs();
    printf("DFS:\n");
    st = tmp_st;
    dfs();
    printf("ASTAR:\n");
    st = tmp_st;
    Astar();
}
