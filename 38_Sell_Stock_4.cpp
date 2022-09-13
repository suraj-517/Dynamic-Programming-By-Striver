// Best Time to Buy and Sell Stock IV (https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/)
// DP on Stock

#include <iostream>
#include <vector>
using namespace std;

int solve(int ind, int buy, int cap, vector<int> &prices, int n, vector<vector<vector<int>>> &dp)
{
    if (ind == n || cap == 0)
        return 0;

    if (dp[ind][buy][cap] != -1)
        return dp[ind][buy][cap];

    if (buy == 1)
        return dp[ind][buy][cap] = max(-prices[ind] + solve(ind + 1, 0, cap, prices, n, dp), 0 + solve(ind + 1, 1, cap, prices, n, dp));
    else
        return dp[ind][buy][cap] = max(prices[ind] + solve(ind + 1, 1, cap - 1, prices, n, dp), 0 + solve(ind + 1, 0, cap, prices, n, dp));
}

int solve_2(int n, vector<int> &prices, int k)
{
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            for (int cap = 1; cap <= k; cap++) // cap ko 0 se isiliye start nhi kiye kyuki (cap == 0) return 0;
            {
                if (buy == 1)
                    dp[ind][buy][cap] = max(-prices[ind] + dp[ind + 1][0][cap], 0 + dp[ind + 1][1][cap]);
                else
                    dp[ind][buy][cap] = max(prices[ind] + dp[ind + 1][1][cap - 1], 0 + dp[ind + 1][0][cap]);
            }
        }
    }

    return dp[0][1][k];
}

int solve_3(int n, vector<int> &prices, int k)
{
    vector<vector<int>> after(2, vector<int>(k + 1, 0)), cur(2, vector<int>(k + 1, 0));

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            for (int cap = 1; cap <= k; cap++) // cap ko 0 se isiliye start nhi kiye kyuki (cap == 0) return 0;
            {
                if (buy == 1)
                    cur[buy][cap] = max(-prices[ind] + after[0][cap], 0 + after[1][cap]);
                else
                    cur[buy][cap] = max(prices[ind] + after[1][cap - 1], 0 + after[0][cap]);
            }
        }
        after = cur;
    }

    return after[1][k];
}

// other method
int solve_4(int ind, int tranNo, vector<int> &prices, int n, int k, vector<vector<int>> &dp)
{
    if (ind == n || tranNo == 2 * k)
        return 0;

    if (dp[ind][tranNo] != -1)
        return dp[ind][tranNo];

    if (tranNo % 2 == 0)
        return dp[ind][tranNo] = max(-prices[ind] + solve_4(ind + 1, tranNo + 1, prices, n, k, dp), 0 + solve_4(ind + 1, tranNo, prices, n, k, dp));
    else
        return dp[ind][tranNo] = max(prices[ind] + solve_4(ind + 1, tranNo + 1, prices, n, k, dp), 0 + solve_4(ind + 1, tranNo, prices, n, k, dp));
}

int solve_5(int n, int k, vector<int> &prices)
{
    vector<vector<int>> dp(n + 1, vector<int>(2 * k + 1, 0));

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int tranNo = 2 * k - 1; tranNo >= 0; tranNo--)
        {

            if (tranNo % 2 == 0)
                dp[ind][tranNo] = max(-prices[ind] + dp[ind + 1][tranNo + 1], 0 + dp[ind + 1][tranNo]);
            else
                dp[ind][tranNo] = max(prices[ind] + dp[ind + 1][tranNo + 1], 0 + dp[ind + 1][tranNo]);
        }
    }
    return dp[0][0];
}

int solve_6(int n, int k, vector<int> &prices)
{
    vector<int> after(2*k+1, 0), cur(2*k+1, 0);

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int tranNo = 2 * k - 1; tranNo >= 0; tranNo--)
        {

            if (tranNo % 2 == 0)
                cur[tranNo] = max(-prices[ind] + after[tranNo + 1], 0 + after[tranNo]);
            else
                cur[tranNo] = max(prices[ind] + after[tranNo + 1], 0 + after[tranNo]);
        }
        after = cur;
    }
    return after[0];
}

/*
int maxProfit(int k, vector<int> &prices)
{
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2*k, -1));
    return solve_4(0, 0, prices, n, k, dp);
}
*/

int maxProfit(int k, vector<int> &prices)
{
    int n = prices.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
    return solve(0, 1, k, prices, n, dp);
}