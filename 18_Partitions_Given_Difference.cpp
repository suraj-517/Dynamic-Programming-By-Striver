// Partitions With Given Difference (https://www.codingninjas.com/codestudio/problems/partitions-with-given-difference_3751628)
// DP ON SUBSEQUENCE / SUBSETS / TARGET

/*
       S1 - S2 = D , S1 + S2 = Sum
    => Sum - S2 - S2 = D
    => Sum - D = 2*S2
    => S2 = (Sum - D)/2

*/

#include <iostream>
#include <vector>
using namespace std;

int mod = (int)(1e9+7);

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

    int ans = (notTake + take) % mod;
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

            int ans = (notTake + take) % mod;
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
            cur[j] = ans % mod;
        }
        prev = cur;
    }
    return prev[sum];
}

int countPartitions(int n, int d, vector<int> &arr)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    int target = sum - d;

    if (target < 0 || target % 2 == 1)
        return 0;
    else
    {   vector<vector<int>> dp(n, vector<int>(target/2, -1));
        return solve(n - 1, target/2, arr, dp);
    }
        
}