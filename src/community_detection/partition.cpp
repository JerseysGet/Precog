#include "partition.hpp"

#include <cassert>
#include <chrono>
#include <random>
#include <algorithm>



double Partition::gain(int node, int community, int edgesBetween, int degree) {
    assert(node >= 0);
    assert(community >= 0);
    assert(edgesBetween >= 0);
    assert(degree >= 0);
    assert(nodeToCommunity[node] == -1);

    return edgesBetween - sigmaTot[community] * degree / (0.0L + g.totalEdgeWeight); 
}