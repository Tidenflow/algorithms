/**
 * @file ClimbingStairsSeries.cpp
 * @brief 爬楼梯类 (线性 DP / 排列方案数) 算法模板
 * @reference 灵茶山艾府 (https://github.com/endlesscheng)
 * * 核心逻辑：
 * 1. 定义状态：f[i] 表示到达第 i 级台阶的方案数（或最小代价）。
 * 2. 状态转移：f[i] = ∑ f[i - step] ，其中 step 是所有合法的步长。
 * 3. 边界条件：f[0] = 1 (方案数) 或 f[0] = 0 (代价)。
 * * 一句话：当前状态是过去若干步状态的“合力”。
 */


 #include <vector>

namespace AlgoTemplate {

class ClimbingStairs {
public:
    /**
     * @brief 爬楼梯通用框架 (以方案数为例)
     * @param target 目标阶数 (n)
     * @param steps 可选的步长集合 (如 {1, 2})
     */
    static int solve(int target, const std::vector<int>& steps) {
        // 1. 初始化 dp 数组，dp[0] = 1 表示起点有一种方案
        std::vector<long long> dp(target + 1, 0);
        dp[0] = 1;
        const int MOD = 1e9 + 7;

        // 2. 遍历每一级台阶 (状态)
        for (int i = 1; i <= target; ++i) {
            // 3. 遍历每一种可能的步长 (转移选择)
            for (int step : steps) {
                if (i >= step) {
                    dp[i] = (dp[i] + dp[i - step]) % MOD;
                }
            }
        }

        return (int)dp[target];
    }
};

} // namespace AlgoTemplate


/*
 * @lc app=leetcode.cn id=3693 lang=cpp
 *
 * [3693] 爬楼梯 II
 */

// @lc code=start
class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        int len = costs.size();
        vector<int> dp(len+1,INT_MAX);
        dp[0] = 0;
        dp[1] = dp[0]+costs[0] + 1;
        if(len>=2) dp[2] = min(costs[1]+dp[0]+4,costs[1]+dp[1]+1);
        for(int i = 3; i <= len; i++) {
            dp[i] = min({costs[i-1]+dp[i-3]+9,costs[i-1]+dp[i-2]+4,costs[i-1]+dp[i-1]+1});
        }
        return dp[len];
    }
};
// @lc code=end