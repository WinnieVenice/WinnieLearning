/*
 * @lc app=leetcode.cn id=753 lang=cpp
 *
 * [753] 破解保险箱
 */

// @lc code=start
class Solution {
public:
    int tot;
    map<string, int> mp;
    map<int, string> id;
    vector<int> G[100005];
    int _cnt1 = 0;
    void dfs(int x, string u, int n, int k) {
        if (++_cnt1>30000) return;
        if (x >= n) {
            if (!mp[u]) {
                mp[u] = ++tot;
                id[tot] = u;
            }
            return;
        }
        for (int i = 0; i < k; i++) {
            dfs(x + 1, u + char(i + '0'), n, k);
        }
    }
    int cnt;
    int pt[100005];
    int _cnt = 0;
    void dfs1(int x) {
        if (_cnt++ > 10000) return;
        for (; !G[x].empty(); ) {
            auto u = G[x].back(); G[x].pop_back();
            dfs1(u);
        }
        pt[++cnt] = x;
    }
    string crackSafe(int n, int k) {
        dfs(0, "", n, k);
        for (auto &u : mp) {
            string v = u.first.substr(1, u.first.size() - 1);
            for (char ch = '0'; ch <= '9'; ch++) {
                v += ch;
                G[u.second].push_back(mp[v]);
            }    
        }
        puts("~");
        dfs1(1);
        string ans = id[pt[cnt]];
        for (int i = cnt - 1; i >= 1; i--) {
            ans += id[pt[cnt]][n - 1];
        }
        return ans;
    }
};
// @lc code=end

