// Palindrome Partitioning II (https://leetcode.com/problems/palindrome-partitioning-ii/)
// Partition DP

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isPalindrome(int i, int j, string &s)
{
    while (i < j)
    {
        if (s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}

int solve(int i, int n, string &s, vector<int> &dp)
{
    if (i == n)
        return 0;

    if (dp[i] != -1)
        return dp[i];

    int minCost = 1e9;
    for (int j = i; j < n; j++)
    {
        if (isPalindrome(i, j, s))
        {
            int cost = 1 + solve(j + 1, n, s, dp);
            minCost = min(minCost, cost);
        }
    }
    return dp[i] = minCost;
}

int solve_2(int n, string s)
{
    vector<int> dp(n + 1, 0);

    dp[n] = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int minCost = 1e9;
        for (int j = i; j < n; j++)
        {
            if (isPalindrome(i, j, s))
            {
                int cost = 1 + dp[j + 1];
                minCost = min(minCost, cost);
            }
        }
        dp[i] = minCost;
    }
    return dp[0] - 1;
}

int minCut(string s)
{
    int n = s.size();
    vector<int> dp(n, -1);
    return solve(0, n, s, dp) - 1;
}