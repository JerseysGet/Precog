#include <algorithm>
#include <cassert>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "../file_io/file_util.h"
#include "d_centrality.h"

#define all(s) s.begin(), s.end()

using namespace std;
using namespace std::filesystem;

int main(int argc, char* argv[]) {
    vector<string> fileDates;
    string prefix = "./dataset/pretime";
    for (const auto& entry : directory_iterator(prefix)) {
        fileDates.push_back(entry.path());
    }

    sort(all(fileDates));

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);      
    cout.tie(NULL);
    for (int i = 0; i < (int) fileDates.size(); i++) {
        auto date = fileDates[i];
        auto graph = readGraph(date);
        
        int maxIn = get_max_in_d_centrality(graph);
        int maxOut = get_max_out_d_centrality(graph);
        auto average = get_average_d_centrality(graph);
        cout << date << " " << graph.size() << " " << maxIn << " " << maxOut << " " << average << "\n";
    }

}