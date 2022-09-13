// Largest Divisible Subset (https://leetcode.com/problems/largest-divisible-subset/)
// Based on LIS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solve(int n, vector<int> arr)
{
    sort(arr.begin(), arr.end());
    vector<int> dp(n, 1), hash(n);

    int maxi = 1;
    int lastIndex = 0;
    for (int i = 0; i < n; i++)
    {
        hash[i] = i;
        for (int prev = 0; prev < i; prev++)
        {
            if (arr[i] % arr[prev] == 0 && dp[prev] + 1 > dp[i])
            {
                dp[i] = dp[prev]+1;
                hash[i] = prev;
            }
        }
        if(dp[i] > maxi)
        {
            maxi = dp[i];
            lastIndex = i;
        }
    }

    // Print 
    vector<int> ans;
    ans.push_back(arr[lastIndex]);
    while(hash[lastIndex] != lastIndex)
    {
        lastIndex = hash[lastIndex];
        ans.push_back(arr[lastIndex]);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

vector<int> largestDivisibleSubset(vector<int> &nums)
{
    int n = nums.size();
    return solve(n, nums);
}