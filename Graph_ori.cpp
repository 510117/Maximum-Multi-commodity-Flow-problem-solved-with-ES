#include "Graph.h"

ll randint(ll start, ll end) {
    return (unif(gen) % (end - start + 1)) + start;
}

// input "prob" in range 0~100;
bool Rand_Prob(ll prob){
    ll r = (rand()%100);
    if(r < prob) 
        return true;
    return false; 
}

Edge::Edge(ll _capacity, ll _to){
    this->capacity = _capacity;
    this->to = _to;
}

E2EEdge::E2EEdge() {}
E2EEdge::E2EEdge(ll _from, ll _to, ll _capacity) : from(_from), to(_to), capacity(_capacity) {}
bool E2EEdge::operator < (const E2EEdge &l) const {
    return array<ll, 3>{from, to, capacity} < array<ll, 3>{l.from, l.to, l.capacity};
}

bool E2EEdge::operator == (const E2EEdge &l) const {
    return array<ll, 3>{from, to, capacity} == array<ll, 3>{l.from, l.to, l.capacity};
}


Graph::Graph() {}
Graph::Graph(int pair_num, int n, int capacity_limit){
    if(n < 2)
        throw overflow_error("Input n for graph is too small.");
    srand(time(NULL) * clock());
    // list_size = n+2*pair_num;
    adj_list.resize(list_size);
    inv_s = pair_num, inv_t = pair_num + n;
    for(int i = 0; i < pair_num; ++i)
        sdpairs.push_back({i, i + n + pair_num});
    
    // randomly create edges between 2 interval nodes.
    for(int i = inv_s; i < inv_t; ++i)
    {
        for(int j = i+1; j < inv_t; ++j){
            if(Rand_Prob(30))
                adj_list[i].emplace_back(randint(1, capacity_limit), j);
        }
    }
    // randomly assert source to interval node.
    vector<bool> source_connected(pair_num, false);
    for(int i = 0; i < pair_num; ++i){
        for(int j = inv_s; j < inv_s + n/2; ++j){
            int prob = static_cast<int>(max(10.0, 100.0 * (1.0)/(n/2)));
            if(Rand_Prob(prob)){
                source_connected[i] = true;
                adj_list[i].emplace_back(randint(1, capacity_limit), j);
            }
        }
    }
    for(int i = 0; i < pair_num; ++i){
        if(!source_connected[i]){
            adj_list[i].emplace_back(randint(1, capacity_limit), rand()%(n/2) + inv_s);
        }
    }

    // randomly assert interval node to sink.
    vector<bool> sink_connected(pair_num, false);
    for(int i = 0; i < pair_num; ++i){
        for(int j = inv_s + n/2; j < inv_t; ++j){
            int prob = static_cast<int>(max(10.0, 100.0 * (1.0)/(n/2)));
            if(Rand_Prob(prob)){
                sink_connected[i] = true;
                adj_list[j].emplace_back(randint(1, capacity_limit), i+inv_t);
            }
        }
    }
    for(int i = 0; i < pair_num; ++i){
        if(!sink_connected[i]){
            adj_list[rand()%(n/2) + inv_s + n/2].emplace_back(randint(1, capacity_limit), i+inv_t);
        }
    }
}