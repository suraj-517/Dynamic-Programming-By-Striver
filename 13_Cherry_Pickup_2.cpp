// Cherry Pickup 2 (https://leetcode.com/problems/cherry-pickup-ii/)
// DP ON GRID (QUESTION)

#include <iostream>
#include <vector>
using namespace std;

int solve(int i, int j1, int j2, int r, int c, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp) // T = O(M*N*N)*9,   S = O(M*N*N)(DP) + O(N)(stack)
{
    if (j1 < 0 || j2 < 0 || j1 >= c || j2 >= c)
        return -1e8;
    if (i == r - 1)
    {
        if (j1 == j2)
            return grid[i][j1];
        else
            return grid[i][j1] + grid[i][j2];
    }

    if (dp[i][j1][j2] != -1)
        return dp[i][j1][j2];

    // explore all paths of alice and bob simultaneously
    int maxi = -1e8;
    for (int dj1 = -1; dj1 <= +1; dj1++)
    {
        for (int dj2 = -1; dj2 <= +1; dj2++)
        {
            int value = 0;
            if (j1 == j2)
                value = grid[i][j1];
            else
                value = grid[i][j1] + grid[i][j2];

            value += solve(i + 1, j1 + dj1, j2 + dj2, r, c, grid, dp);
            maxi = max(maxi, value);
        }
    }
    return dp[i][j1][j2] = maxi;
}

int solve_2(int m, int n, vector<vector<int>> &grid)    // T = O(M*N*N)*9,   S = O(M*N*N)(DP) 
{
    int dp[m][n][n];
    for (int j1 = 0; j1 < n; j1++)
    {
        for (int j2 = 0; j2 < n; j2++)
        {
            if (j1 == j2)
                dp[m - 1][j1][j2] = grid[m - 1][j1];
            else
                dp[m - 1][j1][j2] = grid[m - 1][j1] + grid[m - 1][j2];
        }
    }

    for (int i = m - 2; i >= 0; i--)
    {
        for (int j1 = 0; j1 < n; j1++)
        {
            for (int j2 = 0; j2 < n; j2++)
            {
                int maxi = -1e8;
                for (int dj1 = -1; dj1 <= +1; dj1++)
                {
                    for (int dj2 = -1; dj2 <= +1; dj2++)
                    {
                        int value = 0;
                        if (j1 == j2)
                            value = grid[i][j1];
                        else
                            value = grid[i][j1] + grid[i][j2];

                        if (j1 + dj1 >= 0 && j1 + dj1 < n && j2 + dj2 >= 0 && j2 + dj2 < n)
                            value += dp[i + 1][j1 + dj1][j2 + dj2];
                        else
                            value += -1e8;

                        maxi = max(maxi, value);
                    }
                }
                dp[i][j1][j2] = maxi;
            }
        }
    }
    return dp[0][0][m - 1];
}

int solve_3(int m, int n, vector<vector<int>> &grid)    // T = O(M*N*N)*9,   S = O(N*N)
{
    vector<vector<int>> front(n, vector<int>(n, 0)), cur(n, vector<int>(n, 0));

    for (int j1 = 0; j1 < n; j1++)
    {
        for (int j2 = 0; j2 < n; j2++)
        {
            if (j1 == j2)
                front[j1][j2] = grid[m - 1][j1];
            else
                front[j1][j2] = grid[m - 1][j1] + grid[m - 1][j2];
        }
    }

    for (int i = m - 2; i >= 0; i--)
    {
        for (int j1 = 0; j1 < n; j1++)
        {
            for (int j2 = 0; j2 < n; j2++)
            {
                int maxi = -1e8;
                for (int dj1 = -1; dj1 <= +1; dj1++)
                {
                    for (int dj2 = -1; dj2 <= +1; dj2++)
                    {
                        int value = 0;
                        if (j1 == j2)
                            value = grid[i][j1];
                        else
                            value = grid[i][j1] + grid[i][j2];

                        if (j1 + dj1 >= 0 && j1 + dj1 < n && j2 + dj2 >= 0 && j2 + dj2 < n)
                            value += front[j1 + dj1][j2 + dj2];
                        else
                            value += -1e8;

                        maxi = max(maxi, value);
                    }
                }
                cur[j1][j2] = maxi;
            }
        }
        front = cur;
    }
    return front[0][m - 1];
}

int cherryPickup(vector<vector<int>> &grid)
{
    int m = grid.size(), n = grid[0].size();
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(n, -1)));
    return solve(0, 0, n - 1, m, n, grid, dp);
}