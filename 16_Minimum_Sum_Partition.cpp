// Partition Array Into Two Arrays to Minimize Sum Difference (https://practice.geeksforgeeks.org/problems/minimum-sum-partition3317/1)
// DP ON SUBSEQUENCE/SUBSETS/TARGET
// Similar to Previous Question 


#include <iostream>
#include <vector>
using namespace std;



int solve_2(int n, int sum, int arr[])
{
    vector<vector<bool>> dp(n, vector<bool>(sum + 1, 0));
    for (int i = 0; i < n; i++)
        dp[i][0] = true;

    if (arr[0] <= sum)
        dp[0][arr[0]] = true;

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            bool notTake = dp[i - 1][j];
            bool take = false;

            if (j >= arr[i])
                take = dp[i - 1][j - arr[i]];

            bool ans = notTake | take;
            dp[i][j] = ans;
        }
    }

    int mini = 1e9;
    for (int i = 0; i <= sum / 2; i++)
    {
        if (dp[n - 1][i] == true)
        {
            mini = min(mini, abs((sum - i) - i));
        }
    }
    return mini;
}


int minDifference(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];

    return solve_2(n, sum, arr);
}