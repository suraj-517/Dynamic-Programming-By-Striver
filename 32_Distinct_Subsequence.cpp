// Distinct Subsequences (https://leetcode.com/problems/distinct-subsequences/)
// DP on String
// String Matching

#include <iostream>
#include <vector>
using namespace std;

int solve(int i, int j, string s, string t, vector<vector<int>> &dp) // T = O(N*M) , S = O(N*M) + O(N+M)
{
    if (j == 0) // after shifting index
        return 1;
    if (i == 0)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (s[i - 1] == t[j - 1])
        return dp[i][j] = solve(i - 1, j - 1, s, t, dp) + solve(i - 1, j, s, t, dp);
    else // s[i] != t[j]
        return dp[i][j] = solve(i - 1, j, s, t, dp);
}

int solve_2(int n, int m, string s, string t)
{
    vector<vector<double>> dp(n + 1, vector<double>(m + 1, 0)); // double due to overflow
    for (int i = 0; i <= n; i++)
        dp[i][0] = 1;
    for (int j = 1; j <= m; j++)
        dp[0][j] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return (int)dp[n][m];
}

int solve_3(int n, int m, string s, string t)
{
    vector<double> prev(m + 1, 0), cur(m + 1, 0);
    prev[0] = cur[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                cur[j] = prev[j - 1] + prev[j];
            }
            else
            {
                cur[j] = prev[j];
            }
        }
        prev = cur;
    }
    return (int)prev[m];
}

int numDistinct(string s, string t)
{
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return solve(n, m, s, t, dp);
}