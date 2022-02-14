//@lc app=leetcode.cn id=25 lang=cpp
// @lc code=start
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) return head;
        ListNode *fh = new ListNode(0, head);
        ListNode *st = fh;
        int cnt = 0;
        for (; head; ) {
            if (cnt < k - 1) {
                cnt++;
                head = head->next;
            } else {
                cnt = 0;
                ListNode *ft = head->next;
                ListNode *fhh = fh->next;
                ListNode *p = fh->next;
                ListNode *pre = fh;
                for (; p && p != ft; ) {
                    ListNode *tmp = p->next;
                    p->next = pre;
                    pre = p;
                    p = tmp;
                }
                fhh->next = ft;
                fh->next = pre;
                fh = fhh;
                head = ft;
                
            }
        }
        return st->next;
    }
};
// @lc code=end

