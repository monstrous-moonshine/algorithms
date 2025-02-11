#include "graph.h"
#include "UnionFind.h"
#include <iostream>
#include <queue>
#include <vector>
struct KruskalMST {
    std::vector<Edge> mst;
    KruskalMST(const EdgeWeightedGraph &graph) {
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
        for (auto &&e : graph.edges) pq.push(e);
        UnionFind uf(graph.V);
        while (!pq.empty() && mst.size() < graph.V - 1) {
            auto e = pq.top();
            pq.pop();
            if (uf.connected(e.u, e.v)) continue;
            uf.join(e.u, e.v);
            mst.push_back(e);
        }
    }
};
int main() {
    auto graph = EdgeWeightedGraph::from(std::cin);
    KruskalMST mst(graph);
    for (auto [u, v, w] : mst.mst) {
        printf("%d %d %.2f\n", u, v, w);
    }
}
