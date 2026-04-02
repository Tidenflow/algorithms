/**
 * @file MaxSubArrayPrefixSum.cpp        最大子段和 = 结尾的前缀和 - 结尾之前的最小前缀和
 * @brief 最大子数组和 (前缀和视角) 模板
 * 核心逻辑：
 * 1. 子数组 sum(i, j) = prefixSum[j+1] - prefixSum[i]
 * 2. 要使子数组和最大，固定右端点 j，寻找左侧最小的前缀和 minPrefix
 * 3. 公式：MaxSum = max(prefixSum[j] - minPrefix)
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

namespace AlgoTemplate {

class MaxSubArrayPrefix {
public:
    /**
     * @brief 前缀和实现
     * 时间复杂度: O(n), 空间复杂度: O(1) (边算边存最小前缀和)
     */
    static int solve(const vector<int>& nums) {
        // ans 初始化为最小整数，或 nums[0]
        int ans = INT_MIN;
        
        // 1. 【核心变量】
        int curPrefixSum = 0; // 当前的前缀和
        int minPrefixSum = 0; // 记录遍历过程中遇到的最小前缀和 (初始为 0 处理从头开始的情况)

        for (int x : nums) {
            // 2. 更新当前前缀和
            curPrefixSum += x;
            
            // 3. 计算以当前元素结尾的最大子数组和
            // 即：当前前缀和 - 之前最小的前缀和
            ans = max(ans, curPrefixSum - minPrefixSum);
            
            // 4. 更新最小前缀和，供后面使用
            minPrefixSum = min(minPrefixSum, curPrefixSum);
        }

        return ans;
    }
};

} // namespace AlgoTemplate


// 53. 最大子数组和
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = INT_MIN;
        int min_pre_sum = 0;
        int pre_sum = 0;
        for (int x : nums) {
            pre_sum += x; // 当前的前缀和
            ans = max(ans, pre_sum - min_pre_sum); // 减去前缀和的最小值
            min_pre_sum = min(min_pre_sum, pre_sum); // 维护前缀和的最小值
        }
        return ans;
    }
};

