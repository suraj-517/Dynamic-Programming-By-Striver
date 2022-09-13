// Best Time to Buy and Sell Stock III (https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)
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

int solve_2(int n, vector<int> &prices)
{
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            for (int cap = 1; cap < 3; cap++) // cap ko 0 se isiliye start nhi kiye kyuki (cap == 0) return 0;
            {
                if (buy == 1)
                    dp[ind][buy][cap] = max(-prices[ind] + dp[ind + 1][0][cap], 0 + dp[ind + 1][1][cap]);
                else
                    dp[ind][buy][cap] = max(prices[ind] + dp[ind + 1][1][cap - 1], 0 + dp[ind + 1][0][cap]);
            }
        }
    }

    return dp[0][1][2];
}


int solve_3(int n, vector<int> &prices)
{
    vector<vector<int>> after(2, vector<int>(3, 0)), cur(2, vector<int>(3, 0));

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            for (int cap = 1; cap < 3; cap++) // cap ko 0 se isiliye start nhi kiye kyuki (cap == 0) return 0;
            {
                if (buy == 1)
                    cur[buy][cap] = max(-prices[ind] + after[0][cap], 0 + after[1][cap]);
                else
                    cur[buy][cap] = max(prices[ind] + after[1][cap - 1], 0 + after[0][cap]);
            }
        }
        after = cur;
    }

    return after[1][2];
}

int maxProfit(vector<int> &prices)
{
    int n = prices.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1)));
    return solve(0, 1, 2, prices, n, dp);
}