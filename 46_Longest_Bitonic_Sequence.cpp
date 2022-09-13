// Longest Bitonic Sequence (https://www.codingninjas.com/codestudio/problems/longest-bitonic-sequence_1062688)
// Based on LIS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(int n, vector<int> &arr)
{
    vector<int> dp1(n, 1), dp2(n, 2);

    // Forward direction(increasing)
    for (int i = 0; i < n; i++)
    {
        for (int prev = 0; prev < i; prev++)
        {
            if (arr[i] > arr[prev] && dp1[prev] + 1 > dp1[i])
            {
                dp1[i] = dp1[prev] + 1;
            }
        }
    }

    // Backward direction (decresing)
    for (int i = n - 1; i >= 0; i--)
    {
        for (int prev = n - 1; prev > i; prev--)
        {
            if (arr[i] > arr[prev] && dp2[prev] + 1 > dp2[i])
            {
                dp2[i] = dp2[prev] + 1;
            }
        }
    }

    int maxi = 1;
    for (int i = 0; i < n; i++)
    {
        maxi = max(maxi, dp1[i] + dp2[i] - 1);
    }
    return maxi;
}

int longestBitonicSequence(vector<int> &arr, int n)
{
    return solve(n, arr);
}