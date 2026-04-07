/**
 * @file CompleteKnapsack_DFS.cpp
 * @brief 完全背包通用模板：区分【最值问题】与【方案数问题】(加不加一的问题)
 * @logic 
 * 1. 选：dfs(i, j - w[i]) (注意：下标依然是 i，表示可以重复选)
 * 2. 不选：dfs(i - 1, j) (彻底放弃当前物品，去处理前一个)
 */
#include <bits/stdc++.h>
using namespace std;

namespace AlgoTemplate {

class CompleteKnapsack {
public:
    // ================== 类型 A：求最值 (如：最少硬币数、最大价值) ==================
    static int solveMinMax(vector<int>& nums, int target) {
        int n = nums.size();
        // 初始值 -1 表示未计算
        vector<vector<int>> memo(n, vector<int>(target + 1, -1));

        auto dfs = [&](this auto&& self, int i, int j) -> int {
            if (j == 0) return 0;          // 目标达成：代价为 0
            if (i < 0) return 1e9;         // 物品用完但目标未达成：返回“剧毒”正无穷（求最小用 1e9，求最大用 -1e9）

            int& res = memo[i][j];
            if (res != -1) return res;

            // 1. 不选当前物品：只能去下一关
            int not_pick = self(i - 1, j);

            // 2. 选当前物品：目标减小，但人留在原地(i)，且代价 +1
            int pick = 1e9;
            if (j >= nums[i]) {
                pick = self(i, j - nums[i]) + 1; // 💡 重点：这里是 i 不是 i-1，且有 +1
            }

            return res = std::min(not_pick, pick); // 或者是 max
        };
        return dfs(n - 1, target);
    }

    // ================== 类型 B：求方案数 (如：零钱兑换 II) ==================
    static int solveWays(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<long long>> memo(n, vector<long long>(target + 1, -1));

        auto dfs = [&](this auto&& self, int i, int j) -> int {
            if (j == 0) return 1;          // 目标达成：找到 1 种有效方案
            if (i < 0) return 0;           // 物品用完：无法形成方案，返回 0

            long long& res = memo[i][j];
            if (res != -1) return res;

            // 1. 不选：继承之前的方案数
            int not_pick = self(i - 1, j);

            // 2. 选：目标减小，人留原地(i)，方案数直接累加
            int pick = 0;
            if (j >= nums[i]) {
                pick = self(i, j - nums[i]);    // 💡 重点：这里没有 +1，只是路径合并
            }

            return res = not_pick + pick;       // 💡 重点：这里是加号
        };
        return dfs(n - 1, target);
    }
};

} // namespace AlgoTemplate