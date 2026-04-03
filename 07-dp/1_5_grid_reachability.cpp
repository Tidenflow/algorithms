/**
 * @file GridDP_Reachability.cpp
 * @brief 网格图DP模板一：到达型（从起点到当前点的最优解）
 * @logic
 * 状态：dfs(i, j) 表示从 (0,0) 到达 (i, j) 的最小/最大/路径数
 * 转移：要到达 (i, j)，只能从“上方”或“左方”过来
 * 公式：dfs(i, j) = min(dfs(i-1, j), dfs(i, j-1)) + cost[i][j]
 */
#include <bits/stdc++.h>
using namespace std;
namespace AlgoTemplate {

class GridReachability {
public:
    int solve(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // 记忆化数组
        vector<vector<int>> memo(m, vector<int>(n, -1));

        auto dfs = [&](auto&& self, int i, int j) -> int {
            // 1. 【边界处理】：如果越界，返回一个不影响 min 的极大值
            if (i < 0 || j < 0) return INT_MAX / 2; 
            
            // 2. 【入口/基准条件】：到达起点
            if (i == 0 && j == 0) return grid[0][0];

            // 3. 【记忆化】
            if (memo[i][j] != -1) return memo[i][j];

            // 4. 【转移】：从左边或者上边选一个最优的过来
            return memo[i][j] = min(self(self, i - 1, j), 
                                    self(self, i, j - 1)) + grid[i][j];
        };

        return dfs(dfs, m - 1, n - 1); // 从右下角终点开始递归
    }
};

} // namespace AlgoTemplate


// 3393. 统计异或值为给定值的路径数目
/**
 * @brief 网格图DP模板一：到达型 + 状态压缩(本题是异或和)
 * @logic
 * 状态：dfs(i, j, x) 表示从 (0,0) 到达 (i, j) 且路径异或和为 x 的方案数
 * 缩：此题没有滑动窗口的“缩”，但有递归的“回溯”
 * 关键点：逆向思维。如果要到达 (i, j) 时异或和为 x，那么到达 (i-1, j) 或 (i, j-1) 时的
 * 异或和必须是 x ^ grid[i][j] (因为 a ^ b = c 则 a = c ^ b)
 */

class Solution {
public:
    int countPathsWithXorValue(vector<vector<int>>& grid, int k) {
        const int MOD = 1'000'000'007;
        
        // 1. 【预处理范围】：计算网格中最大值对应的异或上限
        int mx = 0;
        for (auto& row : grid) {
            mx = max(mx, *max_element(row.begin(), row.end()));
        }
        // 计算异或和可能的上限（下一个 2 的幂）
        int u = 1;
        while (u <= mx) u <<= 1;
        
        // 如果目标 k 超过了所有可能产生的异或上限，直接无解
        if (k >= u) {
            return 0;
        }

        int m = grid.size(), n = grid[0].size();
        // 3D 记忆化数组：memo[行][列][当前要求的异或值]
        vector<vector<vector<int>>> memo(m, vector<vector<int>>(n, vector<int>(u, -1)));

        // 使用 C++23 的 explicit object parameter (this auto&& dfs)
        auto dfs = [&](this auto&& dfs, int i, int j, int x) -> int {
            // 2. 【边界处理】：如果坐标越界，说明这条路径走不通，返回 0
            if (i < 0 || j < 0) {
                return 0;
            }

            int val = grid[i][j];

            // 3. 【入口/基准条件】：到达起点 (0, 0)
            // 只有当起点的值恰好等于此时要求的异或值 x 时，才算找到 1 条合法路径
            if (i == 0 && j == 0) {
                return x == val;
            }

            // 4. 【记忆化】：检查是否计算过
            int& res = memo[i][j][x]; 
            if (res != -1) {
                return res;
            }

            // 5. 【转移/递推】：
            // 当前点 (i, j) 的值是 val，目标异或和是 x
            // 那么前一步的异或和必须是 x ^ val
            // 方案数 = 来自左边 (i, j-1) 的方案数 + 来自上边 (i-1, j) 的方案数
            //   x ^ val ^ val = x  异或运算的自反性（自取灭亡）
            return res = (dfs(i, j - 1, x ^ val) + dfs(i - 1, j, x ^ val)) % MOD;
        };

        // 从终点 (m-1, n-1) 开始递归，寻找异或和为 k 的路径数
        return dfs(m - 1, n - 1, k);
    }
};

