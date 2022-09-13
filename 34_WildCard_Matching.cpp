// Wildcard Matching (https://leetcode.com/problems/wildcard-matching/)
// DP on String
// String Matching
// All possible ways -> Recursion

#include <iostream>
#include <vector>
using namespace std;

/*
    After shifting index
    // Base Cases
    if (i == 0 && j == 0)
        return true;
    if (i == 0 && j > 0)
        return false;
    if (j == 0 && i > 0)
    {
        for (int k = 1; k <= i; k++)
        {
            if (p[k-1] != '*')
                return false;
        }
        return true;
    }
*/

bool solve(int i, int j, string p, string s, vector<vector<int>> &dp)
{
    // Base Cases
    if (i < 0 && j < 0)
        return true;
    if (i < 0 && j >= 0)
        return false;
    if (j < 0 && i >= 0)
    {
        for (int k = 0; k <= i; k++)
        {
            if (p[k] != '*')
                return false;
        }
        return true;
    }

    if (dp[i][j] != -1)
        return dp[i][j];

    if (p[i] == s[j] || p[i] == '?')
        return dp[i][j] = solve(i - 1, j - 1, p, s, dp);
    else if (p[i] == '*')
        return dp[i][j] = solve(i - 1, j, p, s, dp) | solve(i, j - 1, p, s, dp);
    else
        return dp[i][j] = false;
}

bool solve_2(int n, int m, string p, string s)
{
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;
    for (int j = 1; j <= m; j++)
        dp[0][j] = false;
    for (int i = 1; i <= n; i++)
    {
        bool flag = true;
        for (int k = 1; k <= i; k++)
        {
            if (p[k - 1] != '*')
            {
                flag = false;
                break;
            }
        }

        dp[i][0] = flag;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (p[i - 1] == s[j - 1] || p[i - 1] == '?')
                dp[i][j] = dp[i - 1][j - 1];
            else if (p[i - 1] == '*')
                dp[i][j] = dp[i - 1][j] | dp[i][j - 1];
            else
                dp[i][j] = false;
        }
    }
    return dp[n][m];
}

bool solve_2(int n, int m, string p, string s)
{
    vector<bool> prev(m + 1, false), cur(m + 1, false);
    prev[0] = true;
    for (int j = 1; j <= m; j++)
        prev[j] = false;

    for (int i = 1; i <= n; i++)
    {
        bool flag = true;
        for (int k = 1; k <= i; k++)
        {
            if (p[k - 1] != '*')
            {
                flag = false;
                break;
            }
        }
        // for every row you are assigning the 0th column's value
        cur[0] = flag;

        for (int j = 1; j <= m; j++)
        {
            if (p[i - 1] == s[j - 1] || p[i - 1] == '?')
                cur[j] = prev[j - 1];
            else if (p[i - 1] == '*')
                cur[j] = prev[j] | cur[j - 1];
            else
                cur[j] = false;
        }
        prev = cur;
    }
    return prev[m];
}

bool isMatch(string s, string p)
{
    int n = p.size(), m = s.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solve(n - 1, m - 1, p, s, dp);
}