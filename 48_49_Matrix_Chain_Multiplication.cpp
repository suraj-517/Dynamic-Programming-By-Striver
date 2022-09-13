// Matrix Chain Multiplication (https://practice.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1)
// Partition DP
// when problems solved in different patterns
/*
    Rules :
        1. Start with entire block/array f(start, end) -> f(i, j).
        2. Try all partition (Run a loop to try all partition).
        3. Return the best possible 2 partition.
*/

// f(1, 4) -> return the minimal multiplication to multiply matrix 1 to matrix 4.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    T = O(N*N*N) = O(N^3)
    S = O(N*N) + O(N)
*/
int solve(int i, int j, int arr[], vector<vector<int>> &dp)
{
    if (i == j)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int mini = 1e9;
    for (int k = i; k < j; k++)
    {
        int step = arr[i - 1] * arr[k] * arr[j] + solve(i, k, arr, dp) + solve(k + 1, j, arr, dp);
        mini = min(mini, step);
    }
    return dp[i][j] = mini;
}



int solve_2(int n, int arr[])
{
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++)
    {
        dp[i][i] = 0;
    }

    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            int mini = 1e9;
            for (int k = i; k < j; k++)
            {
                int step = arr[i - 1] * arr[k] * arr[j] + dp[i][k] + dp[k + 1][j];
                mini = min(mini, step);
            }
            dp[i][j] = mini;
        }
    }
    return dp[1][n - 1];
}


int matrixMultiplication(int n, int arr[])
{
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return solve(1, n - 1, arr, dp);
}