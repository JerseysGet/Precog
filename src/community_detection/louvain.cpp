#include <algorithm>
#include <cassert>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "../file_io/file_util.h"
#include "graph.hpp"
#include "partition.hpp"

#define all(s) s.begin(), s.end()

using namespace std;
using namespace std::filesystem;

vector<vector<int>> getUndirAdjLists(vector<vector<int>>& dirAdjLists) {
    int n = (int)dirAdjLists.size();
    vector<vector<int>> adjLists(n);
    for (int i = 0; i < n; i++) {
        for (auto to : dirAdjLists[i]) {
            adjLists[i].push_back(to);
            adjLists[to].push_back(i);
        }
    }

    return adjLists;
}

int main() {
    // vector<vector<int>> adjLists(10);
    // adjLists[0].push_back(1);
    // adjLists[1].push_back(2);
    // adjLists[2].push_back(0);
    // adjLists[2].push_back(3);
    // adjLists[3].push_back(1);
    // auto _ = getUndirAdjLists(adjLists);
    // Graph g(_);
    // Partition p(g);
    // bool changed = false;
    // do {
    //     changed = p.step1();
    //     g = p.partitionGraph();
    //     p = Partition(g);
    // } while (changed);

    string prefix = "./dataset/pretime";
    vector<string> fileDates;
    for (const auto& entry : directory_iterator(prefix)) {
        fileDates.push_back(entry.path());
    }

    sort(all(fileDates));
    // reverse(all(fileDates));
    int prefixMax = 0;
    for (auto& date : fileDates) {
        cerr << "Computing " << date << endl;
        auto graph = readGraph(date);

        auto undirGraph = getUndirAdjLists(graph);
        
        Graph gg(undirGraph);
        Partition p(gg);

        bool changed = false;
        int iter = 0;
        bool terminated = true;
        do {
            changed = p.step1(terminated);
            // if (not terminated) {
            //     cerr << "jgijg\n";
            //     break;
            // }
            gg = p.partitionGraph();
            p = Partition(gg);
        } while (changed);

        int mx = 0;
        for (int i = 0; i < gg.nodect; i++) {
            mx = max(mx, (int) gg.nodes[i].size());
        }
        prefixMax = max(mx, prefixMax);
        if (terminated) cout << " " << date << " " << graph.size() << " " << gg.nodect << " " << prefixMax << "\n";
    }
}