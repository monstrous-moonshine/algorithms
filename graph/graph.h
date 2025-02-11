#include <istream>
#include <vector>

struct Digraph {
    int V, E{};
    std::vector<std::vector<int>> adj;
    Digraph(int v) : V(v), adj(v) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        E++;
    }
    static Digraph from(std::istream &is) {
        int V, E;
        is >> V >> E;
        Digraph out(V);
        for (int i = 0; i < E; i++) {
            int u, v;
            is >> u >> v;
            out.addEdge(u, v);
        }
        return out;
    }
    Digraph reverse() const {
        Digraph out(V);
        for (int u = 0; u < V; u++) {
            for (auto &&v : adj[u]) {
                out.addEdge(v, u);
            }
        }
        return out;
    }
};

struct Edge {
    int u, v;
    float weight;
    bool operator>(const Edge &that) const { return weight > that.weight; }
};
struct EdgeWeightedGraph {
    int V, E{};
    std::vector<std::vector<Edge>> adj;
    std::vector<Edge> edges;
    EdgeWeightedGraph(int v) : V(v), adj(v) {}
    void addEdge(int u, int v, float w) {
        adj[u].push_back({u, v, w});
        adj[v].push_back({v, u, w});
        edges.push_back({u, v, w});
        E++;
    }
    static EdgeWeightedGraph from(std::istream &is) {
        int V, E;
        is >> V >> E;
        EdgeWeightedGraph out(V);
        for (int i = 0; i < E; i++) {
            int u, v;
            float w;
            is >> u >> v >> w;
            out.addEdge(u, v, w);
        }
        return out;
    }
};
