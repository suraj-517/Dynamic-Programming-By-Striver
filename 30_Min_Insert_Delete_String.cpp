// Minium Insertion / Deletion to convert string-1 to string-2 (https://practice.geeksforgeeks.org/problems/minimum-number-of-deletions-and-insertions0209/1)
// DP on String
// Based on LCS question
// ans = (n - LCS) + (m - LCS)

#include <iostream>
#include <vector>
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

int minOperations(string s, string t)
{

    int n = s.size(), m = t.size();
    int lcs = solve_3(n, m, s, t);
    return (n + m - 2 * lcs);
}
