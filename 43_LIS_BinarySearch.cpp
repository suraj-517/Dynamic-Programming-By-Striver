// Longest Increasing Subsequence using Binary Search (https://leetcode.com/problems/longest-increasing-subsequence/)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Time: O(N * logN), where N <= 2500 is the number of elements in array nums.
// Space: O(N), we can achieve O(1) in space by overwriting values of sub into original nums array.

int lengthOfLIS(vector<int> &arr)
{
    int n = arr.size();
    vector<int> ans;
    ans.push_back(arr[0]);
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > ans.back())
        {
            ans.push_back(arr[i]);
        }
        else
        {
            int ind = lower_bound(ans.begin(), ans.end(), arr[i]) - ans.begin();
            ans[ind] = arr[i];
        }
    }
    return ans.size();
}