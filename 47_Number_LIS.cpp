// Number of Longest Increasing Subsequence (https://leetcode.com/problems/number-of-longest-increasing-subsequence/)
// Based on LIS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    For a sequence of numbers,
    cnt[k] is total number of longest subsequence ending with nums[k];
    dp[k] is the length of longest subsequence ending with nums[k];
*/

int findNumberOfLIS(vector<int> &nums)
{
    int n = nums.size(), maxlen = 1, ans = 0;
    vector<int> cnt(n, 1), dp(n, 1);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (nums[i] > nums[j])
            {
                // inherit
                if (dp[j] + 1 > dp[i])
                {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                }
                // increase the count
                else if (dp[j] + 1 == dp[i])
                    cnt[i] += cnt[j];
            }
        }
        maxlen = max(maxlen, dp[i]);
    }

    // find the longest increasing subsequence of the whole sequence
    // sum valid counts
    for (int i = 0; i < n; i++)
    {
        if (dp[i] == maxlen)
            ans += cnt[i];
    }

    return ans;
}