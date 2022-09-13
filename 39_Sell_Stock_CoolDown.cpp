// Best Time to Buy and Sell Stock with Cooldown (https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)
// DP on Stock

#include <iostream>
#include <vector>
using namespace std;

int solve(int ind, int buy, vector<int> &prices, int n, vector<vector<int>> &dp)
{
    if (ind >= n)
        return 0;

    if (dp[ind][buy] != -1)
        return dp[ind][buy];

    if (buy == 1)
        return dp[ind][buy] = max(-prices[ind] + solve(ind + 1, 0, prices, n, dp), 0 + solve(ind + 1, 1, prices, n, dp));
    else
        return dp[ind][buy] = max(prices[ind] + solve(ind + 2, 1, prices, n, dp), 0 + solve(ind + 1, 0, prices, n, dp));
}

int solve_2(int n, vector<int> &prices)
{
    vector<vector<int>> dp(n + 2, vector<int>(2, 0));

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            if (buy == 1)
                dp[ind][buy] = max(-prices[ind] + dp[ind + 1][0], 0 + dp[ind + 1][1]);
            else
                dp[ind][buy] = max(prices[ind] + dp[ind + 2][1], 0 + dp[ind + 1][0]);
        }
    }
    return dp[0][1];
}

int maxProfit(vector<int> &prices)
{
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2, -1));
    return solve(0, 1, prices, n, dp);
}