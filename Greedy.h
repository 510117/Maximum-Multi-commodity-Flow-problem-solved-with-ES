#ifndef __GREEDY_H
#define __GREEDY_H

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")

#include "Graph.h"

class Greedy {
public:
    int num_nodes;
    Graph graph;
    int BFS(int src, int dst, vector<int> &par, vector<int> &par_id);
    ll shortest_flow();
    Greedy(Graph g);
    ll solve();
};

#endif
