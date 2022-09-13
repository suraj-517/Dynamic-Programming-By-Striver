// N-th Fibonacci Number (https://www.codingninjas.com/codestudio/problems/nth-fibonacci-number_1115780)

#include <iostream>
#include <vector>
using namespace std;

int solve(int n, vector<int> &dp)
{
    if (n <= 1)
        return n;

    if (dp[n] != -1)
        return dp[n];
    dp[n] = solve(n - 1, dp) + solve(n - 2, dp);
    return dp[n];
}

int fibonacciNumber(int n)
{
    vector<int> dp(n + 1, -1);
    return solve(n, dp);
}

/*
    Time complexity: O(N)
    Space complexity: O(1)

    Where 'N' represents the "Nth" number .
*/

int fibonacciNumber(int n)
{
    int mod = (int)1e9 + 7;

    int a = 0;
    int b = 1;
    int c;

    for (int i = 2; i <= n; i++)
    {

        // The variable c stores the ith Fibonacci Number.
        c = (a + b) % mod;

        // Updating values of a and b.
        a = b;
        b = c;
    }

    // The variable b stores the nth Fibonacci Number.
    return b;
}