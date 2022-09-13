// Partition Array for Maximum Sum (https://leetcode.com/problems/partition-array-for-maximum-sum/)
// Partition DP

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// f(0) -> give me the maxium sum if we have the array from 0
/*
    T = O(N*K)
    S = O(N) + O(N)
*/
int solve(int i, int k, int n, vector<int> &arr, vector<int> &dp)
{
    if (i == n)
        return 0;

    if (dp[i] != -1)
        return dp[i];

    int len = 0, maxi = -1e9, maxAns = -1e9;
    for (int j = i; j < min(n, i + k); j++)
    {
        len++;
        maxi = max(maxi, arr[j]);
        int sum = len * maxi + solve(j + 1, k, n, arr, dp);
        maxAns = max(maxAns, sum);
    }
    return dp[i] = maxAns;
}

int solve_2(int n, int k, vector<int> &arr)
{
    vector<int> dp(n + 1, 0);

    for (int i = n - 1; i >= 0; i--)
    {
        int len = 0, maxi = -1e9, maxAns = -1e9;
        for (int j = i; j < min(n, i + k); j++)
        {
            len++;
            maxi = max(maxi, arr[j]);
            int sum = len * maxi + dp[j+1];
            maxAns = max(maxAns, sum);
        }
        dp[i] = maxAns;
    }
    return dp[0];
}

int maxSumAfterPartitioning(vector<int> &arr, int k)
{
    int n = arr.size();
    vector<int> dp(n, -1);
    return solve(0, k, n, arr, dp);
}