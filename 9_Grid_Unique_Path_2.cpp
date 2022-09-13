// Unique Paths II (https://leetcode.com/problems/unique-paths-ii/)
// DP ON GRID (QUESTION)

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int solve(int i, int j, vector<vector<int>> &dp, vector<vector<int>> &grid)
{
    if (i >= 0 && j >= 0 && grid[i][j] == 1)
        return 0;
    if (i == 0 && j == 0)
        return 1;

    if (i < 0 || j < 0)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int up = solve(i - 1, j, dp, grid);
    int left = solve(i, j - 1, dp, grid);
    return dp[i][j] = up + left;
}

int solve_2(int m, int n, vector<vector<int>> &grid)
{
    int dp[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 1)
                dp[i][j] = 0;
            else if (i == 0 && j == 0)
                dp[i][j] = 1;
            else
            {
                int up = 0;
                int left = 0;
                if (i > 0)
                    up = dp[i - 1][j];
                if (j > 0)
                    left = dp[i][j - 1];

                dp[i][j] = up + left;
            }
        }
    }
    return dp[m - 1][n - 1];
}

int solve_3(int m, int n, vector<vector<int>> &grid) // space optimization
{
    vector<int> prev(n, 0);
    for (int i = 0; i < m; i++)
    {
        vector<int> cur(n, 0);
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 1)
                cur[j] = 0;
            else if (i == 0 && j == 0)
                cur[j] = 1;
            else
            {
                int up = 0;
                int left = 0;
                if (i > 0)
                    up = prev[j];
                if (j > 0)
                    left = cur[j - 1];

                cur[j] = up + left;
            }
        }
        prev = cur;
    }

    return prev[n - 1];
}

int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
{
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return solve(m-1, n-1, dp, obstacleGrid);
}