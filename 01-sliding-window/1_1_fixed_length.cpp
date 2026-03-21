/**
 * @file FixedSizeSlidingWindow.cpp
 * @brief 定长滑动窗口算法模板
 * @reference 灵茶山艾府 (https://github.com/endlesscheng)
 * * 核心逻辑：
 * 1. 入：下标为 i 的元素进入窗口
 * 2. 更新：当窗口长度达到 k 时，更新答案
 * 3. 出：下标为 i-k+1 的元素离开窗口
 */

#include <vector>
#include <algorithm>
#include <iostream>

namespace AlgoTemplate {

class SlidingWindow {
public:
    /**
     * @brief 定长滑动窗口通用框架 (以求窗口最大和为例)
     * @param nums 输入数组
     * @param k 窗口长度
     */
    static int solve(const std::vector<int>& nums, int k) {
        int n = nums.size();
        int max_ans = 0;
        int current_running_stat = 0; // 这里的"统计量"可以是和、乘积、哈希表计数等

        for (int i = 0; i < n; ++i) {
            // 1. 【入】右窗口进入，更新当前状态
            current_running_stat += nums[i];

            // 如果窗口还没达到 k，继续补齐
            if (i < k - 1) {
                continue;
            }

            // 2. 【更新】此时窗口长度正好为 k，记录/更新答案
            max_ans = std::max(max_ans, current_running_stat);

            // 3. 【出】左窗口离开，为下一轮滑动做准备
            // 左边界下标为 i - k + 1
            current_running_stat -= nums[i - k + 1];
        }

        return max_ans;
    }
};

} // namespace AlgoTemplate

// ---------------------------------------------------------
// 实战示例：LeetCode 1343. 大于等于阈值的平均值子数组数目
// ---------------------------------------------------------
int numOfSubarrays(std::vector<int>& arr, int k, int threshold) {
    int count = 0;
    int sum = 0;
    int target = k * threshold;

    for (int i = 0; i < arr.size(); ++i) {
        sum += arr[i]; // 入
        if (i < k - 1) continue;
        
        if (sum >= target) count++; // 更新答案
        
        sum -= arr[i - k + 1]; // 出
    }
    return count;
}