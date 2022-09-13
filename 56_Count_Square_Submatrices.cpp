// Count Square Submatrices with All Ones (https://leetcode.com/problems/count-square-submatrices-with-all-ones/)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    dp[i][j] means the size of biggest square with A[i][j] as bottom-right corner.
    dp[i][j] also means the number of squares with A[i][j] as bottom-right corner.

    If A[i][j] == 0, no possible square.
    If A[i][j] == 1,
    we compare the size of square dp[i-1][j-1], dp[i-1][j] and dp[i][j-1].
    min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1 is the maximum size of square that we can find.
*/

// Time O(M*N)
// Space O(1)
int countSquares(vector<vector<int>> &mat)
{
    int n = mat.size(), m = mat[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++)
        dp[i][0] = mat[i][0];

    for (int j = 0; j < m; j++)
        dp[0][j] = mat[0][j];

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            if (mat[i][j] == 0)
                dp[i][j] = 0;
            else
            {
                dp[i][j] = 1 + min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1]));
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            sum += dp[i][j];
        }
    }
    return sum;
}