#include <iostream>
#include <vector>

using namespace std;

int tsp(vector<vector<int>> dist, int n, int nodes_visited, int curr_node,
        vector<vector<int>> &dp) {
    if (nodes_visited == (1 << n) - 1) {
        return dist[curr_node][0];
    }

    if (dp[nodes_visited][curr_node] != -1) {
        return dp[nodes_visited][curr_node];
    }

    int ans = INT_MAX;

    for (int choice = 0; choice < n; choice++) {
        int mask = (1 << choice);
        if ((nodes_visited & mask) == 0) {
            int branch = dist[curr_node][choice] +
                         tsp(dist, n, nodes_visited | mask, choice, dp);
            ans = min(ans, branch);
        }
    }

    dp[nodes_visited][curr_node] = ans;

    return ans;
}

int main() {
    vector<vector<int>> dist;  // Costs of going from node i to node j
    // Example
    dist = {{0, 20, 42, 25}, {20, 0, 30, 34}, {42, 30, 0, 10}, {25, 34, 10, 0}};

    int n = dist.size();    // Amount on nodes
    int nodes_visited = 1;  // Bitwise representation of nodes visited
    int curr_node = 0;
    vector<vector<int>> dp(
        1 << n, vector<int>(n, -1));  // Dynamic programming mapping
                                      // `nodes_visited` and `curr_node`

    int min_distance = tsp(dist, n, nodes_visited, curr_node, dp);
    cout << min_distance << endl;
}