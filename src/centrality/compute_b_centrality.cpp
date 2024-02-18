#include <algorithm>
#include <cassert>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "../file_io/file_util.h"
#include "b_centrality.h"

#define all(s) s.begin(), s.end()

using namespace std;
using namespace std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Expected 1 filename (2 arguments), found " << argc << " arguments \n";
        assert(false);
    }

    string outputPath = argv[1];

    string prefix = "./dataset/pretime";
    vector<string> fileDates;
    for (const auto& entry : directory_iterator(prefix)) {
        fileDates.push_back(entry.path());
    }

    sort(all(fileDates));
    cerr << "Total = " << fileDates.size() << "\n";

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);      
    cout.tie(NULL);
    float mx = 0;
    for (int i = 0; i < (int) fileDates.size(); i++) {
        auto date = fileDates[i];
        if (i % 10 == 0) cerr << i << "\n";
        auto graph = readGraph(date);
        int n = (int) graph.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) {
            for (int to : graph[i]) {
                adj[i].push_back(to);
                adj[to].push_back(i);
            }
        }

        auto ret = b_centrality(adj);

        cout << date << " ";
        cout << (mx = max(mx, ret)) << " ";
        cout << "\n";

    }  
}