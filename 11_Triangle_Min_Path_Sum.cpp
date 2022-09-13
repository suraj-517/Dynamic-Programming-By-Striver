// Triangle Minium Path Sum (https://leetcode.com/problems/triangle/)
// DP ON GRID (QUESTION)

#include <iostream>
#include <vector>
using namespace std;

int solve(int i, int j, int n, vector<vector<int>> &triangle, vector<vector<int>> &dp)
{
    if (i == n - 1)
        return triangle[i][j];

    if (dp[i][j] != -1)
        return dp[i][j];

    int d = triangle[i][j] + solve(i + 1, j, n, triangle, dp);      // down path
    int dg = triangle[i][j] + solve(i + 1, j + 1, n, triangle, dp); // diagonal path
    return dp[i][j] = min(d, dg);
}

int solve_2(int n, vector<vector<int>> &triangle)
{
    int dp[n][n];
    for (int j = 0; j < n; j++)
    {
        dp[n - 1][j] = triangle[n - 1][j];
    }

    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = i; j >= 0; j--)
        {
            if (i == n - 1)
                dp[i][j] = triangle[i][j];
            else
            {
                int d = triangle[i][j] + dp[i + 1][j];      // down path
                int dg = triangle[i][j] + dp[i + 1][j + 1]; // diagonal path
                dp[i][j] = min(d, dg);
            }
        }
    }

    return dp[0][0];
}


int solve_3(int n, vector<vector<int>> &triangle)
{
    vector<int> front(n, 0), cur(n, 0);
    for(int j = 0; j < n; j++)
    {
        front[j] = triangle[n-1][j];
    }

    for(int i = n-2; i >= 0; i--)
    {
        for(int j = i; j >= 0; j--)
        {
            int d = triangle[i][j] + front[j];
            int dg = triangle[i][j] + front[j+1];
            cur[j] = min(d, dg);
        }
        front = cur;
    }
    return front[0];
}

int minimumTotal(vector<vector<int>> &triangle)
{
    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return solve(0, 0, n, triangle, dp);
}