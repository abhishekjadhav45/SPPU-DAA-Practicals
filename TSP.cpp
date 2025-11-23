#include <bits/stdc++.h>
using namespace std;

#define INF 9999

struct Node {
    vector<int> path;              // current path
    vector<vector<int>> matrix;    // reduced cost matrix
    int cost;                      // total cost
    int vertex, level;             // current vertex and level
};

// Function to reduce a matrix and return the reduction cost
int reduceMatrix(vector<vector<int>>& mat) {
    int n = mat.size(), reduction = 0;

    // Row reduction
    for (int i = 0; i < n; i++) {
        int rowMin = INF;
        for (int j = 0; j < n; j++)
            rowMin = min(rowMin, mat[i][j]);
        if (rowMin != INF && rowMin > 0) {
            reduction += rowMin;
            for (int j = 0; j < n; j++)
                if (mat[i][j] != INF)
                    mat[i][j] -= rowMin;
        }
    }

    // Column reduction
    for (int j = 0; j < n; j++) {
        int colMin = INF;
        for (int i = 0; i < n; i++)
            colMin = min(colMin, mat[i][j]);
        if (colMin != INF && colMin > 0) {
            reduction += colMin;
            for (int i = 0; i < n; i++)
                if (mat[i][j] != INF)
                    mat[i][j] -= colMin;
        }
    }
    return reduction;
}

// Create a new node by moving from 'i' to 'j'
Node* newNode(vector<vector<int>> parent, vector<int> const& path, int level, int i, int j) {
    int n = parent.size();
    Node* node = new Node;
    node->matrix = parent;

    // Set outgoing edges from i and incoming edges to j as INF
    for (int k = 0; k < n; k++) {
        node->matrix[i][k] = INF;
        node->matrix[k][j] = INF;
    }
    node->matrix[j][0] = INF;  // prevent returning to start too early

    node->path = path;
    node->path.push_back(j);
    node->level = level;
    node->vertex = j;

    return node;
}

// Compare nodes by cost (for priority queue)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->cost > b->cost;
    }
};

// TSP using Branch and Bound
void solveTSP(vector<vector<int>> cost) {
    int n = cost.size();

    vector<vector<int>> reduced = cost;
    int costReduction = reduceMatrix(reduced);

    priority_queue<Node*, vector<Node*>, Compare> pq;

    Node* root = new Node;
    root->path.push_back(0);
    root->matrix = reduced;
    root->cost = costReduction;
    root->vertex = 0;
    root->level = 0;

    pq.push(root);

    int minCost = INF;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node* curr = pq.top();
        pq.pop();

        int i = curr->vertex;

        if (curr->level == n - 1) {  // all cities visited
            int finalCost = curr->cost + cost[i][0];
            if (finalCost < minCost) {
                minCost = finalCost;
                bestPath = curr->path;
                bestPath.push_back(0);
            }
            continue;
        }

        for (int j = 0; j < n; j++) {
            if (curr->matrix[i][j] != INF) {
                Node* child = newNode(curr->matrix, curr->path, curr->level + 1, i, j);
                child->cost = curr->cost + curr->matrix[i][j] + reduceMatrix(child->matrix);
                pq.push(child);
            }
        }
    }

    cout << "\nOptimal Path: ";
    for (int i = 0; i < bestPath.size(); i++) {
        cout << bestPath[i] + 1;
        if (i != bestPath.size() - 1) cout << " -> ";
    }
    cout << "\nMinimum Tour Cost: " << minCost << endl;
}

// Main function
int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));
    cout << "Enter cost matrix (use 999 for infinity):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    solveTSP(cost);
    return 0;
}





Enter number of cities: 4
Enter cost matrix (use 999 for infinity):
999 10 15 20
10 999 35 25
15 35 999 30
20 25 30 999