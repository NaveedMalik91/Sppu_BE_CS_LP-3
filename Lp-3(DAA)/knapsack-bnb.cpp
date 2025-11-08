#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Item
{
  int weight;
  int value;
  double ratio;
};

struct Node
{
  int level;
  int profit;
  int weight;
  double bound;
  vector<int> taken; // store which items are included
};

//Sort items in descending order of value/weight ratio.
bool compareItems(Item a, Item b)
{
  return a.ratio > b.ratio;
}


//Calculates upper bound of max profit from node u.
double bound(Node u, int n, int W, vector<Item> &items)
{
  //If weight already exceeds capacity → cannot take more → return bound = 0.
  if (u.weight >= W)
    return 0;

  double profit_bound = u.profit; //current profit
  int j = u.level + 1; //next item to consider
  int totweight = u.weight; //current weight

  //Add the item if everything is in bound like weight and next item
  while (j < n && totweight + items[j].weight <= W)
  {
    totweight += items[j].weight;
    profit_bound += items[j].value;
    j++;
  }

  //If the next item doesn't fully fit, add fractional part 
  if (j < n)
    profit_bound += (W - totweight) * items[j].ratio;

  return profit_bound;
}


int knapsack(int W, vector<Item> &items, vector<int> &bestTaken)
{
  int n = items.size();
  sort(items.begin(), items.end(), compareItems);

  queue<Node> Q;
  Node u, v;
  //u-> current node
  //v->child node/next node
  u.level = -1;
  u.profit = 0;
  u.weight = 0;
  u.bound = 0;
  u.taken = vector<int>(n, 0);
  Q.push(u);

  int maxProfit = 0;

  while (!Q.empty())
  {
    u = Q.front();
    Q.pop();

    //If all the items considered->skip this branch
    if (u.level == n - 1)
      continue;

    // Generate next decision level (next item index)
    // So we first copy everything from u into v:
    //Now we move to the next item index:

    v = u;
    v.level = u.level + 1;

    // Include the item
    v.weight = u.weight + items[v.level].weight;
    v.profit = u.profit + items[v.level].value;
    v.taken = u.taken;
    v.taken[v.level] = 1;

    //Add the items and its prfit to reuslt
    if (v.weight <= W && v.profit > maxProfit)
    {
      maxProfit = v.profit;
      bestTaken = v.taken;
    }

    v.bound = bound(v, n, W, items);
    if (v.bound > maxProfit)
      Q.push(v);

    // Exclude the item: Donot add the items.
    // But check If this branch still could beat best profit → explore.
    v = u;
    v.level = u.level + 1;
    v.bound = bound(v, n, W, items);
    if (v.bound > maxProfit)
      Q.push(v);
  }

  return maxProfit;
}

int main()
{
  int W = 50; //maximum knapsack capacity
  vector<Item> items = {{10, 60, 6}, {20, 100, 5}, {30, 120, 4}};

  for (auto &item : items)
    item.ratio = (double)item.value / item.weight;

  vector<int> bestTaken;
  int max_value = knapsack(W, items, bestTaken);

  cout << "Maximum value: " << max_value << endl;
  cout << "Items selected (weights): ";

  for (int i = 0; i < bestTaken.size(); i++)
  {
    if (bestTaken[i] == 1)
      cout << items[i].weight << " ";
  }

  cout << endl;
  return 0;
}
