#include "graph.h"
#include "IndexPQ.h"
#include <algorithm>
#include <cfloat>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
struct LazyDijkstraSP {
    LazyDijkstraSP(const EdgeWeightedDigraph &graph, int src) : distTo(graph.V, FLT_MAX), pathTo_(graph.V) {
        std::priority_queue<QueueItem, std::vector<QueueItem>, std::greater<QueueItem>> pq;
        pq.push({src, -1, 0});
        while (!pq.empty()) {
            // This part of the loop runs E times, since each vertex adds all
            // its neighbors to the pq, and sum(degree(v)) = E. Actually, it
            // runs E+1 times since we add one item to the pq at the start.
            auto [v, u, d] = pq.top();
            pq.pop();
            // Ignore if ineligible
            if (d > distTo[v]) continue;
            // The rest of the loop runs exactly once for each vertex. We will
            // not later find a shorter path through another neighbor because:
            //
            // 1. We add vertices with increasing distance from the source, so
            //    any neighbor not already added to the tree is farther from
            //    the source than this one.
            // 2. Edge weights must be positive for the Dijkstra algorithm, so
            //    adding the edge weight from that neighbor to this one can't
            //    give a shorter path to the source.
            //
            // Hence any path through other neighbors discovered later will be
            // rejected by the check above.
            distTo[v] = d;
            pathTo_[v] = u;
            // In the lazy version, we indiscriminately add vertices to the pq
            // leaving the task of eliminating ineligible vertices to the check
            // above
            for (auto &&e : graph.adj[v])
                pq.push({e.v, v, d + e.weight});
        }
    }
    std::vector<int> pathTo(int dst) const {
        std::vector<int> out;
        while (pathTo_[dst] != -1) {
            out.push_back(dst);
            dst = pathTo_[dst];
        }
        std::reverse(out.begin(), out.end());
        return out;
    }
    std::vector<float> distTo;
private:
    std::vector<int>   pathTo_;
    struct QueueItem {
        int   vert;
        int   from;
        float dist;
        bool operator>(const QueueItem &that) const { return dist > that.dist; }
    };
};
struct DijkstraSP {
    DijkstraSP(const EdgeWeightedDigraph &graph, int src) : distTo(graph.V, FLT_MAX), pq(graph.V), pathTo_(graph.V) {
        distTo[src] = 0;
        pathTo_[src] = -1;
        pq.insert(src, 0);
        while (!pq.empty()) {
            auto v = pq.top();
            pq.pop();
            relax(graph, v);
        }
    }
    std::vector<int> pathTo(int dst) const {
        std::vector<int> out;
        while (pathTo_[dst] != -1) {
            out.push_back(dst);
            dst = pathTo_[dst];
        }
        std::reverse(out.begin(), out.end());
        return out;
    }
    std::vector<float> distTo;
private:
    std::vector<int>   pathTo_;
    IndexPQ<float, std::greater<float>> pq;
    void relax(const EdgeWeightedDigraph &graph, int v) {
        for (auto &&e : graph.adj[v]) {
            if (distTo[e.v] > distTo[v] + e.weight) {
                distTo[e.v] = distTo[v] + e.weight;
                pathTo_[e.v] = v;
                if (pq.count(e.v) != 0) pq.change(e.v, distTo[e.v]);
                else                    pq.insert(e.v, distTo[e.v]);
            }
        }
    }
};
int main(int argc, char *argv[]) {
    int src = argc < 2 ? 0 : atoi(argv[1]);
    auto graph = EdgeWeightedDigraph::from(std::cin);
    LazyDijkstraSP djk(graph, src);
    for (int i = 0; i < graph.V; i++) {
        printf("%d->%d %.2f ", src, i, djk.distTo[i]);
        printf("%d", src);
        for (auto &&v : djk.pathTo(i))
            printf("->%d", v);
        printf("\n");
    }
}
