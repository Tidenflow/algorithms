/**
 * @file GridDP_Departure.cpp
 * @brief 网格图DP模板二：出发型（从当前点出发到终点的最优解）
 * @logic
 * 状态：dfs(i, j) 表示从 (i, j) 出发到达最后一行/目标状态的最小代价
 * 转移：从 (i, j) 下一步可以走到下一行的哪些位置
 * 公式：dfs(i, j) = min(dfs(i+1, j-1), dfs(i+1, j), dfs(i+1, j+1)) + cost[i][j]
 */
#include <bits/stdc++.h>
using namespace std;
namespace AlgoTemplate {

class GridDeparture {
public:
    int solve(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> memo(m, vector<int>(n, INT_MIN)); // 假设求最大

        auto dfs = [&](auto&& self, int i, int j) -> int {
            // 1. 【边界处理】：列越界
            if (j < 0 || j >= n) return INT_MIN / 2;

            // 2. 【入口/基准条件】：到达最后一行
            if (i == m - 1) return grid[i][j];

            // 3. 【记忆化】
            if (memo[i][j] != INT_MIN) return memo[i][j];

            // 4. 【转移】：向下方、左下、右下三个方向探索，选最强的
            int res = max({self(self, i + 1, j - 1), 
                           self(self, i + 1, j), 
                           self(self, i + 1, j + 1)});
            
            return memo[i][j] = res + grid[i][j];
        };

        // 可能需要遍历第一行的每一个点作为起点
        int ans = INT_MIN;
        for (int j = 0; j < n; ++j) {
            ans = max(ans, dfs(dfs, 0, j));
        }
        return ans;
    }
};

} // namespace AlgoTemplate


// 2304. 网格中的最小路径代价 
/**
 * @brief 网格图DP模板二：出发型（从当前点出发到最后一行的最小代价）
 * @logic
 * 状态：dfs(i, j) 表示从 (i, j) 出发到达最后一行所需要的最小代价
 * 转移：在 (i, j) 处，可以走向下一行的任意一列 k
 * 公式：dfs(i, j) = min(dfs(i+1, k) + moveCost[grid[i][j]][k]) + grid[i][j]
 */

class Solution {
public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int m = grid.size(), n = grid[0].size();
        
        // 记忆化数组：记录从 (i, j) 出发后的最小代价
        vector<vector<int>> memo(m, vector<int>(n));

        auto dfs = [&](this auto&& dfs, int i, int j) -> int {
            // 1. 【基准条件/递归边界】：已经到达最后一行
            // 从最后一行出发到最后一行，代价就是格子本身的值
            if (i == m - 1) { 
                return grid[i][j];
            }

            // 2. 【记忆化】：如果 res 不为 0，说明之前计算过该起点的结果
            auto& res = memo[i][j]; 
            if (res) { 
                return res;
            }

            // 3. 【初始化】：求最小值，初始设为无穷大
            res = INT_MAX;

            // 4. 【转移/探索】：枚举下一行的每一列 k
            for (int k = 0; k < n; k++) { 
                // 计算从 (i, j) 走到 (i+1, k) 的移动代价，加上从 (i+1, k) 往后走的递归代价
                res = min(res, dfs(i + 1, k) + moveCost[grid[i][j]][k]);
            }

            // 5. 【累加当前值】：别忘了加上当前格子 (i, j) 本身的权值
            res += grid[i][j];
            return res;
        };

        // 6. 【入口】：因为可以从第一行的任意一个格子出发
        // 我们需要遍历第一行的所有列，取其中的最小值
        int ans = INT_MAX;
        for (int j = 0; j < n; j++) { 
            ans = min(ans, dfs(0, j));
        }
        return ans;
    }
};