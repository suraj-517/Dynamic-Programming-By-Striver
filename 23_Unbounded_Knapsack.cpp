// Knapsack with Duplicate Item (https://practice.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1)
// DP ON SUBSEQUENCE / SUBSETS / TARGET
// Similar to 20. Minium no. of coins

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int solve(int ind, int W, int wt[], int val[], vector<vector<int>> &dp)
{
    if (ind == 0)
    {
        return (W / wt[0]) * val[0];
    }

    if (dp[ind][W] != -1)
        return dp[ind][W];

    int notTake = 0 + solve(ind - 1, W, wt, val, dp);
    int take = INT_MIN;
    if (W >= wt[ind])
    {
        take = val[ind] + solve(ind, W - wt[ind], wt, val, dp);
    }

    return dp[ind][W] = max(notTake, take);
}

int solve_2(int n, int W, int wt[], int val[])
{
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));
    for (int j = 0; j <= W; j++)
    {
        dp[0][j] = (j / wt[0]) * val[0];
    }

    for (int ind = 1; ind < n; ind++)
    {
        for (int j = 0; j <= W; j++)
        {
            int notTake = 0 + dp[ind - 1][j];
            int take = INT_MIN;
            if (j >= wt[ind])
            {
                take = val[ind] + dp[ind][j - wt[ind]];
            }

            dp[ind][j] = max(notTake, take);
        }
    }
    return dp[n - 1][W];
}

int solve_3(int n, int W, int wt[], int val[])
{
    vector<int> prev(W + 1, 0), cur(W + 1, 0);
    for (int j = 0; j <= W; j++)
    {
        prev[j] = (j / wt[0]) * val[0];
    }

    for (int ind = 1; ind < n; ind++)
    {
        for (int j = 0; j <= W; j++)
        {
            int notTake = 0 + prev[j];
            int take = INT_MIN;
            if (j >= wt[ind])
            {
                take = val[ind] + cur[j - wt[ind]];
            }

            cur[j] = max(notTake, take);
        }
        prev = cur;
    }
    return prev[W];
}


int solve_4(int n, int W, int wt[], int val[])
{
    vector<int> prev(W + 1, 0);
    for (int j = 0; j <= W; j++)
    {
        prev[j] = (j / wt[0]) * val[0];
    }

    for (int ind = 1; ind < n; ind++)
    {
        for (int j = 0; j <= W; j++)
        {
            int notTake = 0 + prev[j];
            int take = INT_MIN;
            if (j >= wt[ind])
            {
                take = val[ind] + prev[j - wt[ind]];
            }

            prev[j] = max(notTake, take);
        }
    }
    return prev[W];
}

int knapSack(int n, int W, int val[], int wt[])
{
    vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    return solve(n - 1, W, wt, val, dp);
}