#ifndef __D_CENTRALITY_H
#define __D_CENTRALITY_H

#include <vector>

using namespace std;

int get_max_in_d_centrality(vector<vector<int>>& adjLists);
int get_max_out_d_centrality(vector<vector<int>>& adjLists);
float get_average_d_centrality(vector<vector<int>>& adjLists);

#endif