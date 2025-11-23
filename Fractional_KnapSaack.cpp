// This code is for Ubuntu // 


#include <bits/stdc++.h>
using namespace std;

double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity, int n) {
    // Pair each value with its weight
    vector<pair<int, int>> items;
    for (int i = 0; i < n; i++) {
        items.push_back({val[i], wt[i]});
    }

    // Sort by value/weight ratio in descending order
    sort(items.begin(), items.end(), [](auto &a, auto &b) {
        double r1 = (double)a.first / a.second;
        double r2 = (double)b.first / b.second;
        return r1 > r2; // descending
    });

    double remaining = capacity;
    double profit = 0.0;

    for (int i = 0; i < n; i++) {
        if (remaining >= items[i].second) {
            // take whole item
            profit += items[i].first;
            remaining -= items[i].second;
        } else {
            // take fractional part
            profit += (remaining / items[i].second) * items[i].first;
            break;
        }
    }

    return profit;
}

int main() {
    int n;
    cout << "Enter no. of items: ";
    cin >> n;

    vector<int> val(n), wt(n);
    cout << "Enter values of items: ";
    for (int i = 0; i < n; i++) cin >> val[i];

    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++) cin >> wt[i];

    int capacity;
    cout << "Enter capacity: ";
    cin >> capacity;

    cout << "Profit: " << fractionalKnapsack(val, wt, capacity, n) << endl;
    return 0;
}