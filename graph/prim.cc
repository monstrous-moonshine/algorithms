#include <cfloat>
#include <iostream>
#include <queue>
#include <vector>
#include "graph.h"
#include "IndexPQ.h"
struct LazyPrimMST {
    std::vector<Edge> mst;
    LazyPrimMST(const EdgeWeightedGraph &graph) : marked(graph.V) {
        visit(graph, 0);
        while (!pq.empty()) {
            auto e = pq.top();
            pq.pop();
            if (marked[e.v]) continue;
            mst.push_back(e);
            visit(graph, e.v);
        }
        if (mst.size() != graph.V - 1) {
            fprintf(stderr, "LazyPrimMST: too few edges in MST. Not connected?\n");
        }
    }
private:
    std::vector<bool> marked;
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    void visit(const EdgeWeightedGraph &graph, int v) {
        marked[v] = true;
        for (auto &&e : graph.adj[v]) {
            if (!marked[e.v]) pq.push(e);
        }
    }
};
struct PrimMST {
    std::vector<Edge> edgeTo;
    std::vector<float> distTo;
    PrimMST(const EdgeWeightedGraph &graph) : marked(graph.V), edgeTo(graph.V), distTo(graph.V, FLT_MAX), pq(graph.V) {
        distTo[0] = 0;
        pq.insert(0, 0);
        while (!pq.empty()) {
            int i = pq.top();
            pq.pop();
            visit(graph, i);
        }
    }
private:
    std::vector<bool> marked;
    IndexPQ<float, std::greater<float>> pq;
    void visit(const EdgeWeightedGraph &graph, int v) {
        marked[v] = true;
        for (auto &&e : graph.adj[v]) {
            if (marked[e.v]) continue;
            if (e.weight > distTo[e.v]) continue;
            edgeTo[e.v] = e;
            distTo[e.v] = e.weight;
            if (pq.count(e.v) != 0) pq.change(e.v, e.weight);
            else                    pq.insert(e.v, e.weight);
        }
    }
};
int main() {
    auto graph = EdgeWeightedGraph::from(std::cin);
    {
        LazyPrimMST mst(graph);
        for (auto [u, v, w] : mst.mst) {
            printf("%d %d %.2f\n", u, v, w);
        }
    }
    {
        PrimMST mst(graph);
        for (auto [u, v, w] : mst.edgeTo) {
            printf("%d %d %.2f\n", u, v, w);
        }
    }
}
