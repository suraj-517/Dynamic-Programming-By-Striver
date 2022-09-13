// Minimum Cost to Cut a Stick (https://leetcode.com/problems/minimum-cost-to-cut-a-stick/)
// Partition DP

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    T = O(C*C*C)  = O(C^3)
    S = O(C^2) + O(C)
*/
int solve(int i, int j, vector<int> &cuts, vector<vector<int>> &dp)
{
    if (i > j)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int mini = 1e9;
    for (int k = i; k <= j; k++)
    {
        int cost = cuts[j + 1] - cuts[i - 1] + solve(i, k - 1, cuts, dp) + solve(k + 1, j, cuts, dp);
        mini = min(mini, cost);
    }
    return dp[i][j] = mini;
}

int solve_2(int c, vector<int> &cuts)
{
    vector<vector<int>> dp(c + 2, vector<int>(c + 2, 0));

    for (int i = c; i >= 1; i--)
    {
        for (int j = 1; j <= c; j++)
        {
            if (i > j)
                continue;

            int mini = 1e9;
            for (int k = i; k <= j; k++)
            {
                int cost = cuts[j + 1] - cuts[i - 1] + dp[i][k-1] + dp[k+1][j];
                mini = min(mini, cost);
            }
            dp[i][j] = mini;
        }
    }
    return dp[1][c];
}

int minCost(int n, vector<int> &cuts)
{
    int c = cuts.size();
    vector<vector<int>> dp(c + 1, vector<int>(c + 1, -1));
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    return solve(1, c, cuts, dp);
}