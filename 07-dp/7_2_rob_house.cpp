/**
 * @file HouseRobberTemplate.cpp
 * @brief 打家劫舍 (不相邻元素最大和) 算法模板
 * @reference 灵茶山艾府 (https://github.com/endlesscheng)
 * 核心逻辑：
 * 1. 状态定义：dp[i] 表示考虑到第 i 个元素时能获得的最大收益
 * 2. 选：如果选第 i 个，则不能选 i-1，收益为 dp[i-2] + val[i]
 * 3. 不选：如果不选第 i 个，收益同 dp[i-1]
 * * 一句话：当前最大 = max(不选上一家, 选这一家+上上家)
 */


#include <bits/stdc++.h>


using namespace std;

namespace AlgoTemplate {

class HouseRobber {
public:
    /**
     * @brief 通用打家劫舍框架 (以求数组不相邻元素最大和为例)
     * @param values 转换后的价值数组 (如桶计数的总和)
     */
    static int solve(const std::vector<int>& values) {
        int n = values.size();
        if (n == 0) return 0;
        if (n == 1) return values[0];

        // 1. 【初始化】
        std::vector<int> dp(n, 0);
        dp[0] = values[0];
        dp[1] = std::max(values[0], values[1]);

        // 2. 【状态转移】
        for (int i = 2; i < n; ++i) {
            // dp[i] = max(不选当前, 选当前+上上个状态)
            dp[i] = std::max(dp[i - 1], dp[i - 2] + values[i]);
        }

        return dp[n - 1];
    }
};

} // namespace AlgoTemplate

//740. 删除并获得点数
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if (nums.empty()) return 0;

        // 1. 【预处理】找到最大值确定范围
        int mx = 0;
        for (int x : nums) mx = max(mx, x);

        // 2. 【转化】构造财富数组 (把删除点数问题 转化为 打家劫舍模型)
        // 索引即数值，sum[i] 即该数值的总价值
        vector<int> sum(mx + 1, 0);
        for (int x : nums) {
            sum[x] += x;
        }

        // 3. 【应用模板】执行打家劫舍逻辑
        // 这里直接展开模板内容，逻辑更清晰
        int n = sum.size();
        vector<int> dp(n, 0);
        
        // 初始化数值 0 和 1 的情况
        dp[0] = sum[0]; 
        if (n > 1) {
            dp[1] = max(sum[0], sum[1]);
        }

        // 状态转移：从数值 2 开始考虑
        for (int i = 2; i < n; ++i) {
            // i 代表当前考虑的数值
            // dp[i-1] 表示不拿数值 i
            // dp[i-2] + sum[i] 表示拿了数值 i，则必须放弃 i-1
            dp[i] = max(dp[i - 1], dp[i - 2] + sum[i]);
        }

        return dp[n - 1];
    }
};