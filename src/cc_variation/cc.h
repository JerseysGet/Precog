#ifndef __CC_H
#define __CC_H

using namespace std;
#include <vector>

vector<vector<int>> getSccs(vector<vector<int>>& adjLists);
int getSccCount(vector<vector<int>>& adjLists);
int getLargestSccSize(vector<vector<int>>& adjLists);

/* Assumes a directed graph as input */
vector<vector<int>> getWccs(vector<vector<int>>& adjLists);
int getWccCount(vector<vector<int>>& adjLists);
int getLargestWccSize(vector<vector<int>>& adjLists);

#endif