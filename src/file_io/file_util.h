#ifndef __FILE_UTIL_H
#define __FILE_UTIL_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Reads files with graphs in the format
number_of_nodes number_of_edges
edge_1_from edge_1_to
.
.
.
edge_m_from edge_m_from
where the nodes are 0 indexed */
vector<vector<int>> readGraph(string path);

#endif