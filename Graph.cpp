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
    adj_list.resize(n);



    vector<int> pru_seq, cnt(n, 0);
    for(int i = 0; i < n - 2; i++) {
        int node = randint(0, n - 1);
        pru_seq.push_back(node);
    }
    set<int> leaf;
    for(int i = 0; i < n; i++) {
        leaf.insert(i);
    }
    for(int i = 0; i < n - 2; i++) {
        leaf.erase(pru_seq[i]);
        cnt[pru_seq[i]]++;
    }

    vector<set<int>> adj_set(n);
    for(int i = 0; i < n - 2; i++) {
        auto mi = leaf.begin();
        adj_list[pru_seq[i]].emplace_back(randint(1, capacity_limit), *mi);
        adj_list[*mi].emplace_back(randint(1, capacity_limit), pru_seq[i]);

        adj_set[pru_seq[i]].insert(*mi);
        adj_set[*mi].insert(pru_seq[i]);

        leaf.erase(mi);
        cnt[pru_seq[i]]--;
        if(cnt[pru_seq[i]] == 0) {
            leaf.insert(pru_seq[i]);
        }
    }

    adj_list[*next(leaf.begin())].emplace_back(randint(1, capacity_limit), *leaf.begin());
    adj_list[*leaf.begin()].emplace_back(randint(1, capacity_limit), *next(leaf.begin()));
    adj_set[*next(leaf.begin())].insert(*leaf.begin());
    adj_set[*leaf.begin()].insert(*next(leaf.begin()));


    int rand_edges = n / 10;

    for(int i = 0; i < rand_edges; i++) {
        int u = randint(0, n - 1);
        int v = randint(0, n - 1);
        if(u != v && !adj_set[u].count(v)) {
            adj_list[u].emplace_back(randint(1, capacity_limit), v);
            adj_list[v].emplace_back(randint(1, capacity_limit), u);

            adj_set[u].insert(v);
            adj_set[v].insert(u);
        }
    }

    vector<SDpair> all_pairs;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(adj_set[i].count(j) == 0 && i != j) all_pairs.emplace_back(i, j);
        }
    }

    random_shuffle(all_pairs.begin(), all_pairs.end());
    for(int i = 0; i < min((int)all_pairs.size(), pair_num); i++) {
        sdpairs.emplace_back(all_pairs[i]);
    }
}