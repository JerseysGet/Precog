#include <algorithm>
#include <cassert>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "../file_io/file_util.h"
#include "diameter.h"

#define all(s) s.begin(), s.end()

using namespace std;
using namespace std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Expected 1 filename (2 arguments), found " << argc << " arguments \n";
        assert(false);
    }

    string outpath = argv[1];
    string prefix = "./dataset/pretime";
    vector<string> fileDates;
    for (const auto& entry : directory_iterator(prefix)) {
        fileDates.push_back(entry.path());
    }

    sort(all(fileDates));

    freopen(outpath.c_str(), "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (auto& date : fileDates) {
        cerr << "Computing " << date << endl;
        auto graph = readGraph(date);
        int n = (int)graph.size();
        int currdia = getDiameter(graph, max(n / 5, 1500));
        cout << date << " " << graph.size() << " " << currdia << "\n";
    }
}