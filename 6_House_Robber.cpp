// House Robber II (https://www.codingninjas.com/codestudio/problems/house-robber_839733)

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

long long solve_3(vector<int> &nums, int n) // Space optimisation , T = O(N), S = O(N)
{
    long long prev = nums[0];
    long long prev2 = 0;
    for (int i = 1; i < n; i++)
    {
        long long pick = nums[i] + prev2;
        long long notPick = 0 + prev;
        long long cur1 = max(pick, notPick);
        prev2 = prev;
        prev = cur1;
    }
    return prev;
}

long long int houseRobber(vector<int> &valueInHouse)
{
    int n = valueInHouse.size();
    if (n == 1)
        return valueInHouse[0];

    vector<int> temp1, temp2;
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
            temp1.push_back(valueInHouse[i]);

        if (i != n - 1)
            temp2.push_back(valueInHouse[i]);
    }

    long long ans1 = solve_3(temp1, n - 1);
    long long ans2 = solve_3(temp2, n - 1);
    return max(ans1, ans2);
}