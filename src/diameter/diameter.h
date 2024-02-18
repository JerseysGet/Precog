#ifndef __DIAMETER_H
#define __DIAMETER_H

#include <vector>
using namespace std;

/* Assumest the graph is directed, finds diameter as longest path from every node */
int getDiameter(vector<vector<int>>& adjLists, int numToCheck = -1);



#endif