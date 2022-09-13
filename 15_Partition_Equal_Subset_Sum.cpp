// Partition Equal Subset Sum (https://leetcode.com/problems/partition-equal-subset-sum/)
// DP ON SUBSEQUENCE/SUBSETS/TARGET
// Similar to Previous Question

#include <iostream>
#include <vector>
using namespace std;

bool solve_3(int n, int sum, vector<int> &arr)
{
    vector<int> prev(sum + 1, 0), cur(sum + 1, 0);
    prev[0] = cur[0] = true;

    if (arr[0] <= sum)
        prev[arr[0]] = true;

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            bool notTake = prev[j];
            bool take = false;
            if (j >= arr[i])
                take = prev[j - arr[i]];

            bool ans = notTake | take;
            cur[j] = ans;
        }
        prev = cur;
    }
    return prev[sum];
}

bool canPartition(vector<int> &nums)
{
    int n = nums.size();
    int sum = 0;
    for (auto i : nums)
    {
        sum += i;
    }

    if (sum % 2 == 1)
        return false;
    else
        return solve_3(n, sum / 2, nums);
}