// Edit Distance (https://leetcode.com/problems/edit-distance/)
// DP on String
// String Matching

#include <iostream>
#include <vector>
using namespace std;

/*
    After shifting index
     // return no. of insertion
    if (i == 0)
        return j;
    // return no. of deletion
    if (j == 0)
        return i;
*/

int solve(int i, int j, string &s, string &t, vector<vector<int>> &dp)
{ // return no. of insertion
    if (i < 0)
        return j + 1;
    // return no. of deletion
    if (j < 0)
        return i + 1;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (s[i] == t[j])
    {
        return dp[i][j] = 0 + solve(i - 1, j - 1, s, t, dp);
    }
    else // s[i] != t[j]
    {
        int insert = 1 + solve(i, j - 1, s, t, dp);
        int remove = 1 + solve(i - 1, j, s, t, dp);
        int update = 1 + solve(i - 1, j - 1, s, t, dp);
        return dp[i][j] = min(insert, min(remove, update));
    }
}

int solve_2(int n, int m, string s, string t)
{
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int j = 0; j <= m; j++)
        dp[0][j] = j;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                dp[i][j] = 0 + dp[i - 1][j - 1];
            }
            else // s[i] != t[j]
            {
                int insert = 1 + dp[i][j - 1];
                int remove = 1 + dp[i - 1][j];
                int update = 1 + dp[i - 1][j - 1];
                dp[i][j] = min(insert, min(remove, update));
            }
        }
    }
    return dp[n][m];
}

int solve_3(int n, int m, string s, string t)   // we don't optimise to only  1 array
{
    vector<int> prev(m + 1, 0), cur(m + 1, 0);
    for (int j = 0; j <= m; j++)
        prev[j] = j;

    for (int i = 1; i <= n; i++)
    {
        cur[0] = i; // here edge something
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                cur[j] = 0 + prev[j - 1];
            }
            else // s[i] != t[j]
            {
                int insert = 1 + cur[j - 1];
                int remove = 1 + prev[j];
                int update = 1 + prev[j - 1];
                cur[j] = min(insert, min(remove, update));
            }
        }
        prev = cur;
    }
    return prev[m];
}

int minDistance(string s, string t)
{
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solve(n - 1, m - 1, s, t, dp);
}