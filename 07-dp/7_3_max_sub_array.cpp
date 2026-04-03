/**
 * @file MaxSubArrayDP.cpp        当前元素是“另起炉灶”还是“接续前缘”
 * @brief 最大子数组和 (Kadane 算法) 模板
 * @reference 灵茶山艾府 (https://github.com/endlesscheng)
 * 核心逻辑：
 * 1. 状态定义：dp[i] 表示以第 i 个元素结尾的最大子数组和
 * 2. 状态转移：dp[i] = max(dp[i-1] + nums[i], nums[i])
 * - 简化为：dp[i] = max(dp[i-1], 0) + nums[i] (若前一个状态小于0，则舍弃，只取当前值)
 * 3. 最终答案：max(dp[0...n-1])
 */
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

namespace AlgoTemplate {

class MaxSubArray {
public:
    /**
     * @brief 动态规划实现 (Kadane 算法)
     * 时间复杂度: O(n), 空间复杂度: O(n) (可空间优化至 O(1))
     */
    static int solve(const vector<int>& nums) {
        if (nums.empty()) return 0;
        int n = nums.size();
        int i;
        // 1. 【初始化】
        // dp[i] 表示以 nums[i] 结尾的最大连续子数组和
        vector<int> dp(n);
        dp[0] = nums[i];
        int ans = dp[0];

        // 2. 【状态转移】
        for (int i = 1; i < n; ++i) {
            // 如果 dp[i-1] 是负数，加上它只会更小，所以取 0
            dp[i] = max(dp[i - 1], 0) + nums[i];
            // 更新全局最大值
            ans = max(ans, dp[i]);
        }

        return ans;
    }

    /**
     * @brief 空间优化版的 Kadane (面试常用)
     */
    static int solveOptimized(const vector<int>& nums) {
        int ans = INT_MIN;
        int f = 0; // 记录前一个 dp 状态
        for (int x : nums) {
            f = max(f, 0) + x;
            ans = max(ans, f);
        }
        return ans;
    }
};

} // namespace AlgoTemplate


// 53. 最大子数组和
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> f(nums.size());
        f[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            f[i] = max(f[i - 1], 0) + nums[i];   // 最重要的状态转移方程
        }
        return *max_element(f.begin(), f.end());
    }
};

