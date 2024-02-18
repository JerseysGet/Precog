#include "d_centrality.h"
#include <algorithm>

int get_max_in_d_centrality(vector<vector<int>>& adjLists) {
    int n = (int) adjLists.size();
    vector<int> inDegree(n);
    for (int i = 0; i < n; i++) {
        for (auto to : adjLists[i]) {
            inDegree[to]++;
        }
    }

    return *max_element(inDegree.begin(), inDegree.end());
}

int get_max_out_d_centrality(vector<vector<int>>& adjLists) {
    int n = (int) adjLists.size();
    int ret = 0;

    for (int i = 0; i < n; i++) {
        ret = max(ret, (int) adjLists[i].size());
    }

    return ret;
}

float get_average_d_centrality(vector<vector<int>>& adjLists) {
    int n = (int) adjLists.size();
    int tot = 0;
    for (int i = 0; i < n; i++) tot += (int) adjLists[i].size();
    return (0.0 + tot) / n;
}