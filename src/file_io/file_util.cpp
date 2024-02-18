#include "file_util.h"

vector<vector<int>> readGraph(string path) {
    freopen(path.c_str(), "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adjLists(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adjLists[u].push_back(v);
    }

    return adjLists;
}