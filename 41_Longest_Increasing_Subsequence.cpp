// Longest Increasing Subsequence (https://leetcode.com/problems/longest-increasing-subsequence/)

#include <iostream>
#include <vector>
using namespace std;

// f(3, 0) ===> Length of LIS starting from index 3, whose previous index is 0.
// ind -> 0 to n-1 -> {N}
// prevIndex -> -1 to n-1 -> {N+1} (co-ordinate change, -1 -> 0)
// T = O(N^2), S = O(N^2)(DP) + O(N)(stack)

int solve(int ind, int prevInd, vector<int> &arr, int n, vector<vector<int>> &dp)
{
    if (ind == n)
        return 0;

    if (dp[ind][prevInd + 1] != -1)
        return dp[ind][prevInd];

    int notTake = 0 + solve(ind + 1, prevInd, arr, n, dp);
    int take = 0;
    if (prevInd == -1 || arr[ind] > arr[prevInd])
    {
        take = 1 + solve(ind + 1, ind, arr, n, dp);
    }
    return dp[ind][prevInd + 1] = max(take, notTake);
}

int solve_2(int n, vector<int> &arr)
{
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int prevInd = ind - 1; prevInd >= -1; prevInd--)
        {
            int notTake = 0 + dp[ind + 1][prevInd + 1]; // co-ordinate change/shift
            int take = 0;
            if (prevInd == -1 || arr[ind] > arr[prevInd])
            {
                take = 1 + dp[ind + 1][ind + 1]; // co-ordinate change/shift
            }
            dp[ind][prevInd + 1] = max(take, notTake);
        }
    }

    return dp[0][-1 + 1];
}

int solve_3(int n, vector<int> &arr)
{
    vector<int> next(n + 1, 0), cur(n + 1, 0);

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int prevInd = ind - 1; prevInd >= -1; prevInd--)
        {
            int notTake = 0 + next[prevInd + 1]; // co-ordinate change/shift
            int take = 0;
            if (prevInd == -1 || arr[ind] > arr[prevInd])
            {
                take = 1 + next[ind + 1]; // co-ordinate change/shift
            }
            cur[prevInd + 1] = max(take, notTake);
        }
        next = cur;
    }

    return next[-1 + 1];
}

// Let dp[i] is the longest increase subsequence of nums[0..i] which has nums[i] as the end element of the subsequence.
// T = O(N^2), S = O(N)
int solve_4(int n, vector<int> &arr)
{
    vector<int> dp(n, 1);

    int maxi = 1;
    for (int i = 0; i < n; i++)
    {
        for (int prev = 0; prev < i; prev++)
        {
            if (arr[i] > arr[prev] && dp[prev] + 1 > dp[i])
            {
                dp[i] = dp[prev] + 1;
            }
        }
        maxi = max(maxi, dp[i]);
    }

    return maxi;
}

int lengthOfLIS(vector<int> &nums)
{
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    return solve(0, -1, nums, n, dp);
}