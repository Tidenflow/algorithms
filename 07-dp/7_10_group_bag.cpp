/**
 * @file GroupKnapsack_DFS.cpp
 * @brief 分组背包模板：每一组物品中【最多只能选一个】
 * @logic 
 * 1. 核心变化：当前层 dfs(i, j) 代表处理第 i 组
 * 2. 决策：枚举组内的每一个物品 k，选它则跳到下一组 dfs(i - 1, j - w[i][k])
 */
#include <bits/stdc++.h>
using namespace std;

namespace AlgoTemplate {

class GroupKnapsack {
public:
    // weights[i][k] 表示第 i 组第 k 个物品的重量，values 同理
    static int solveMax(vector<vector<int>>& weights, vector<vector<int>>& values, int target) {
        int n = weights.size(); // 组数
        vector<vector<int>> memo(n, vector<int>(target + 1, -1));

        auto dfs = [&](this auto&& self, int i, int j) -> int {
            if (i < 0) return 0;

            int& res = memo[i][j];
            if (res != -1) return res;

            // 决策 1：这一组我一个都不选
            res = self(i - 1, j);

            // 决策 2：枚举选这一组里的某【一个】物品
            // 💡 这里的 for 循环和多重背包很像，但含义不同：
            // 多重背包选的是“个数”，分组背包选的是“具体的哪一个”
            for (int k = 0; k < weights[i].size(); ++k) {
                if (j >= weights[i][k]) {
                    res = max(res, self(i - 1, j - weights[i][k]) + values[i][k]);
                }
            }
            return res;
        };
        return dfs(n - 1, target);
    }
};

} // namespace AlgoTemplate