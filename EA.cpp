#include "EA.h"


double Gaussian(double val) {
    double std_dev = 1.0;
    normal_distribution<double> distribution(0, std_dev);
    // cerr << val << " " << distribution(gen) << endl;
    return val * distribution(gen);
}

template <typename T>
class MaxFlow {
public:
    int n, s, t;
    MaxFlow(int _n, int src, int dst) : n(_n), s(src), t(dst) {
        adj.clear();
        adj.resize(n);
        level.clear();
        level.resize(n);
        iter.clear();
        iter.resize(n);
    }

    struct FlowEdge {
        int to; T cap; int rev;
        FlowEdge(){} // important
        FlowEdge(int _to, T _cap, int _rev) : to(_to), cap(_cap), rev(_rev) {}
    };
    vector<vector<FlowEdge>> adj;
    vector<int> level, iter;
    void add_edge(int from, int to, T cap) {
        adj[from].push_back(FlowEdge(to, cap, (int)adj[to].size()));
        adj[to].push_back(FlowEdge(from, 0, (int)adj[from].size() - 1));
    }
    void BFS() {
        for(int i = 0; i < n; i++) {
            level[i] = -1;
        }
        level[s] = 0;
        queue<int> q; 
        q.push(s);
        while(!q.empty()) {
            int frt = q.front();
            q.pop();
            for(auto e : adj[frt]) {
                if(e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[frt] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    T DFS(int now, T flow) {
        if(now == t) return flow;
        for(int &i = iter[now]; i < (int)adj[now].size(); i++) {// & is important for update iter[now]
            FlowEdge &e = adj[now][i];
            if(e.cap > 0 && level[e.to] == level[now] + 1) {
                T ret = DFS(e.to, min(flow, e.cap));
                if(ret > 0) {
                    e.cap -= ret;
                    adj[e.to][e.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    T solve() {
        T ret = 0;
        while(1) {
            BFS();
            if(level[t] == -1) break;
            for(int i = 0; i < n; i++) {
                iter[i] = 0;
            }
            T tmp;
            while((tmp = DFS(s, INF)) > 0)  {
                ret += tmp;
            }
        }
        return ret;
    }
};

Individual::Individual() {}
Individual::Individual(Graph g, map<SDpair, vector<E2EEdge>> &_sdpairs_usededges) {
    graph = g;
    num_nodes = graph.adj_list.size();
    sdpairs_usededges = _sdpairs_usededges;
    for(auto &[sdpair, E2Eedges] : sdpairs_usededges) {
        for(E2EEdge E2Eedge : E2Eedges) {
            // f[{sdpair, E2Eedge}] = randint(0, E2Eedge.capacity);
            f[{sdpair, E2Eedge}] = 0;
        }
    }
}

map<pair<SDpair, E2EEdge>, double> Individual::make_feasible() {
    map<pair<SDpair, E2EEdge>, double> newf = f;
    map<E2EEdge, double> flow_sum;
    for(auto &[sdpair, E2Eedges] : sdpairs_usededges) {
        for(E2EEdge E2Eedge : E2Eedges) {
            flow_sum[E2Eedge] += f[{sdpair, E2Eedge}];
        }
    }
    for(auto &[sdpair, E2Eedges] : sdpairs_usededges) {
        for(E2EEdge E2Eedge : E2Eedges) {
            if(flow_sum[E2Eedge] > EPS) {
                double ratio = min(1.0, E2Eedge.capacity / flow_sum[E2Eedge]);
                newf[{sdpair, E2Eedge}] *= ratio;
            }
        }
    }
    return newf;
}

// void Individual::mutation() {
//     for(auto &[sdpair, E2Eedges] : sdpairs_usededges) {
//         if(!Rand_Prob(100.0 / graph.sdpairs.size())) continue;
//         for(E2EEdge E2Eedge : E2Eedges) {
//             f[{sdpair, E2Eedge}] = min((double)E2Eedge.capacity, f[{sdpair, E2Eedge}] + Gaussian(E2Eedge.capacity));
//             f[{sdpair, E2Eedge}] = max((double)0, f[{sdpair, E2Eedge}] + Gaussian(E2Eedge.capacity));
//         }
//     }
// }


void Individual::DFS_rand(int cur, vector<bool> &visited, vector<int> &par, vector<int> &par_id) {
    visited[cur] = true;
    vector<pair<Edge, int>> rand_order;
    for(int i = 0; i < (int)graph.adj_list[cur].size(); i++) {
        rand_order.emplace_back(graph.adj_list[cur][i], i);
    }

    random_shuffle(rand_order.begin(), rand_order.end());

    for(auto [edge, i]  : rand_order) {
        if(!visited[edge.to] && edge.capacity > 0) {
            par[edge.to] = cur;
            par_id[edge.to] = i;
            DFS_rand(edge.to, visited, par, par_id);
        }
    }
}

vector<E2EEdge> Individual::find_random_path(int src, int dst) {
    vector<int> par(num_nodes), par_id(num_nodes);
    vector<bool> visited(num_nodes, false);
    DFS_rand(src, visited, par, par_id);

    assert(visited[dst]);

    vector<E2EEdge> edges;
    for(int i = dst; i != src; i = par[i]) {
        Edge e = graph.adj_list[par[i]][par_id[i]];
        edges.push_back(E2EEdge(par[e.to], e.to, e.capacity));
    }

    return edges;
}

void Individual::mutation() {
    for(auto &[sdpair, E2Eedges] : sdpairs_usededges) {
        if(!Rand_Prob(100.0 / graph.sdpairs.size())) continue;
        vector<E2EEdge> edges = find_random_path(sdpair.first, sdpair.second);
        for(E2EEdge E2Eedge : edges) {
            f[{sdpair, E2Eedge}] = min((double)E2Eedge.capacity, f[{sdpair, E2Eedge}] + Gaussian(E2Eedge.capacity));
            f[{sdpair, E2Eedge}] = max((double)0, f[{sdpair, E2Eedge}] + Gaussian(E2Eedge.capacity));
        }
    }
}

ll Individual::fitness() {
    if(debug) cerr << "make feasible\n";
    map<pair<SDpair, E2EEdge>, double> feasiablef = make_feasible();
    map<E2EEdge, int> amount;
    ll flow_sum = 0;
    if(debug) cerr << "max flow\n";
    for(auto [src, dst] : graph.sdpairs) {
        SDpair sdpair(src, dst);
        MaxFlow<int> maxflow(num_nodes, src, dst);
        for(E2EEdge E2Eedge : sdpairs_usededges[sdpair]) {
            if((int)feasiablef[{sdpair, E2Eedge}] > 0) {
                ll cap = (ll)floor(feasiablef[{sdpair, E2Eedge}]);
                maxflow.add_edge(E2Eedge.from, E2Eedge.to, cap);
                amount[E2Eedge] += cap;
                // cerr << amount[E2Eedge] << " " << E2Eedge.capacity << endl;
                assert((amount[E2Eedge] <= E2Eedge.capacity));
            }
        }

        flow_sum += maxflow.solve();
    }
    return flow_sum;
}

void EA::DFS(int cur, vector<bool> &visited, SDpair &sdpair) {
    visited[cur] = true;
    for(Edge edge : graph.adj_list[cur]) {
        sdpairs_usededges[sdpair].push_back(E2EEdge(cur, edge.to, edge.capacity));
        if(!visited[edge.to]) {
            DFS(edge.to, visited, sdpair);
        }
    }
}
EA::EA(Graph g) {
    graph = g;
    for(SDpair sdpair : graph.sdpairs) {
        sdpairs_usededges[sdpair];
        vector<bool> visited(graph.adj_list.size(), false);
        DFS(sdpair.first, visited, sdpair);
    }
    individual = Individual(g, sdpairs_usededges);
}
ll EA::one_plus_one(int epochs) {
    individual = Individual(graph, sdpairs_usededges);
    ll cur_fitness = individual.fitness();
    while(epochs--) {
        if(debug) cerr << epochs << endl;
        if(debug) cerr << "build child" << endl;
        Individual child = individual;
        if(debug) cerr << "mutation" << endl;
        child.mutation();
        if(debug) cerr << "compare" << endl;

        ll child_fitness = child.fitness();
        if(cur_fitness < child_fitness) {
            cur_fitness = child_fitness;
            individual = child;
        }
    }
    return individual.fitness();
}
