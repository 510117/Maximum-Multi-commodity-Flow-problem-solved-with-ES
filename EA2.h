#ifndef __EA2_H
#define __EA2_H

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")

#include "Graph.h"

class Individual2 {
public:
    map<pair<SDpair, E2EEdge>, double> f;
    map<SDpair, vector<E2EEdge>> sdpairs_usededges;
    Graph graph;
    int num_nodes;
    Individual2();
    Individual2(Graph g, map<SDpair, vector<E2EEdge>> &_sdpairs_usededges);
    map<pair<SDpair, E2EEdge>, double> make_feasible();
    void mutation();
    ll fitness();
};

class EA2 {
public:
    Individual2 individual;
    map<SDpair, vector<E2EEdge>> sdpairs_usededges;
    Graph graph;
    void DFS(int cur, vector<bool> &visited, SDpair &sdpair);
    EA2(Graph g);
    ll one_plus_one(int epochs);
};

#endif
