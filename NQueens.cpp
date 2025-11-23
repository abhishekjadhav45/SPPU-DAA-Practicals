// This code is for Ubuntu // 


#include <bits/stdc++.h>
using namespace std;

bool isSafe(int row, int col, vector<vector<char>> &board, int n) {
    int dR = row, dC = col;

    // Check left in the same row
    int c = col;
    while (c >= 0) {
        if (board[row][c] == 'Q') return false;
        c--;
    }

    // Check upper-left diagonal
    int r = row, cc = col;
    while (r >= 0 && cc >= 0) {
        if (board[r][cc] == 'Q') return false;
        r--; cc--;
    }

    // Check lower-left diagonal
    r = row; cc = col;
    while (r < n && cc >= 0) {
        if (board[r][cc] == 'Q') return false;
        r++; cc--;
    }

    return true;
}

void recursive(int col, vector<vector<char>> &board, vector<vector<string>> &ans, int n) {
    if (col == n) {
        vector<string> temp;
        for (int i = 0; i < n; i++) {
            string rowStr = "";
            for (int j = 0; j < n; j++) {
                rowStr += board[i][j];
                rowStr += " ";  // add space after each character
            }
            temp.push_back(rowStr);
        }
        ans.push_back(temp);
        return;
    }

    for (int row = 0; row < n; row++) {
        if (isSafe(row, col, board, n)) {
            board[row][col] = 'Q';
            recursive(col + 1, board, ans, n);
            board[row][col] = '.'; // backtrack
        }
    }
}

vector<vector<string>> solve(int n) {
    vector<vector<string>> ans;
    vector<vector<char>> board(n, vector<char>(n, '.'));
    recursive(0, board, ans, n);
    return ans;
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    vector<vector<string>> solutions = solve(n);
    int count = 1;
    for (auto &board : solutions) {
        cout << "Solution " << count++ << ":\n";
        for (auto &row : board) {
            cout << row << "\n";
        }
        cout << "\n";
    }

    return 0;
}