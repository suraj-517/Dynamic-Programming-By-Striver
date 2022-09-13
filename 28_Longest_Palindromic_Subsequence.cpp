// Longest Palindromic Subsequence (https://practice.geeksforgeeks.org/problems/longest-palindromic-subsequence-1612327878/1)
// DP on String
// similar to LCS question

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(int i, int j, string &s, string &t, vector<vector<int>> &dp) // T = O(N*M), S = O(N*M)(DP) + O(N+M)(Stack)
{
    if (i == 0 || j == 0) // After shifting index
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (s[i - 1] == t[j - 1])
        return dp[i][j] = 1 + solve(i - 1, j - 1, s, t, dp);
    else
        return dp[i][j] = 0 + max(solve(i - 1, j, s, t, dp), solve(i, j - 1, s, t, dp));
}

int solve_2(int n, int m, string s, string t)
{
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = 0;
    }
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = 0 + max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[n][m];
}

int solve_3(int n, int m, string s, string t)
{
    vector<int> prev(m + 1, 0), cur(m + 1, 0);
    for (int j = 0; j <= m; j++)
    {
        prev[j] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
                cur[j] = 1 + prev[j - 1];
            else
                cur[j] = 0 + max(prev[j], cur[j - 1]);
        }
        prev = cur;
    }

    return prev[m];
}

int longestPalinSubseq(string s)
{
    int n = s.size();
    string t = s;
    reverse(t.begin(), t.end());
    return solve_3(n, n, s, t);
}