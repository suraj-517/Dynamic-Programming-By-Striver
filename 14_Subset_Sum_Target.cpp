//  Subset Sum Problem (https://practice.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1)
// DP ON SUBSEQUENCE/SUBSETS/TARGET

#include <iostream>
#include <vector>
using namespace std;

bool solve(int i, int sum, vector<int> &arr, vector<vector<int>> &dp)
{
    if (sum == 0)
        return true;

    if (i == 0)
        return arr[0] == sum;

    if (dp[i][sum] != -1)
        return dp[i][sum];

    bool notTake = solve(i - 1, sum, arr, dp);
    bool take = false;
    if (sum >= arr[i])
        take = solve(i - 1, sum - arr[i], arr, dp);

    bool ans = notTake | take;
    return dp[i][sum] = ans;
}

bool solve_2(int n, int sum, vector<int> &arr)
{
    vector<vector<bool>> dp(n, vector<bool>(sum + 1, 0));
    for (int i = 0; i < n; i++)
        dp[i][0] = true;

    if (arr[0] <= sum)
        dp[0][arr[0]] = true;

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            bool notTake = dp[i - 1][j];
            bool take = false;

            if (j >= arr[i])
                take = dp[i - 1][j - arr[i]];

            bool ans = notTake | take;
            return dp[i][j] = ans;
        }
    }
    return dp[n - 1][sum];
}

bool solve_3(int n, int sum, vector<int> &arr)
{
    vector<int> prev(sum + 1, 0), cur(sum + 1, 0);
    prev[0] = cur[0] = true;

    if (arr[0] <= sum)
        prev[arr[0]] = true;

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            bool notTake = prev[j];
            bool take = false;
            if (j >= arr[i])
                take = prev[j - arr[i]];

            bool ans = notTake | take;
            cur[j] = ans;
        }
        prev = cur;
    }
    return prev[sum];
}

bool isSubsetSum(vector<int> arr, int sum)
{
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
    return solve(n - 1, sum, arr, dp);
}