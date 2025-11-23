/* This code is designed to run on Ubuntu*/


#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int src, dest, weight;
};

void bellmanFord(int V, int E, vector<Edge>& edges, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for negative-weight cycles
    bool negativeCycle = false;
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            negativeCycle = true;
            break;
        }
    }

    if (negativeCycle) {
        cout << "\nGraph contains a negative weight cycle!" << endl;
    } else {
        cout << "\nVertex\tDistance from Source\n";
        for (int i = 0; i < V; i++) {
            cout << i << "\t\t";
            if (dist[i] == INT_MAX)
                cout << "INF";
            else
                cout << dist[i];
            cout << endl;
        }
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices (V): ";
    cin >> V;
    cout << "Enter number of edges (E): ";
    cin >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (src dest weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    bellmanFord(V, E, edges, src);

    return 0;
}




Enter number of vertices (V): 5
Enter number of edges (E): 8
Enter edges (src dest weight):
0 1 -1
0 2 4
1 2 3
1 3 2
1 4 2
3 2 5
3 1 1
4 3 -3
Enter source vertex: 0