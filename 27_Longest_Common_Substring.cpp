// Longest Common Substring (https://practice.geeksforgeeks.org/problems/longest-common-substring1452/1)
// DP on String

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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

    int ans = -1e8;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = 0;

            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}


int solve_3(int n, int m, string s, string t)
{
    vector<int> prev(m+1, 0), cur(m+1, 0);

    int ans = -1e8;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
                cur[j] = 1 + prev[j - 1];
            else
                cur[j] = 0;

            ans = max(ans, cur[j]);
        }
        prev = cur;
    }
    return ans;
}

int longestCommonSubstr(string S1, string S2, int n, int m)
{
    return solve_2(n, m, S1, S2);
}