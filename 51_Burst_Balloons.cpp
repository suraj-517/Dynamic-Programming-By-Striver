// Burst Balloons (https://leetcode.com/problems/burst-balloons/)
// Partition DP

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
solve(nums, i, j)
    by which I mean that we need to burst balloons starting from index i to index j. At the beginning, they'll be 0, nums.size() -1 respectively. Let's suppose we burst the kth balloon in the first chance. We will get nums[k-1] * nums[k] * nums[k+1] coins.

Notes:
    So, as we saw that if we choose the kth balloon to be the first one to be burst, we can't make the subproblems independent. Let's try the other way round. We choose the kth balloon as the last one to be burst. Now the subproblems will become independent since (k - 1)th balloon and (k + 1)th balloon won't need each other in order to calculate the answer. (Try it out using pen and paper).

    Important point to be noted here is that the balloons in the range (i, k - 1) and (k + 1, j) will be burst BEFORE kth balloon. So, when we burst the kth balloon, the profit will be nums[i - 1] * nums[k] * nums[j + 1] PROVIDED that index i - 1 and j + 1 are valid.

Link for Explaination : https://leetcode.com/problems/burst-balloons/discuss/892552/For-those-who-are-not-able-to-understand-any-solution-WITH-DIAGRAM

*/

int solve(int i, int j, vector<int> &arr, vector<vector<int>> &dp)
{
    if (i > j)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int maxi = -1e9;
    for (int k = i; k <= j; k++)
    {
        int cost = arr[i - 1] * arr[k] * arr[j + 1] + solve(i, k - 1, arr, dp) + solve(k + 1, j, arr, dp);
        maxi = max(maxi, cost);
    }
    return dp[i][j] = maxi;
}

int solve_2(int n, vector<int> &arr)
{
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i > j)
                continue;

            int maxi = -1e9;
            for (int k = i; k <= j; k++)
            {
                int cost = arr[i - 1] * arr[k] * arr[j + 1] + dp[i][k - 1] + dp[k + 1][j];
                maxi = max(maxi, cost);
            }
            dp[i][j] = maxi;
        }
    }
    return dp[1][n];
}

int maxCoins(vector<int> &nums)
{
    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    nums.push_back(1);
    nums.insert(nums.begin(), 1);
    return solve(1, n, nums, dp); // new_n = n+2
}