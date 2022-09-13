// Best Time to Buy and Sell Stock (https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
// DP on Stock

#include <iostream>
#include <vector>
using namespace std;

int maxProfit(vector<int> &prices)
{
    int maxpro = 0, mn = prices[0];
    for (int i = 1; i < prices.size(); i++)
    {
        maxpro = max(maxpro, prices[i] - mn);
        mn = min(mn, prices[i]);
    }
    return maxpro;
}