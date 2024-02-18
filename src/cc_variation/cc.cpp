#include "cc.h"

#include <functional>
#include <queue>
#include <iostream>

vector<vector<int>> getSccs(vector<vector<int>>& adjLists) {
    int n = (int) adjLists.size();
    vector<int> stack;
    vector<bool> visited(n);

    vector<vector<int>> transposeLists(n);

    for (int i = 0; i < n; i++) {
        for (int to : adjLists[i]) {
            transposeLists[to].push_back(i);
        }
    }

    function<void(int)> dfs = [&] (int from) {
        visited[from] = true;
        for (auto to : adjLists[from]) {
            if (visited[to]) continue;
            dfs(to);
        }

        stack.push_back(from);
    };

    for (int i = 0; i < n; i++) {
        if (not visited[i]) dfs(i);
    }

    visited.assign(n, false);
    function<void(int, vector<int>&)> kosadfs = [&] (int from, vector<int>& scc) {
        // cout << "kosadfs on " << from << "\n";
        visited[from] = true;
        scc.push_back(from);
        for (auto to : transposeLists[from]) {
            // cout << "from = " << from <<  " to = " << to << " visited[to] = " << visited[to];
            if (visited[to]) {
                // cout << "\n";
                continue;
            }
            // cout << "actually visiting\n";
            kosadfs(to, scc); 
        }
    };  

    vector<vector<int>> ret;
    while (not empty(stack)) {
        int from = stack.back();
        stack.pop_back();
        if (visited[from]) continue;
        ret.push_back(vector<int>());
        kosadfs(from, ret.back());
    }

    return ret;
}

int getSccCount(vector<vector<int>>& adjLists) {
    auto sccs = getSccs(adjLists);
    return (int) sccs.size();
}

int getLargestSccSize(vector<vector<int>>& adjLists) {
    auto sccs = getSccs(adjLists);
    int ret = 0;
    for (auto scc : sccs) ret = max(ret, (int) scc.size());
    return ret;
}

vector<vector<int>> getWccs(vector<vector<int>>& adjLists) {
    int n = (int) adjLists.size();
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (int to : adjLists[i]) {
            adj[i].push_back(to);
            adj[to].push_back(i);
        }
    }

    vector<bool> visited(n);
    auto bfs = [&] (int src, vector<int>& wcc) {
        visited[src] = true;
        queue<int> q;
        q.push(src);
        while (not empty(q)) {
            auto from = q.front();
            wcc.push_back(from);
            q.pop();
            for (auto to : adj[from]) {
                if (visited[to]) continue;
                visited[to] = true;
                q.push(to);
            }
        }
    };

    vector<vector<int>> ret;
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        ret.push_back(vector<int>());
        bfs(i, ret.back());
    }

    return ret;
}

int getWccCount(vector<vector<int>>& adjLists) {
    auto wccs = getWccs(adjLists);
    return (int) wccs.size();
}

int getLargestWccSize(vector<vector<int>>& adjLists) {
    auto wccs = getWccs(adjLists);
    int ret = 0;
    for (auto wcc : wccs) ret = max(ret, (int) wcc.size());
    return ret;
}