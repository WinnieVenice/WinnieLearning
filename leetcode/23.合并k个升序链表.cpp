/*
 * @lc app=leetcode.cn id=23 lang=cpp
 *
 * [23] 合并K个升序链表
 *
 * https://leetcode-cn.com/problems/merge-k-sorted-lists/description/
 *
 * algorithms
 * Hard (56.32%)
 * Likes:    1707
 * Dislikes: 0
 * Total Accepted:    377.8K
 * Total Submissions: 670.8K
 * Testcase Example:  '[[1,4,5],[1,3,4],[2,6]]'
 *
 * 给你一个链表数组，每个链表都已经按升序排列。
 * 
 * 请你将所有链表合并到一个升序链表中，返回合并后的链表。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：lists = [[1,4,5],[1,3,4],[2,6]]
 * 输出：[1,1,2,3,4,4,5,6]
 * 解释：链表数组如下：
 * [
 * ⁠ 1->4->5,
 * ⁠ 1->3->4,
 * ⁠ 2->6
 * ]
 * 将它们合并到一个有序链表中得到。
 * 1->1->2->3->4->4->5->6
 * 
 * 
 * 示例 2：
 * 
 * 输入：lists = []
 * 输出：[]
 * 
 * 
 * 示例 3：
 * 
 * 输入：lists = [[]]
 * 输出：[]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * k == lists.length
 * 0 <= k <= 10^4
 * 0 <= lists[i].length <= 500
 * -10^4 <= lists[i][j] <= 10^4
 * lists[i] 按 升序 排列
 * lists[i].length 的总和不超过 10^4
 * 
 * 
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        function<void(ListNode*&, int)> add = [&](ListNode *&p, int val) {
            if (!p) {
                p = new ListNode(val);
                return;
            }
            ListNode *t = p;
            for (; t->next; t = t->next);
            t->next = new ListNode(val);
        };
        int n = lists.size();
        vector<ListNode*> p = lists;
        ListNode *hd = nullptr;
        vector<int> a;
        for (; 1; ) {
            bool f = 0;
            for (int i = 0; i < n; i++) {
                if (p[i]) f = 1;
            }
            if (!f) break;
            int mi = 1e9;
            for (int i = 0; i < n; i++) {
                if (!p[i]) continue;
                mi = min(mi, p[i]->val);
            }
            for (int i = 0; i < n; i++) {
                if (!p[i]) continue;
                if (mi == p[i]->val) {
                    add(hd, mi);
                    p[i] = p[i]->next;
                    break;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (!p[i]) continue;
            for ( ; p[i]; p[i] = p[i]->next) {
                add(hd, p[i]->val);
            } 
        }
        return hd;
    }
};
// @lc code=end

