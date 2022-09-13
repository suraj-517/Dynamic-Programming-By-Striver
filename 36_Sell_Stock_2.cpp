// Best Time to Buy and Sell Stock II (https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)
// DP on Stock

#include <iostream>
#include <vector>
using namespace std;

int solve(int ind, int buy, vector<int> &arr, int n, vector<vector<int>> &dp)
{
    if (ind == n)
        return 0;

    if (dp[ind][buy] != -1)
        return dp[ind][buy];

    int profit = 0;
    if (buy)
    {
        profit = max(-arr[ind] + solve(ind + 1, 0, arr, n, dp), 0 + solve(ind + 1, 1, arr, n, dp));
    }
    else
    {
        profit = max(arr[ind] + solve(ind + 1, 1, arr, n, dp), 0 + solve(ind + 1, 0, arr, n, dp));
    }
    return dp[ind][buy] = profit;
}

int solve_2(int n, vector<int> arr)
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
                profit = max(-arr[ind] + dp[ind+1][0], 0 + dp[ind + 1][1]);
            }
            else
            {
                profit = max(arr[ind] + dp[ind+1][1], 0 + dp[ind + 1][0]);
            }
            dp[ind][buy] = profit;
        }
    }
    return dp[0][1];
}


int solve_3(int n, vector<int> arr)
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
                profit = max(-arr[ind] + ahead[0], 0 + ahead[1]);
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


int maxProfit(vector<int> &prices)
{
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2, -1));
    return solve(0, 1, prices, n, dp);
}

/*
int mn = 1e9, maxpro = 0;
    for (int i = 0; i < prices.size(); i++)
    {
        mn = min(mn, prices[i]);
        if (mn < prices[i])
        {
            maxpro += (prices[i] - mn);
            mn = prices[i];
        }
    }
    return maxpro;
*/