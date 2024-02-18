#include <algorithm>
#include <cassert>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "../file_io/file_util.h"
#include "cc.h"

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

    freopen(outputPath.c_str(), "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);      
    cout.tie(NULL);
    for (auto& date : fileDates) {
        auto graph = readGraph(date);
        cout << date << " " << graph.size() << " " << getSccCount(graph) << " " << getLargestSccSize(graph) << " " << getWccCount(graph) << " " << getLargestWccSize(graph) << "\n";
    }   
}