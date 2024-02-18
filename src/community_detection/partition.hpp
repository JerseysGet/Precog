#ifndef __PARTITION_H
#define __PARTITION_H

#include <algorithm>
#include <cassert>
#include <chrono>
#include <numeric>
#include <random>
#include <vector>
#include <map>

#include "graph.hpp"
#include <iostream>

using namespace std;

struct Partition {
    vector<int> nodeToCommunity;
    vector<int> sigmaIn;  /* Number of edges in a community x 2 */
    vector<int> sigmaTot; /* Sum of degrees of nodes in a community */
    Graph g;

    Partition(Graph& g);

    /* Remove node from its community, given the number of edges between the node and its community and the degree of the node */
    void remove(int node, int edgesBetween, int degree, int selfEdges);

    /* Add node to community, given the number of edges between the node and the community */
    void add(int node, int community, int edgesBetween, int degree, int selfEdges);

    /* Calculates gain in modularity if node were to move into community */
    double gain(int node, int community, int edgesBetween, int degree);

    /* Step 1 of the Louvian Algorithm, greedily changing communities, returns true if something changed */
    bool step1(bool& terminated) {
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        vector<int> randomOrder(g.nodect);
        iota(randomOrder.begin(), randomOrder.end(), 0);
        shuffle(randomOrder.begin(), randomOrder.end(), rng);

        bool changedAtAll = false;
        int MAX_ITER = 50;
        vector<int> edgesBetween(g.nodect);
        bool changed = false;
        int iter = 0;
        int iter_count = 0;
        do {
            iter_count++;
            changed = false;
            for (auto nodeIndex : randomOrder) {
                int degree = 0;
                int selfEdges = 0;
                int oldCommunity = nodeToCommunity[nodeIndex];
                edgesBetween[oldCommunity] = 0;
                
                for (auto& [to, w] : g.adjLists[nodeIndex]) {
                    if (to == nodeIndex) selfEdges += w;
                    edgesBetween[nodeToCommunity[to]] = 0;
                    degree += w;
                }
                for (auto& [to, w] : g.adjLists[nodeIndex])
                    if (to != nodeIndex) {
                        edgesBetween[nodeToCommunity[to]] += w;
                    }

                remove(nodeIndex, edgesBetween[oldCommunity], degree, selfEdges);

                int max_community = oldCommunity;
                double max_gain = 0.0L;

                for (auto& [to, w] : g.adjLists[nodeIndex])
                    if (to != nodeIndex) {
                        int otherCommunity = nodeToCommunity[to];
                        double gn = gain(nodeIndex, otherCommunity, edgesBetween[otherCommunity], degree);
                        if (gn > max_gain) {
                            max_gain = gn;
                            max_community = otherCommunity;
                        }
                    }

                add(nodeIndex, max_community, edgesBetween[max_community], degree, selfEdges);

                if (max_community != oldCommunity) changed = true;
            }

            if (changed) changedAtAll = true;
            // cout << iter_count << " ";
            // cout.flush();
            MAX_ITER--;
        } while (changed and MAX_ITER);

        terminated = not (MAX_ITER == 0);
        return changedAtAll;
    }

    /* Re-creates the graph after step1() */
    Graph partitionGraph();
};

inline Partition::Partition(Graph& _g) {
    g = _g;
    nodeToCommunity.resize(g.nodect);
    iota(nodeToCommunity.begin(), nodeToCommunity.end(), 0);

    sigmaIn.assign(g.nodect, 0);
    sigmaTot.assign(g.nodect, 0);
    for (int i = 0; i < g.nodect; i++) {
        int totalDegree = 0;
        for (auto& [to, w] : g.adjLists[i]) {
            if (to == i) {
                sigmaIn[i] += w;
            }

            totalDegree += w;
        }

        sigmaTot[i] = totalDegree;
    }
}

inline Graph Partition::partitionGraph() {
    Graph ret;
    vector<int> communityCts(g.nodect, 0);
    for (int i = 0; i < g.nodect; i++) {
        communityCts[nodeToCommunity[i]]++;
    }

    int __ptr = 0;
    vector<int> oldToNew(g.nodect, -1);  // mapping from old community index to new ones
    for (int i = 0; i < g.nodect; i++) {
        if (communityCts[i] == 0) continue;
        oldToNew[i] = __ptr++;
    }

    int newNodect = __ptr;
    ret.nodect = newNodect;
    ret.nodes.assign(__ptr, Node());

    vector<vector<int>> combined(__ptr);
    for (int i = 0; i < g.nodect; i++) {
        int oldC = nodeToCommunity[i];
        int newC = oldToNew[oldC];

        combined[newC].push_back(i);
        for (auto k : g.nodes[i]) ret.nodes[newC].push_back(k);
    }
    using pii = pair<int, int>;
    map<pii, int> newedges;
    
    for (int i = 0; i < g.nodect; i++) {
        int icom = oldToNew[nodeToCommunity[i]];
        for (auto& [to, w] : g.adjLists[i]) {
            int tocom = oldToNew[nodeToCommunity[to]];
            newedges[{tocom, icom}] += w;
        }
    }

    ret.adjLists.assign(__ptr, vector<Edge>());

    for (auto& [k, v]: newedges) {
        auto& [from, to] = k;
        ret.adjLists[from].push_back({to, v});
        ret.totalEdgeWeight += v;
    }

    assert(ret.totalEdgeWeight == g.totalEdgeWeight);
    return ret;
}

inline void Partition::remove(int node, int edgesBetween, int degree, int selfEdges) {
    assert(node >= 0);
    assert(node < g.nodect);
    assert(edgesBetween >= 0);
    assert(degree >= 0);
    assert(selfEdges >= 0);

    int community = nodeToCommunity[node];

    sigmaIn[community] -= 2 * edgesBetween;
    sigmaIn[community] -= selfEdges;
    sigmaTot[community] -= degree;

    nodeToCommunity[node] = -1;

    assert(sigmaIn[community] >= 0);
    assert(sigmaTot[community] >= 0);
}

inline void Partition::add(int node, int community, int edgesBetween, int degree, int selfEdges) {
    assert(node >= 0);
    assert(node < g.nodect);
    assert(community >= 0);
    assert(edgesBetween >= 0);
    assert(nodeToCommunity[node] == -1);
    assert(degree >= 0);

    sigmaIn[community] += 2 * edgesBetween;
    sigmaIn[community] += selfEdges;
    sigmaTot[community] += degree;

    nodeToCommunity[node] = community;

    assert(sigmaIn[community] >= 0);
    assert(sigmaTot[community] >= 0);
}

#endif