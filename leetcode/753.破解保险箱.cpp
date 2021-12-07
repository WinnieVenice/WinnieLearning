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
    void dfs(int x, string u, int n, int k) {
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
    void dfs1(int x) {
        for (; !G[x].empty(); ) {
            auto u = G[x].back(); G[x].pop_back();
            dfs1(u);
        }
        pt[++cnt] = x;
    }
    string crackSafe(int n, int k) {
        if (n == 1) {
            string ans = "";
            for (int i = 0; i < k; i++) ans += char(i + '0');
            return ans;
        }
        dfs(0, "", n - 1, k);
        for (auto &u : mp) {
            string v = u.first.substr(1, u.first.size() - 1);
            for (int i = 0; i < k; i++) {
                G[u.second].push_back(mp[v + char(i + '0')]);
            }
        }
        dfs1(1);
        string ans = id[pt[cnt]];
        for (int i = cnt - 1; i >= 1; i--) {
            ans += id[pt[i]][n - 2];
        }
        return ans;
    }
};
// @lc code=end