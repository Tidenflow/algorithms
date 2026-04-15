/**
 * @file BoundedKnapsack_DFS.cpp
 * @brief 多重背包通用模板：每个物品最多选 s[i] 次
 * @logic 
 * 1. 核心变化：在当前层通过 for 循环枚举选 0, 1, 2, ..., s[i] 个
 * 2. 下一步：总是去 dfs(i - 1, j - k * w[i])，因为当前物品的额度已在这一层枚举完
 */
#include <bits/stdc++.h>
using namespace std;

namespace AlgoTemplate {

class BoundedKnapsack {
public:
    // ================== 类型 A：求最值 (如：最大价值) ==================
    // w: 重量, v: 价值, s: 数量限制
    static int solveMax(vector<int>& w, vector<int>& v, vector<int>& s, int target) {
        int n = w.size();
        vector<vector<int>> memo(n, vector<int>(target + 1, -1));

        auto dfs = [&](this auto&& self, int i, int j) -> int {
            if (i < 0) return 0; // 基础情况：没东西选了，价值为 0

            int& res = memo[i][j];
            if (res != -1) return res;

            res = 0; 
            // 💡 重点：枚举当前物品选 k 个，k 不能超过库存 s[i]，也不能让背包超重
            for (int k = 0; k <= s[i] && k * w[i] <= j; ++k) {
                res = max(res, self(i - 1, j - k * w[i]) + k * v[i]);
            }
            return res;
        };
        return dfs(n - 1, target);
    }

    // ================== 类型 B：求方案数 ==================
    static int solveWays(vector<int>& w, vector<int>& s, int target) {
        int n = w.size();
        vector<vector<long long>> memo(n, vector<long long>(target + 1, -1));

        auto dfs = [&](this auto&& self, int i, int j) -> long long {
            if (j == 0) return 1;    // 凑齐了：找到 1 种方案
            if (i < 0) return 0;    // 没物品了且目标未达成

            long long& res = memo[i][j];
            if (res != -1) return res;

            res = 0;
            // 💡 重点：累加所有可能的选择分支
            for (int k = 0; k <= s[i] && k * w[i] <= j; ++k) {
                res += self(i - 1, j - k * w[i]);
            }
            return res;
        };
        return dfs(n - 1, target);
    }

    // ================== 进阶：二进制拆分（优化为 0-1 背包） ==================
    // 如果 s[i] 很大，上面的 for 循环会超时。将 s[i] 拆成 1, 2, 4... 组合
    static int solveByBinarySplitting(vector<int>& w, vector<int>& v, vector<int>& s, int target) {
        struct Item { int weight, value; };
        vector<Item> new_items;

        for (int i = 0; i < w.size(); ++i) {
            int num = s[i];
            for (int k = 1; num > 0; k <<= 1) {
                int real_k = min(k, num);
                new_items.push_back({real_k * w[i], real_k * v[i]});
                num -= real_k;
            }
        }
        // 此时 new_items 已经变成了普通的 0-1 背包问题，直接套用 0-1 背包 DFS 即可
        return solveStandard01(new_items, target);
    }
};

} // namespace AlgoTemplate