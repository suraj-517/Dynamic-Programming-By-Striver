// Frog Jump (https://www.codingninjas.com/codestudio/problems/frog-jump_3621012)

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int solve(int ind, vector<int> &heights, vector<int> &dp) // Top - Down // T = O(N), S = O(N)
{
    if (ind == 0)
        return 0;

    if (dp[ind] != -1)
        return dp[ind];

    int left = solve(ind - 1, heights, dp) + abs(heights[ind] - heights[ind - 1]);
    int right = INT_MAX;
    if (ind > 1)
    {
        right = solve(ind - 2, heights, dp) + abs(heights[ind] - heights[ind - 2]);
    }
    int ans = min(left, right);
    return dp[ind] = ans;
}

int solve_2(vector<int> &dp, vector<int> &heights, int n) // Bottom - up // T = O(N), S = O(N)
{
    dp[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int left = dp[i - 1] + abs(heights[i] - heights[i - 1]);
        int right = INT_MAX;
        if (i > 1)
        {
            right = dp[i - 2] + abs(heights[i] - heights[i - 2]);
        }
        dp[i] = min(left, right);
    }
    return dp[n - 1];
}

int solve_3(vector<int> &heights, int n) // T = O(N), S = O(1)
{
    int prev = 0, prev2 = 0;

    for(int i = 1; i < n; i++)
    {
        int left = prev + abs(heights[i] - heights[i - 1]);
        int right = INT_MAX;
        if (i > 1)
        {
            right = prev2 + abs(heights[i] - heights[i - 2]);
        }
        int cur1 = min(left, right);
        prev2 = prev;
        prev = cur1;
    }
    return prev;
}

int frogJump(int n, vector<int> &heights)
{
    vector<int> dp(n + 1, -1); // dp(n, -1) works fine
    return solve(n, heights, dp);
}