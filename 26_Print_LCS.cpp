// Print Longest Common Subsequence (https://leetcode.com/problems/longest-common-subsequence/)
// DP on String

/*
    * DP on String
        -> Comparison
        -> Replace / Edit
    * Generate all subsequence and compare on way in general way
*/

#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;



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

    // Print LCS
    int i = n, j = m;
    string ans;
    while (i > 0 && j > 0)
    {
        if (s[i - 1] == t[j - 1])
        {
            ans.push_back(s[i - 1]);
            i--, j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

string PrintlongestCommonSubsequence(string s, string t)
{
    int n = s.size(), m = t.size();
    return solve_2(n, m, s, t);
}