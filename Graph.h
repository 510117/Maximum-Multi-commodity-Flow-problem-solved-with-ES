#ifndef __GRAPH_H
#define __GRAPH_H

#include "config.h"


ll randint(ll start, ll end);

// input "prob" in range 0~100;
bool Rand_Prob(ll prob);

class Edge{
public:
    ll capacity, to;
    Edge(ll _capacity, ll _to);
};

class E2EEdge {
public:
    ll from, to, capacity;
    E2EEdge();
    E2EEdge(ll _from, ll _to, ll _capacity);

    bool operator < (const E2EEdge &l) const;

    bool operator == (const E2EEdge &l) const;
};

class Graph {
public: 
    vector<vector<Edge>> adj_list;
    vector<SDpair> sdpairs;
    // 左關右開 => [inv_s, inv_t)
    int inv_s, inv_t;
    /*
        'pair_num' number of source-sink pair
        'n' is number of internal node
        n should be greater than 2.
    */
    Graph();
    Graph(int pair_num, int n, int capacity_limit);
};

#endif