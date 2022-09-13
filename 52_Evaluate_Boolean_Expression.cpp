// Evaluate Boolean Expression to true (https://practice.geeksforgeeks.org/problems/boolean-parenthesization5610/1)
// Partition DP

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(int i, int j, int isTrue, string &s, vector<vector<vector<int>>> &dp)
{
    if (i > j)
        return 0;
    if (i == j)
    {
        if (isTrue)
            return s[i] == 'T';
        else
            return s[i] == 'F';
    }

    if (dp[i][j][isTrue] != -1)
        return dp[i][j][isTrue];

    int ways = 0;
    for (int k = i + 1; k <= j - 1; k += 2)
    {
        int lT = solve(i, k - 1, 1, s, dp);
        int lF = solve(i, k - 1, 0, s, dp);
        int rT = solve(k + 1, j, 1, s, dp);
        int rF = solve(k + 1, j, 0, s, dp);

        if (s[k] == '&')
        {
            if (isTrue)
                ways += lT * rT;
            else
                ways += lF * rT + lF * rF + lT * rF;
        }
        else if (s[k] == '|')
        {
            if (isTrue)
                ways += lT * rT + lT * rF + lF * rT;
            else
                ways += lF * rF;
        }
        else
        {
            if (isTrue)
                ways += lT * rF + lF * rT;
            else
                ways += lF * rF + lT * rT;
        }
    }
    return dp[i][j][isTrue] = ways % 1003;
}

int mod = 1003;

int solve_2(int n, string s)
{
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            if (i > j)
                continue;
            else if (i == j)
            {
                dp[i][j][0] = (s[i] == 'F');
                dp[i][j][1] = (s[i] == 'T');
            }
            else
            {
                for (int k = i + 1; k <= j - 1; k += 2)
                {
                    int lT = dp[i][k - 1][1];
                    int lF = dp[i][k - 1][0];
                    int rT = dp[k + 1][j][1];
                    int rF = dp[k + 1][j][0];

                    if (s[k] == '&')
                    {
                        (dp[i][j][1] += lT * rT)%= mod;

                        (dp[i][j][0] += lF * rT + lF * rF + lT * rF)%= mod;
                    }
                    else if (s[k] == '|')
                    {
                        (dp[i][j][1] += lT * rT + lT * rF + lF * rT)%= mod;
                        (dp[i][j][0] += lF * rF)%= mod;
                    }
                    else
                    {
                        (dp[i][j][1] += lT * rF + lF * rT)%= mod;
                        (dp[i][j][0] += lF * rF + lT * rT)%= mod;
                    }
                }
            }
        }
    }
    return dp[0][n-1][1];
}

int countWays(int n, string s)
{
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, -1)));
    return solve(0, n - 1, 1, s, dp);
}