/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个正序数组的中位数
 */

// @lc code=start
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<double> a;
        int n = nums1.size(), m = nums2.size();
        int i = 0, j = 0;
        for (; i < n && j < m; ) {
            if (nums1[i] <= nums2[j]) {
                a.push_back(nums1[i]);
                i++;
            } else {
                a.push_back(nums2[j]);
                j++;
            }
        }
        for (; i < n; i++) a.push_back(nums1[i]);
        for (; j < m; j++) a.push_back(nums2[j]);
        int sz = a.size();
        if (sz & 1) return a[max(0, (sz + 1) / 2 - 1)];
        else return (a[max(0, (sz + 1) / 2 - 1)] + a[(sz + 1) / 2]) / 2.0;
    }
};
// @lc code=end

