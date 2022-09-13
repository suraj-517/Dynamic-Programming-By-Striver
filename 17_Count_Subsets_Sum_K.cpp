// Count No. of subsets with k sum (https://practice.geeksforgeeks.org/problems/perfect-sum-problem5633/1)
// DP ON SUBSEQUENCE / SUBSETS / TARGET

#include <iostream>
#include <vector>
using namespace std;

int mod = (int)(1e9 + 7);

/*
    * if zero is present in the array then base case :

    if(i == 0)
    {
        if(sum == 0 && nums[0] == 0) return 2;
        if(sum == 0 || sum == nums[0]) return 1;
        return 0;
    }
*/

int solve(int i, int sum, int *arr, vector<vector<int>> &dp)
{
    if (i == 0)
    {
        if (sum == 0 && arr[0] == 0) // 2 option -> take + notTake
            return 2;
        if (sum == 0 || sum == arr[0])
            return 1;
        return 0;
    }

    if (dp[i][sum] != -1)
        return dp[i][sum];

    int notTake = solve(i - 1, sum, arr, dp);
    int take = 0;
    if (sum >= arr[i])
        take = solve(i - 1, sum - arr[i], arr, dp);

    int ans = (notTake + take) % mod;
    return dp[i][sum] = ans;
}

int solve_2(int n, int sum, int *arr)
{
    vector<vector<int>> dp(n, vector<int>(sum + 1, 0));

    if (arr[0] == 0)
        dp[0][0] = 2;
    else
        dp[0][0] = 1;

    if (arr[0] != 0 && arr[0] <= sum)
        dp[0][arr[0]] = 1;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= sum; j++)
        {
            int notTake = dp[i - 1][j];
            int take = 0;

            if (j >= arr[i])
                take = dp[i - 1][j - arr[i]];

            int ans = (notTake + take) % mod;
            dp[i][j] = ans;
        }
    }
    return dp[n - 1][sum];
}

int solve_3(int n, int sum, int *arr)
{
    vector<int> prev(sum + 1, 0), cur(sum + 1, 0);
    if (arr[0] == 0)
        prev[0] = 2;
    else
        prev[0] = 1;

    if (arr[0] != 0 && arr[0] <= sum)
        prev[arr[0]] = 1;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= sum; j++)
        {
            int notTake = prev[j];
            int take = 0;
            if (j >= arr[i])
                take = prev[j - arr[i]];

            int ans = notTake + take;
            cur[j] = ans % mod;
        }
        prev = cur;
    }
    return prev[sum];
}

int perfectSum(int arr[], int n, int sum)
{
    vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
    return solve(n - 1, sum, arr, dp);
}