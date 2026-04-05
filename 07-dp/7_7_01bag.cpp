/**
 * @file Knapsack01_DFS.cpp
 * @brief 0/1 背包通用模板：求满足条件的某种最值（最大价值/最长长度/最少个数）
 * @logic 
 * 1. 选：dfs(i - 1, j - w[i]) + v[i] (剩余目标减小，结果累加)
 * 2. 不选：dfs(i - 1, j) (目标不变，结果直接继承)
 * 3. 记：memo[i][j] 存下当前“进度+余额”组合下的最优解   二维数组！！！
 */

namespace AlgoTemplate {

class Knapsack01 {
public:
    static int solve(vector<int>& nums, int target) {
        int n = nums.size();
        // 1. 【记忆化数组】为什么要二维？
        // 状态由两个变量锁定：i (处理到哪了) 和 j (还剩多少目标)
        // 不同的 j 会导致后续完全不同的决策路径，必须分开存储。
        vector<vector<int>> memo(n, vector<int>(target + 1, -2));

        auto dfs = [&](this auto&& self, int i, int j) -> int {
            // 2. 【边界值/基准情况】
            if (j == 0) return 0;           // 目标达成：通常返回 0，表示后续无需额外代价
            if (i < 0 || j < 0) return -1e9; // 彻底失败：越界或目标透支，返回“剧毒”负数防止被选中

            // 3. 【查表】
            int& res = memo[i][j];
            if (res != -2) return res;

            // 4. 【选与不选的博弈】
            // 不选当前 nums[i]
            int not_pick = self(i - 1, j);
            
            // 选当前 nums[i]（此时目标 j 减小，结果值 +1 或 +nums[i]）
            int pick = self(i - 1, j - nums[i]) + 1; 

            // 5. 【更新与返回】
            return res = std::max(not_pick, pick);
        };

        int ans = dfs(n - 1, target);
        return ans < 0 ? -1 : ans; // 统一翻译非法值
    }
};

} // namespace AlgoTemplate


// (1) 为什么 memo 数组必须是二维？
// 状态的唯一性：如果你只记录 i（我处理到第几个数），你丢失了 j（我手里还剩多少钱）。
// 举例：你和朋友都走到了第 5 关，但你剩 100 血，他剩 10 血。后续的通关难度（结果）能一样吗？显然不能。
// 所以必须用 memo[关卡][血量] 两个坐标来精准定位你的“存档”。

// (2) 边界值的“剧毒”逻辑
// -1e9 (非法态)：它代表这一步是死路。在 max 操作中，我们要确保“死路 + 1”依然是死路，不能让它翻身。
// 0 (成功态)：它代表目标达成。所有的 +1 最终都是累加在这些 0 之上的。



// [2915] 和为目标值的最长子序列的长度
class Solution {
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int m = nums.size();
        // 1. 记忆化数组必须是二维：memo[m][target + 1]
        // 初始化为 -2，因为题目结果可能是 -1，我们要区分“未计算”和“无解”
        vector<vector<int>> memo(m, vector<int>(target + 1, -2));
        auto dfs = [&](this auto&& dfs,int i, int j) -> int {
            // 基准情况：目标达成
            if (j == 0) return 0;
            // 基准情况：数组用完或目标越界
            if (i < 0 || j < 0) return -1e9;

            int& res = memo[i][j];
            if (res != -2) return res;

            // 选与不选的博弈：
            // 不选：直接看上一个状态
            int not_pick = dfs(i - 1, j);

            // 选：上一个状态的长度 + 1 
            int pick = dfs(i - 1, j - nums[i]) + 1;

            return res = max(not_pick, pick);
        };
        int ans = dfs(m - 1, target);
        // 如果最终结果小于 0，说明凑不出来，按题目要求返回 -1
        return ans < 0 ? -1 : ans;
    }
};
// @lc code=end

