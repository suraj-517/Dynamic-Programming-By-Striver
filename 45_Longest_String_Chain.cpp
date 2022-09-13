// Longest String Chain (https://leetcode.com/problems/longest-string-chain/)
// Based on LIS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool checkPossible(string &s1, string &s2)
{
    if (s1.size() != s2.size() + 1)
        return false;

    int first = 0, second = 0;
    while (first < s1.size())
    {
        if (s1[first] == s2[second])
        {
            first++;
            second++;
        }
        else
            first++;
    }

    if (first == s1.size() && second == s2.size())
        return true;
    else
        return false;
}

bool cmp(string &s1, string &s2)
{
    return s1.size() < s2.size();
}

int longestStrChain(vector<string> &words)
{
    sort(words.begin(), words.end(), cmp);

    int n = words.size();
    vector<int> dp(n, 1);

    int maxi = 1;
    for (int i = 0; i < n; i++)
    {
        for (int prev = 0; prev < i; prev++)
        {
            if (checkPossible(words[i], words[prev]) && dp[prev] + 1 > dp[i])
            {
                dp[i] = dp[prev]+1;
            }
        }
        maxi = max(maxi, dp[i]);
    }
    return maxi;
}