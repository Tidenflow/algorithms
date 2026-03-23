/**
 * @file VariableSlidingWindow_Shortest.cpp
 * @brief 不定长滑动窗口模板：求满足条件的最短/最小区间
 * @logic
 * 入：右端点元素进入窗口，更新状态
 * 缩（核心）：while (窗口满足合法条件) {
 * a. 更新答案：因为要找“最短”，现在合法了，赶紧记下长度 res = min(res, right - left + 1)
 * b. 左端点元素出窗口，更新状态
 * c. left++，尝试看看更短的行不行
}
 一句话：为了找最短，首先足够长是合法的，越长越合法，这样左边才开始收缩，直到不合法停止  为了短就要试探合法的底线，合法循环收缩
 */

#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
#include <string>    
#include <algorithm> 
using namespace std;

namespace AlgoTemplate {

class VariableWindow {
public:
    /**
     * @brief 求最短子数组/子串通用框架
     * @param s 输入序列
     * @return 最小长度（若无解返回 0 或特定值）
     */
    template <typename T>
    static int solveShortest(const T& s) {
        int n = s.size();
        int left = 0;
        int ans = INT_MAX; // 求最小，初始设为无穷大
        // WindowState state; 

        for (int right = 0; right < n; ++right) {
            // 1. 【入】将 s[right] 加入窗口，更新状态
            // updateState(s[right]);

            // 2. 【缩】只要当前窗口“满足条件”（合法）
            // 灵神名言：只要合法，就一直缩，缩到不合法为止
            while (/* 窗口满足合法条件 */ true) {
                
                // 3. 【更新答案】此时窗口是合法的，记录当前长度
                // 重点：在 while 内部更新，因为我们要的是“满足条件的最短”
                ans = std::min(ans, right - left + 1);

                // 4. 【出】左端点离开窗口，尝试寻找更短的可能
                // shrinkState(s[left]);
                left++;
            }
        }

        return (ans == INT_MAX) ? 0 : ans;
    }
};

} // namespace AlgoTemplate

// ---------------------------------------------------------
// 实战示例：LeetCode 2875. 无限数组的最短子数组
// ---------------------------------------------------------
class Solution {
public:
    int balancedString(string s) {
        int cnt['X']{}; // 也可以用哈希表，不过数组更快一些
        for (char c : s) {
            cnt[c]++;
        }

        int n = s.size(), m = n / 4;
        if (cnt['Q'] == m && cnt['W'] == m && cnt['E'] == m && cnt['R'] == m) {
            return 0; // 已经符合要求啦
        }
        
        int ans = n, left = 0;
        for (int right = 0; right < n; right++) { // 枚举子串右端点
            cnt[s[right]]--; // 注意 cnt 统计的是在子串 [left,right] 外面的字母个数
            while (cnt['Q'] <= m && cnt['W'] <= m && cnt['E'] <= m && cnt['R'] <= m) {    // while内部就是合法条件
                // 子串 [left,right] 满足要求
                ans = min(ans, right - left + 1);
                cnt[s[left]]++; // 缩小子串，把 s[left] 放到外面
                left++;
            }
        }
        return ans;
    }
};

