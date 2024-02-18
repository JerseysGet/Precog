#include "b_centrality.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <queue>
#include <random>

void bfs_tree(int src, vector<vector<int>>& adjLists, vector<vector<int>>& prev, vector<vector<int>>& next, vector<int>& dist) {
    int n = (int)adjLists.size();
    prev.assign(n, vector<int>());
    next.assign(n, vector<int>());
    dist.assign(n, __INT_MAX__);

    queue<int> q;
    dist[src] = 0;
    q.push(src);

    while (not empty(q)) {
        auto from = q.front();
        q.pop();
        for (auto to : adjLists[from]) {
            if (dist[to] != __INT_MAX__) continue;
            dist[to] = 1 + dist[from];
            q.push(to);
        }
    }

    for (int i = 0; i < n; i++) {
        if (dist[i] == __INT_MAX__) continue;
        for (auto to : adjLists[i]) {
            if (dist[to] == __INT_MAX__) continue;
            if (dist[i] + 1 == dist[to]) {
                next[i].push_back(to);
                prev[to].push_back(i);
            }
        }
    }
}

void topologicalSort(vector<vector<int>>& next, vector<int>& topo, vector<bool>& visited, int from) {
    visited[from] = true;
    for (auto to : next[from]) {
        if (visited[to]) continue;
        topologicalSort(next, topo, visited, to);
    }

    topo.push_back(from);
};

void vec_add(vector<float>& out, vector<float>& in) {
    for (int i = 0; i < (int) out.size(); i++) out[i] += in[i];
}

#pragma omp declare reduction( \
        add_vec_float : \
        vector<float> : \
        vec_add(omp_out, omp_in) \
    )   initializer (omp_priv=omp_orig)

float b_centrality(vector<vector<int>>& adjLists) {
    // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int n = (int)adjLists.size();
    vector<float> ret(n);

    #pragma omp parallel for default(none) reduction(add_vec_float: ret) shared(n) shared(adjLists)
    for (int src = 0; src < n; src++) {
        vector<vector<int>> prev, next;
        vector<int> dist;
        bfs_tree(src, adjLists, prev, next, dist);
        vector<int> topoSort;
        vector<bool> visited(n);
        topologicalSort(next, topoSort, visited, src);
        reverse(topoSort.begin(), topoSort.end());
        vector<int> pathCount(n);
        pathCount[src] = 1;
        for (auto u : topoSort) {
            assert(dist[u] != __INT_MAX__);
            for (auto p : prev[u]) {
                pathCount[u] += pathCount[p];
            }
        }

        vector<float> delta(n);

        for (auto it = topoSort.rbegin(); it != topoSort.rend(); it++) {
            int u = *it;
            for (auto n : next[u]) {
                delta[u] += (1 + delta[n]) * pathCount[u] / (0.0 + pathCount[n]);
            }

            if (u != src) {
                ret[u] += delta[u];
            }
        }
    }

    float mx = 0;
    #pragma omp parallel for default(none) shared(n) shared(ret) reduction(max: mx)
    for (int i = 0; i < n; i++) {
        mx = max(ret[i], mx);
    }

    return mx;
}