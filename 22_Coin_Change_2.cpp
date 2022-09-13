// Coin change 2 (https://practice.geeksforgeeks.org/problems/coin-change2448/1)
// DP ON SUBSEQUENCE / SUBSETS / TARGET

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

long long solve(int ind, int T, int coins[], vector<vector<long long>> &dp)
{
    if (ind == 0)
    {
        if (T % coins[0] == 0)
            return 1;
        else
            return 0;
    }

    if (dp[ind][T] != -1)
        return dp[ind][T];

    long long notTake = solve(ind - 1, T, coins, dp);
    long long take = 0;
    if (T >= coins[ind])
    {
        take = solve(ind, T - coins[ind], coins, dp);
    }
    return dp[ind][T] = notTake + take;
}

long long solve_2(int n, int coins[], int target)
{
    vector<vector<long long>> dp(n, vector<long long>(target + 1, 0));

    for (int T = 0; T <= target; T++)
    {

        if (T % coins[0] == 0)
            dp[0][T] = 1;
        else
            dp[0][T] = 0;
    }

    for (int ind = 1; ind < n; ind++)
    {
        for (int T = 0; T <= target; T++)
        {
            long long notTake = dp[ind - 1][T];
            long long take = 0;
            if (T >= coins[ind])
            {
                take = dp[ind][T - coins[ind]];
            }

            dp[ind][T] = notTake + take;
        }
    }
    return dp[n-1][target];
}


long long solve_3(int n, int coins[], int target)
{
    vector<long long> prev(target+1, 0), cur(target+1, 0);

    for (int T = 0; T <= target; T++)
    {

        if (T % coins[0] == 0)
            prev[T] = 1;
        else
            prev[T] = 0;
    }

    for (int ind = 1; ind < n; ind++)
    {
        for (int T = 0; T <= target; T++)
        {
            long long notTake = prev[T];
            long long take = 0;
            if (T >= coins[ind])
            {
                take = cur[T - coins[ind]];
            }

            cur[T] = notTake + take;
        }
        prev = cur;
    }
    return prev[target];
}

long long int count(int coins[], int n, int target)
{
    vector<vector<long long>> dp(n, vector<long long>(target + 1, -1));
    return solve(n - 1, target, coins, dp);
}