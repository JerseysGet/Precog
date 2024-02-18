#include "diameter.h"

#include <algorithm>
#include <chrono>
#include <queue>
#include <random>

int longestPathFrom(int src, vector<vector<int>>& adj) {
    int n = (int)adj.size();
    vector<int> dist(n, __INT_MAX__);
    dist[src] = 0;
    queue<int> q;
    q.push(src);

    while (not empty(q)) {
        int from = q.front();
        q.pop();
        for (auto to : adj[from]) {
            if (dist[to] == __INT_MAX__) {
                dist[to] = dist[from] + 1;
                q.push(to);
            }
        }
    }

    int ret = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] == __INT_MAX__) continue;
        ret = max(ret, dist[i]);
    }

    return ret;
}

#define PORTION_TO_CHECK 0.1L
int getDiameter(vector<vector<int>>& adjLists, int numToCheck) {
    int n = (int)adjLists.size();
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end(), rng);

    vector<bool> toChoose(n);
    if (numToCheck == -1) {
        for (int i = 0; (i + 1) <= PORTION_TO_CHECK * n; i++) {
            toChoose[perm[i]] = true;
        }
    } else {
        for (int i = 0; i < min(n, numToCheck); i++) {
            toChoose[perm[i]] = true;
        }
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (int to : adjLists[i]) {
            adj[i].push_back(to);
            adj[to].push_back(i);
        }
    }

    int ret = 0;
    for (int i = 0; i < n; i++)
        if (toChoose[i]) ret = max(ret, longestPathFrom(i, adj));
    return ret;
}