// Print Longest Increasing Subsequence (https://leetcode.com/problems/longest-increasing-subsequence/)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Algorithmic Approach
// Let dp[i] is the longest increase subsequence of nums[0..i] which has nums[i] as the end element of the subsequence.
// T = O(N^2), S = O(N)
vector<int> solve_4(int n, vector<int> &arr)
{
    vector<int> dp(n, 1), hash(n);

    int maxi = 1;
    int lastIndex = 0; // last index of longest increasing subsequence
    for (int i = 0; i < n; i++)
    {
        hash[i] = i;
        for (int prev = 0; prev < i; prev++)
        {
            if (arr[i] > arr[prev] && dp[prev] + 1 > dp[i])
            {
                dp[i] = dp[prev] + 1;
                hash[i] = prev;
            }
        }
        if (dp[i] > maxi)
        {
            maxi = dp[i];
            lastIndex = i;
        }
    }

    // Print LIS
    vector<int> lis;
    lis.push_back(arr[lastIndex]);

    while (hash[lastIndex] != lastIndex)
    {
        lastIndex = hash[lastIndex];
        lis.push_back(arr[lastIndex]);
    }
    reverse(lis.begin(), lis.end());

    return lis;
}