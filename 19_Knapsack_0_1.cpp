// 0 - 1 Knapsack Problem (https://practice.geeksforgeeks.org/problems/0-1-knapsack-problem0945/1)
// DP ON SUBSEQUENCE / SUBSETS / TARGET

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int solve(int ind, int W, int wt[], int val[], vector<vector<int>> &dp)
{
    if (ind == 0)
    {
        if (wt[0] <= W)
            return val[0];
        else
            return 0;
    }

    if (dp[ind][W] != -1)
        return dp[ind][W];

    int notTake = 0 + solve(ind - 1, W, wt, val, dp);
    int take = INT_MIN;
    if (wt[ind] <= W)
    {
        take = val[ind] + solve(ind - 1, W - wt[ind], wt, val, dp);
    }
    return dp[ind][W] = max(notTake, take);
}


int solve_2(int n, int W, int wt[], int val[])
{
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));

    for (int j = 0; j <= W; j++)
    {
        if (j >= wt[0])
            dp[0][j] = val[0];
        else
            dp[0][j] = 0;
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            int notTake = 0 + dp[i - 1][j];
            int take = INT_MIN;
            if (wt[i] <= j)
            {
                take = val[i] + dp[i - 1][j - wt[i]];
            }
            dp[i][j] = max(notTake, take);
        }
    }

    return dp[n-1][W];
}

int solve_3(int n, int W, int wt[], int val[])
{
    vector<int> prev(W+1, 0), cur(W+1, 0);

    for (int j = 0; j <= W; j++)
    {
        if (j >= wt[0])
            prev[j] = val[0];
        else
            prev[j] = 0;
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            int notTake = 0 + prev[j];
            int take = INT_MIN;
            if (wt[i] <= j)
            {
                take = val[i] + prev[j - wt[i]];
            }
            cur[j] = max(notTake, take);
        }
        prev = cur;
    }

    return prev[W];
}


int knapSack(int W, int wt[], int val[], int n)
{
    vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    return solve(n - 1, W, wt, val, dp);
}