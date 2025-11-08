#include <bits/stdc++.h>
using namespace std;

int COL;  // Column where the user wants to place the first queen
int ROW;  // Row where the user wants to place the first queen
int N = 4; // Default board size (updated by user)

void printSolution(vector<vector<int>> board) {
  for (int i = 0; i < N; i++) { 
    for (int j = 0; j < N; j++) { 
      if (board[i][j])
        cout << "Q "; 
        cout << ". "; 
    }
    cout << "\n"; 
  }
}

// Check if placing a queen at (row, col) is safe
bool isSafe(vector<vector<int>> board, int row, int col) {
  int i, j;

  // Check same row (left side)
  for (i = 0; i < col; i++)
    if (board[row][i])
      return false;

  // Check same row (right side) - extra safety check
  for (i = col + 1; i < N; i++)
    if (board[row][i])
      return false;

  // Check diagonal (bottom-right)
  for (i = row, j = col; i < N && j < N; i++, j++)
    if (board[i][j])
      return false;

  // Check diagonal (top-right)
  for (i = row, j = col; i >= 0 && j < N; i--, j++)
    if (board[i][j])
      return false;

  // Check diagonal (top-left)
  for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    if (board[i][j])
      return false;

  // Check diagonal (bottom-left)
  for (i = row, j = col; j >= 0 && i < N; i++, j--)
    if (board[i][j])
      return false;

  return true; // Safe to place queen
}


// Recursive function to place queens column by column
bool solveNQUtil(vector<vector<int>> &board, int col) {

  // If all queens are placed → solution found
  if (col >= N)
    return true;

  // Skip the column containing the user-fixed queen
  if (col == COL) {
    return solveNQUtil(board, col + 1);
  }

  // Try placing queen in each row of this column
  for (int i = 0; i < N; i++) {

    // Check if placing queen here is safe
    if (isSafe(board, i, col)) {

      board[i][col] = 1; // Place queen

      // If placing queen here leads to a solution → done
      if (solveNQUtil(board, col + 1))
        return true;

      board[i][col] = 0; // Backtrack if not successful
    }
  }

  return false; // No valid position found in this column
}

// Function to take input and start solving
bool solveNQ() {
  cout << "Enter size of board: ";
  cin >> N; 

  cout << "Enter row and col of first queen to be placed:\nrow (1-" << N << "): ";
  cin >> ROW;
  ROW--; // Convert to 0-based index

  cout << "\ncol(1-" << N << "): ";
  cin >> COL;
  COL--; // Convert to 0-based index
  cout << endl;

  // Create N x N chessboard initialized to 0
  vector<vector<int>> board(N, vector<int>(N, 0));

  // Place the user-fixed queen
  board[ROW][COL] = 1;

  // Solve from column 0
  if (!solveNQUtil(board, 0)) {
    cout << "Solution does not exist";
    return false;
  }
  printSolution(board);
  return true;
}

int main() {
  solveNQ(); 
  return 0;
}

/*
==================== N-QUEEN COMPLEXITY ANALYSIS ====================

N-Queen is solved using Backtracking. We try placing a queen in a row
of the current column and recursively attempt to place queens in the
next columns. If a placement leads to conflict, we backtrack.

-----------------------------------------------------------------------
TIME COMPLEXITY:

In the worst case, we try all possible arrangements of N queens:
- First column → N choices
- Second column → (N-1) possible safe choices (approx)
- Third column → (N-2) possible safe choices (approx)
  ...
This resembles a factorial growth pattern.

Worst Case Time Complexity ≈ O(N!)

More accurately:
Time Complexity = O(N!) because for each column we try multiple rows,
and reduce options as we move forward.

-----------------------------------------------------------------------
SPACE COMPLEXITY:

Space is mainly used by:
1) The recursion stack (depth = N, one call per column)
2) The chessboard of size N x N

Chessboard: O(N²)
Recursion Stack: O(N)

Total Space Complexity = O(N²)
*/