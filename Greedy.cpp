#include "Greedy.h"

Greedy::Greedy(Graph g) {
    graph = g;
    num_nodes = graph.adj_list.size();
}

int Greedy::BFS(int src, int dst, vector<int> &par, vector<int> &par_id) {
    par.clear(), par_id.clear();
    par.resize(num_nodes, -1);
    par_id.resize(num_nodes, -1);
    vector<bool> visited(num_nodes, false);
    vector<int> dist(num_nodes, -1);
    
    queue<int> que;
    que.push(src);
    visited[src] = true;
    dist[src] = 0;
    par[src] = -1;
    par_id[src] = -1;
    while(!que.empty()) {
        int frt_node = que.front();
        que.pop();
        for(int i = 0; i < (int)graph.adj_list[frt_node].size(); i++) {
            Edge &e = graph.adj_list[frt_node][i];
            if(e.capacity <= 0) continue;
            if(!visited[e.to]) {
                visited[e.to] = true;
                que.push(e.to);
                par[e.to] = frt_node;
                par_id[e.to] = i;
                dist[e.to] = dist[frt_node] + 1; 
            }
        }
    }

    return dist[dst];
}

ll Greedy::shortest_flow() {
    ll shortest_distance = INF;
    vector<int> shorest_par_id, shorest_par;
    SDpair shorest_sdpair;
    for(auto [src, dst] : graph.sdpairs) {
        vector<int> par, par_id;
        int dist = BFS(src, dst, par, par_id);
        if(dist == -1) continue;
        if(shortest_distance > dist) {
            shortest_distance = dist;
            shorest_par_id = par_id;
            shorest_par = par;
            shorest_sdpair = {src, dst};
        }
    }

    if(shortest_distance == INF) return 0;


    int src = shorest_sdpair.first;
    int dst = shorest_sdpair.second;
    vector<int> &par = shorest_par, &par_id = shorest_par_id;

    ll mi_flow = INF;
    for(int i = dst; i != src; i = par[i]) {
        mi_flow = min(mi_flow, graph.adj_list[par[i]][par_id[i]].capacity);
    }

    for(int i = dst; i != src; i = par[i]) {
        Edge &e = graph.adj_list[par[i]][par_id[i]];
        e.capacity -= mi_flow;
    }

    // cerr << shortest_distance << endl;
    return mi_flow;
}


ll Greedy::solve() {
    ll tmp, res = 0;
    while((tmp = shortest_flow()) > 0) {
        res += tmp;
    }
    return res;
}