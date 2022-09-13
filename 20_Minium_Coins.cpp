// Minium No. of Coins (https://practice.geeksforgeeks.org/problems/number-of-coins1824/1)
// DP ON SUBSEQUENCE / SUBSETS / TARGET

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int solve(int ind, int T, int coins[], vector<vector<int>> &dp)
{
    if (ind == 0)
    {
        if (T % coins[0] == 0)
            return T / coins[0];
        else
            return 1e9;
    }

    if (dp[ind][T] != -1)
        return dp[ind][T];

    int notTake = 0 + solve(ind - 1, T, coins, dp);
    int take = INT_MAX;
    if (T >= coins[ind])
    {
        take = 1 + solve(ind, T - coins[ind], coins, dp);
    }

    return dp[ind][T] = min(notTake, take);
}

int solve_2(int n, int coins[], int target)
{
    vector<vector<int>> dp(n, vector<int>(target + 1, 0));

    for (int T = 0; T <= target; T++)
    {
        if (T % coins[0] == 0)
            dp[0][T] = T / coins[0];
        else
            dp[0][T] = 1e9;
    }

    for (int i = 1; i < n; i++)
    {
        for (int T = 0; T <= target; T++)
        {
            int notTake = 0 + dp[i - 1][T];
            int take = INT_MAX;
            if (T >= coins[i])
            {
                take = 1 + dp[i][T - coins[i]];
            }

            dp[i][T] = min(notTake, take);
        }
    }

    int ans = dp[n - 1][target];
    if (ans >= 1e9)
        return -1;
    else
        return ans;
}


int solve_3(int n, int coins[], int target)
{
    vector<int> prev(target+1, 0), cur(target+1, 0);

    for (int T = 0; T <= target; T++)
    {
        if (T % coins[0] == 0)
            prev[T] = T / coins[0];
        else
            prev[T] = 1e9;
    }

    for (int i = 1; i < n; i++)
    {
        for (int T = 0; T <= target; T++)
        {
            int notTake = 0 + prev[T];
            int take = INT_MAX;
            if (T >= coins[i])
            {
                take = 1 + cur[T - coins[i]];
            }

            cur[T] = min(notTake, take);
        }
        prev = cur;
    }

    int ans = prev[target];
    if (ans >= 1e9)
        return -1;
    else
        return ans;
}

int minCoins(int coins[], int n, int target)
{
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    int ans = solve(n - 1, target, coins, dp);

    if (ans >= 1e9)
        return -1;
    else
        return ans;
}