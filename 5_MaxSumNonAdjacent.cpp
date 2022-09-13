// Maximum sum of non-adjacent elements (https://www.codingninjas.com/codestudio/problems/maximum-sum-of-non-adjacent-elements_843261?leftPanelTab=0)

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int solve(int ind, vector<int> &nums, vector<int> &dp)
{
    if (ind == 0)
        return nums[ind];

    if (ind < 0)
        return 0;

    if (dp[ind] != -1)
        return dp[ind];

    int pick = nums[ind] + solve(ind - 2, nums, dp);
    int notPick = 0 + solve(ind - 1, nums, dp);
    return dp[ind] = max(pick, notPick);
}

int solve_2(vector<int> &dp, vector<int> &nums, int n)
{
    dp[0] = nums[0];
    for(int i = 1; i < n; i++)
    {
        int pick = nums[i];
        if(i > 1) pick+= dp[i-2];
        int notPick = 0 + dp[i-1];
        dp[i] = max(pick, notPick);
    }
    return dp[n-1];
}

int solve_3(vector<int> &nums, int n)  // Space optimisation
{
    int prev = nums[0];
    int prev2 = 0;
    for(int i = 1; i < n; i++)
    {
        int pick = nums[i] + prev2;
        int notPick = 0 + prev;
        int cur1 = max(pick, notPick);
        prev2 = prev;
        prev = cur1;
    }
    return prev;
}

int maximumNonAdjacentSum(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n, -1);
    return solve(n - 1, nums, dp);
}