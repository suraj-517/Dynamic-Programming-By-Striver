// Buy and sell stock with transaction fee (https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)
// DP on Stock
// It is similar to stock_2 , only substract fee.

#include <iostream>
#include <vector>
using namespace std;

int solve(int ind, int buy, vector<int> &arr, int n, vector<vector<int>> &dp, int fees)
{
    if (ind == n)
        return 0;

    if (dp[ind][buy] != -1)
        return dp[ind][buy];

    int profit = 0;
    if (buy)
    {
        profit = max(-arr[ind] - fees + solve(ind + 1, 0, arr, n, dp, fees), 0 + solve(ind + 1, 1, arr, n, dp, fees));
    }
    else
    {
        profit = max(arr[ind] + solve(ind + 1, 1, arr, n, dp, fees), 0 + solve(ind + 1, 0, arr, n, dp, fees));
    }
    return dp[ind][buy] = profit;
}

int solve_2(int n, vector<int> arr, int fee)
{
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    dp[n][0] = dp[n][1] = 0;

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            int profit = 0;
            if (buy)
            {
                profit = max(-arr[ind] - fee + dp[ind + 1][0], 0 + dp[ind + 1][1]);
            }
            else
            {
                profit = max(arr[ind] + dp[ind + 1][1], 0 + dp[ind + 1][0]);
            }
            dp[ind][buy] = profit;
        }
    }
    return dp[0][1];
}

int solve_3(int n, vector<int> arr, int fee)
{
    vector<int> ahead(2, 0), cur(2, 0);
    ahead[0] = ahead[1] = 0;

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            int profit = 0;
            if (buy)
            {
                profit = max(-arr[ind] - fee + ahead[0], 0 + ahead[1]);
            }
            else
            {
                profit = max(arr[ind] + ahead[1], 0 + ahead[0]);
            }
            cur[buy] = profit;
        }
        ahead = cur;
    }
    return ahead[1];
}

int maxProfit(vector<int> &prices, int fee)
{
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2, -1));
    return solve(0, 1, prices, n, dp, fee);
}