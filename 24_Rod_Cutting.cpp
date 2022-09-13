// Rod Cutting (https://practice.geeksforgeeks.org/problems/rod-cutting0840/1)
// DP ON SUBSEQUENCE / SUBSETS / TARGET
// Similar to Unbounded Knapsack

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int solve(int ind, int L, int price[], vector<vector<int>> &dp)
{
    if (ind == 0)
    {
        return L * price[0];
    }

    if (dp[ind][L] != -1)
        return dp[ind][L];

    int notTake = 0 + solve(ind - 1, L, price, dp);
    int take = INT_MIN;
    int rodLength = ind + 1;
    if (L >= rodLength)
    {
        take = price[ind] + solve(ind, L - rodLength, price, dp);
    }

    return dp[ind][L] = max(notTake, take);
}

int solve_2(int n, int price[])
{
    vector<vector<int>> dp(n, vector<int>(n + 1, 0));
    for (int L = 0; L <= n; L++)
    {
        dp[0][L] = L * price[0];
    }

    for (int ind = 1; ind < n; ind++)
    {
        for (int L = 0; L <= n; L++)
        {
            int notTake = 0 + dp[ind - 1][L];
            int take = INT_MIN;
            int rodLength = ind + 1;
            if (L >= rodLength)
            {
                take = price[ind] + dp[ind][L - rodLength];
            }

            dp[ind][L] = max(notTake, take);
        }
    }
    return dp[n - 1][n];
}

int solve_3(int n, int price[])
{
    vector<int> prev(n + 1, 0), cur(n + 1, 0);
    for (int L = 0; L <= n; L++)
    {
        prev[L] = L * price[0];
    }

    for (int ind = 1; ind < n; ind++)
    {
        for (int L = 0; L <= n; L++)
        {
            int notTake = 0 + prev[L];
            int take = INT_MIN;
            int rodLength = ind + 1;
            if (L >= rodLength)
            {
                take = price[ind] + cur[L - rodLength];
            }

            cur[L] = max(notTake, take);
        }
        prev = cur;
    }
    return prev[n];
}

int cutRod(int price[], int n)
{
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    return solve(n - 1, n, price, dp);
}