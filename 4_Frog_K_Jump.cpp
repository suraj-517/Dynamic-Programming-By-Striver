// Frog K Jumps 


#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int solve(int ind, int k, vector<int> &heights, vector<int> &dp) // Top - Down // T = O(N*K), S = O(N) + O(N)
{
    if (ind == 0)
        return 0;

    if (dp[ind] != -1)
        return dp[ind];
    int ans = INT_MAX;
    for (int i = 1; i <= k; i++)
    {
        if (ind - i >= 0)
        {
            int temp = solve(ind - i, k, heights, dp) + abs(heights[ind] - heights[ind - i]);
            ans = min(ans, temp);
        }
    }
    return dp[ind] = ans;
}



int frogJump(int n, int k, vector<int> &heights)
{
    vector<int> dp(n + 1, -1); // dp(n, -1) works fine
    return solve(n - 1, k, heights, dp);
}