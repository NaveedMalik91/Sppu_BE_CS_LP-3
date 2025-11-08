#include <bits/stdc++.h>
using namespace std;

struct Item {
  int weight;
  int value;
};

int knapsack(int W, vector<Item> &items) {
  int n = items.size();
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

  // Build DP table
  for (int i = 1; i <= n; i++) {
    for (int w = 1; w <= W; w++) {
      if (items[i - 1].weight <= w) {
        dp[i][w] = max(dp[i - 1][w],dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
      } else {
        dp[i][w] = dp[i - 1][w];
      }
    }
  }

  // ✅ Backtrack to find selected items
  int res = dp[n][W];
  int w = W;
  cout << "Selected item weights: ";

  for (int i = n; i > 0 && res > 0; i--) {
    if (res == dp[i - 1][w])
      continue;  // Item not selected

    // Item was selected
    cout << items[i - 1].weight << " ";
    res -= items[i - 1].value;
    w -= items[i - 1].weight;
  }
  cout << endl;

  return dp[n][W];
}

int main() {
  int W = 50; // Knapsack capacity
  vector<Item> items = {{10, 60}, {20, 100}, {30, 120}}; // {weight, value}

  int max_value = knapsack(W, items);
  cout << "Maximum value: " << max_value << endl;

  return 0;
}
