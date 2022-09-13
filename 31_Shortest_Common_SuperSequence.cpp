// Shortest Common SuperSequence (https://leetcode.com/problems/shortest-common-supersequence/submissions/)
// DP on String
// ans = m + n - LCS

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

string solve_2(int n, int m, string s, string t)
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

    // Print SCS
    string ans;
    int i = n, j = m;
    while (i > 0 && j > 0)
    {
        if (s[i - 1] == t[j - 1])
        {
            ans.push_back(s[i - 1]);
            i--, j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) // move up
        {
            ans.push_back(s[i - 1]);
            i--;
        }
        else // move left
        {
            ans.push_back(t[j - 1]);
            j--;
        }
    }
    while (i > 0)
    {
        ans.push_back(s[i - 1]);
        i--;
    }
    while (j > 0)
    {
        ans.push_back(t[j - 1]);
        j--;
    }
    reverse(ans.begin(), ans.end());

    return ans;
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

int shortestCommonSupersequenceLength(string s, string t)
{
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    int lcs = solve(n, m, s, t, dp);
    return (m + n - lcs);
}


string shortestCommonSupersequence(string s, string t)
{
    int n = s.size(), m = t.size();
    return solve_2(n, m, s, t);
}