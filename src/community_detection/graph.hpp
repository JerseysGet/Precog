#ifndef __GRAPH_H
#define __GRAPH_H

#include <vector>

using namespace std;

typedef vector<int> Node;
typedef pair<int, int> Edge;

struct Graph {
    int nodect;
    vector<Node> nodes;            /* Node with index 'i' contains nodes[i] as vertices */
    vector<vector<Edge>> adjLists; /* Contains {toIndex, weight} entries in adjacency list */
    int totalEdgeWeight = 0;       /* m, or twice the total edge weight */
    Graph();

    /* Takes undirected adjLists and converts to undirected graph */
    Graph(vector<vector<int>>& adjLists);
};

inline Graph::Graph() {}

inline Graph::Graph(vector<vector<int>>& _adjLists) {
    nodect = (int)_adjLists.size();

    nodes.assign(nodect, Node());
    for (int i = 0; i < nodect; i++) {
        nodes[i].push_back(i);
    }

    adjLists.assign(nodect, vector<Edge>());
    for (int i = 0; i < nodect; i++) {
        for (auto to : _adjLists[i]) {
            adjLists[i].push_back({to, 1});
            totalEdgeWeight++;
        }
    }

    
}

#endif