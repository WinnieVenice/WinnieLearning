#include<bits/stdc++.h>
//#define wwj
struct trie {
    void ins(std::string &s, int v) {
        int cur = rt;
        for (int i = s.size() - 1; i >= 0; i--) {
            int c = _ch(s[i]);
            if (!ch[c][cur]) ch[c][cur] = ++tot;
            cur = ch[c][cur];
        }
        val[cur] = v;
    }
    int find(std::string &s) {
        int cur = rt;
        for (int i = s.size() - 1; i >= 0; i--) {
            int c = _ch(s[i]);
            if (!ch[c][cur]) return 0;
            cur = ch[c][cur];
        }
        return cur;
    }
    int _ch(char c) { return c - 'a'; }
    trie(int _n, int _m): n(_n), m(_m) {
        ch.resize(m, std::vector<int>(n, 0));
        rt = tot = 0;
        val.resize(n);
    }
    int rt, n, m, tot;
    std::vector<std::vector<int>> ch;
    std::vector<int> val;
};
signed main() {
    //std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0);
    #ifdef wwj
        std::ifstream cin("E:\\workworkwork\\GitHub\\demo\\test.in");
        std::ofstream cout("E:\\workworkwork\\GitHub\\demo\\test.out");
    #endif
    int n; std::cin >> n;
    #ifdef wwj
        cin >> n;
    #endif
    std::vector<std::pair<std::string, int>> a(n);
    int sum_len = 0;
    for (auto &v: a) {
        std::cin >> v.first;
        #ifdef wwj
            cin >> v.first;
        #endif
        sum_len += (int)v.first.size();
    } 
    int mx_col = 0;
    for (auto &v: a) {
        std::cin >> v.second;
        #ifdef wwj
            cin >> v.second;
        #endif
        mx_col = std::max(mx_col, v.second);
    }
    trie tr(sum_len + 1, 26);
    for (auto &v: a) {
        tr.ins(v.first, v.second);
    }
    int tot = 0;
    std::vector<int> sz(tr.tot + 1 + 1);
    std::vector<int> idx(tr.tot + 1 + 1);
    std::function<int(int)> dfs = [&](int x) {
        idx[++tot] = x; sz[x] = 1;
        for (int i = 0; i < 26; i++) {
            if (!tr.ch[i][x]) continue;
            sz[x] += dfs(tr.ch[i][x]);
        }
        return sz[x];
    };
    dfs(tr.rt);
    std::vector<int> ans(tr.tot + 1 + 1, 0);
    int mx = 0;
    std::vector<int> mp(mx_col + 1, 0);
    auto add = [&](int x) {
        mx = std::max(mx, ++mp[tr.val[idx[x]]]);
    };
    auto del = [&](int x) {
        mp[tr.val[idx[x]]]--;
    };
    std::function<void(int, int)> sol = [&](int l, int r) {
        if (l == r) {
            ans[idx[l]] = 1;
            return;
        }
        int mid = l + r >> 1;
        sol(l, mid); sol(mid + 1, r);
        mx = 0;
        for (int i = mid, j, p = mid; l <= i && (j = i + sz[idx[i]] - 1) <= r; i--) {
            add(i);
            if (j <= mid) continue;
            for (; p < j; ) add(++p);
            ans[idx[i]] = std::max(ans[idx[i]], mx);
        }
        for (int i = mid, j, p = mid; l <= i && (j = i + sz[idx[i]] - 1) <= r; i--) {
            del(i);
            if (j <= mid) continue;
            for (; p < j; ) del(++p);
        }
    };
    sol(1, tot);
    for (auto &v: a) {
        std::cout << ans[tr.find(v.first)] << '\n';
        #ifdef wwj
            cout << ans[tr.find(v.first)] << '\n';
        #endif
    }
}