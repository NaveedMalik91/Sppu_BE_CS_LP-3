#include <bits/stdc++.h>
using namespace std;

struct Item
{
  int weight;
  int value;
};

int knapsack(int W, vector<Item> &items)
{
  int n = items.size();
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

   // Build DP table
  // 1-indexed dp table
  for (int i = 1; i <= n; i++)
  {
    for (int w = 1; w <= W; w++)
    {
      if (items[i - 1].weight <= w)
      {
        // max( exclude item(value stays same) , include item = value (subtact the weight from current) + best of remaining capacity )
        dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
      }
      else
      {
        dp[i][w] = dp[i - 1][w];
      }
    }
  }

  // ✅ Backtrack to find selected items
  int res = dp[n][W];
  int w = W;
  cout << "Selected item weights: ";

  for (int i = n; i > 0 && res > 0; i--)
  {
    // current result is same that of previous one i.e. no change
    if (res == dp[i - 1][w])
      continue; // Item not selected

    // Item was selected
    cout << items[i - 1].weight << " ";
    res -= items[i - 1].value;
    w -= items[i - 1].weight;
  }
  cout << endl;

  return dp[n][W];
}

int main()
{
  // Knapsack capacity
  int W = 50;     
  // {weight, value}                                       
  vector<Item> items = {{10, 60}, {20, 100}, {30, 120}}; 

  int max_value = knapsack(W, items);
  cout << "Maximum value: " << max_value << endl;

  return 0;
}

/*
  ---------------------------------------------------------
  Complexity Analysis of 0/1 Knapsack (Dynamic Programming)
  ---------------------------------------------------------

  Let:
     n = number of items
     W = maximum capacity of knapsack

  We use a DP table of size (n + 1) x (W + 1).

  For each item (n) we compute values for every capacity (W),
  and each DP state dp[i][w] takes constant time (O(1)).
  
  Therefore,
      Time Complexity = O(n * W)

  The DP table stores n * W values,

      Space Complexity = O(n * W)

 */

