#ifndef __EA_H
#define __EA_H

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")

#include "Graph.h"

class Individual {
public:
    map<pair<SDpair, E2EEdge>, double> f;
    map<SDpair, vector<E2EEdge>> sdpairs_usededges;
    Graph graph;
    int num_nodes;
    Individual();
    Individual(Graph g, map<SDpair, vector<E2EEdge>> &_sdpairs_usededges);
    map<pair<SDpair, E2EEdge>, double> make_feasible();
    vector<E2EEdge> find_random_path(int src, int dst);
    void DFS_rand(int cur, vector<bool> &visited, vector<int> &par, vector<int> &par_id);
    void mutation();
    ll fitness();
};

class EA {
public:
    Individual individual;
    map<SDpair, vector<E2EEdge>> sdpairs_usededges;
    Graph graph;
    void DFS(int cur, vector<bool> &visited, SDpair &sdpair);
    EA(Graph g);
    ll one_plus_one(int epochs);
};

#endif
