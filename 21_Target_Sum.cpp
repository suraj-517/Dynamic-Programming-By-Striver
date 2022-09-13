// Target Sum (https://leetcode.com/problems/target-sum/)
// DP ON SUBSEQUENCE / SUBSETS / TARGET
// similar to 18. Partitions With Given Difference


#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

/*
       S1 - S2 = D , S1 + S2 = Sum
    => Sum - S2 - S2 = D
    => Sum - D = 2*S2
    => S2 = (Sum - D)/2

*/


int solve(int i, int sum, vector<int> &arr, vector<vector<int>> &dp)
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

    int ans = (notTake + take);
    return dp[i][sum] = ans;
}

int solve_2(int n, int sum, vector<int> &arr)
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

            int ans = (notTake + take) ;
            dp[i][j] = ans;
        }
    }
    return dp[n - 1][sum];
}

int solve_3(int n, int sum, vector<int> &arr)
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
            cur[j] = ans ;
        }
        prev = cur;
    }
    return prev[sum];
}


int findTargetSumWays(vector<int> &arr, int d)
{
    int n = arr.size();
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    int target = sum - d;

    if (target < 0 || target % 2 == 1)
        return 0;
    else
    {   
        return solve_3(n - 1, target/2, arr);
    }
}