// Grid Minimum Falling Path Sum (https://leetcode.com/problems/minimum-falling-path-sum/)
// Dream 11 interview
// DP ON GRID (QUESTION)

#include <iostream>
#include <vector>
using namespace std;

int solve(int i, int j, int n, vector<vector<int>> &grid, vector<vector<int>> &dp)
{

    if (j < 0 || j >= n)
        return 1e9;

    if (i == 0)
        return grid[i][j];

    if (dp[i][j] != -1)
        return dp[i][j];

    int left = grid[i][j] + solve(i - 1, j - 1, n, grid, dp);
    int straight = grid[i][j] + solve(i - 1, j, n, grid, dp);
    int right = grid[i][j] + solve(i - 1, j + 1, n, grid, dp);

    return dp[i][j] = min(straight, min(left, right));
}

int solve_2(int m, int n, vector<vector<int>> &grid)
{
    int dp[m][n];
    for (int j = 0; j < n; j++)
    {
        dp[0][j] = grid[0][j];
    }

    for (int i = 1; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int u = grid[i][j] + dp[i - 1][j]; // upper straight
            int ld = grid[i][j];               // left diagonal
            int rd = grid[i][j];               // right diagonal
            if (j - 1 >= 0)
                ld += dp[i - 1][j - 1];
            else
                ld += 1e9;
            if (j + 1 < n)
                rd += dp[i - 1][j + 1];
            else
                rd += 1e9;

            dp[i][j] = min(u, min(ld, rd));
        }
    }

    int mn = 1e9;
    for (int j = 0; j < n; j++)
    {
        mn = min(mn, dp[m - 1][j]);
    }
    return mn;
}

int solve_3(int m, int n, vector<vector<int>> &grid)
{
    vector<int> prev(n, 0), cur(n, 0);
    for (int j = 0; j < n; j++)
    {
        prev[j] = grid[0][j];
    }

    for (int i = 1; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int u = grid[i][j] + prev[j]; // upper straight
            int ld = grid[i][j];          // left diagonal
            int rd = grid[i][j];          // right diagonal
            if (j - 1 >= 0)
                ld += prev[j - 1];
            else
                ld += 1e9;
            if (j + 1 < n)
                rd += prev[j + 1];
            else
                rd += 1e9;

            cur[j] = min(u, min(ld, rd));
        }
        prev = cur;
    }

    int mn = 1e9;
    for (int j = 0; j < n; j++)
    {
        mn = min(mn, prev[j]);
    }
    return mn;
}

int minFallingPathSum(vector<vector<int>> &grid)
{
    int m = grid.size(), n = grid[0].size();
    int ans = 1e9;
    for (int j = 0; j < n; j++)
    {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        int temp = solve(m - 1, j, n, grid, dp);
        ans = min(ans, temp);
    }
    return ans;
}