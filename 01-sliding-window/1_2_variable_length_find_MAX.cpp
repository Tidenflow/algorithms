/**
 * @file VariableSlidingWindow_Longest.cpp
 * @brief 不定长滑动窗口模板：求满足条件的最长/最大区间
 * @logic 
 * 1. 入：右端点元素进入窗口，更新窗口状态
 * 2. 缩：while (窗口不合法) { 左端点元素出窗口，更新状态，left++ }
 * 3. 更新答案：此时窗口一定合法，计算 res = max(res, right - left + 1)
 */

#include <vector>
#include <algorithm>
#include <unordered_map>

namespace AlgoTemplate {

class VariableWindow {
public:
    /**
     * @brief 求最长子数组/子串通用框架
     * @param s 输入序列（数组或字符串）
     * @return 最大长度
     */
    template <typename T>
    static int solveLongest(const T& s) {
        int n = s.size();
        int left = 0;
        int ans = 0;
        // WindowState state; // 这里的状态可以是 sum, counter, hash_map 等

        for (int right = 0; right < n; ++right) {
            // 1. 【入】将 s[right] 加入窗口，更新状态
            // updateState(s[right]);

            // 2. 【缩】一旦当前窗口不满足题目要求的“合法性”
            // 灵神名言：只要不合法，就一直缩
            while (/* 窗口不合法条件 */ false) {
                // left 离开窗口，更新状态
                // shrinkState(s[left]);
                left++;
            }

            // 3. 【更新答案】此时 [left, right] 区间绝对合法
            // 这里的“越短越合法”体现为：经过 while 缩减后，剩下的区间是当前右端点下的最长合法区间
            ans = std::max(ans, right - left + 1);
        }

        return ans;
    }
};

} // namespace AlgoTemplate

// ---------------------------------------------------------
// 实战示例：LeetCode 3. 无重复字符的最长子串
// ---------------------------------------------------------
int lengthOfLongestSubstring(std::string s) {
    std::unordered_map<char, int> cnt;
    int left = 0, ans = 0;
    for (int right = 0; right < s.length(); ++right) {
        cnt[s[right]]++; // 入
        
        // 只要当前字符重复了（不合法），就移动左边界
        while (cnt[s[right]] > 1) { 
            cnt[s[left]]--; // 出
            left++;
        }
        
        // 此时窗口内无重复字符，更新最大长度
        ans = std::max(ans, right - left + 1);
    }
    return ans;
}




/*
🧠 深度总结：
(1)单调性：这种方法生效的前提是，如果一个区间 [L, R] 不合法，那么任何包含它的更大区间 [L-1, R] 也一定不合法。

(2)延迟更新：与定长窗口不同，不定长窗口的答案更新通常放在 while 循环之后。
因为 while 的作用是“修正”，只有修正完成后的窗口状态才是我们需要的。

(3)时间复杂度：虽然代码里有 for 嵌套 while，但因为 left 指针和 right 指针都只向右移动、不回退，
所以每个元素最多进出窗口一次，整体复杂度依然是稳健的 O(n)。

*/