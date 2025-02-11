#include "graph.h"
#include <iostream>
#include <vector>
struct DepthFirstOrder {
    DepthFirstOrder(const Digraph &graph) : marked(graph.V) {
        for (int v = 0; v < graph.V; v++)
            if (!marked[v]) dfs(graph, v);
    }
    void dfs(const Digraph &graph, int node) {
        marked[node] = true;
        for (auto &&v : graph.adj[node])
            if (!marked[v])
                dfs(graph, v);
        postorder.push_back(node);
    }
    std::vector<int> postorder;
private:
    std::vector<bool> marked;
};
struct KosarajuSharirSCC {
    KosarajuSharirSCC(const Digraph &graph) : marked(graph.V), id(graph.V) {
        DepthFirstOrder order(graph.reverse());
        auto postorder = order.postorder;
        while (!postorder.empty()) {
            auto node = postorder.back();
            postorder.pop_back();
            if (!marked[node]) {
                dfs(graph, node);
                count++;
            }
        }
    }
    std::vector<int> id;
    int count{};
private:
    std::vector<bool> marked;
    void dfs(const Digraph &graph, int node) {
        marked[node] = true;
        id[node] = count;
        for (auto &&v : graph.adj[node])
            if (!marked[v])
                dfs(graph, v);
    }
};
int main() {
    auto graph = Digraph::from(std::cin);
    KosarajuSharirSCC scc(graph);
    std::vector<std::vector<int>> components(scc.count);
    for (int i = 0; i < graph.V; i++)
        components[scc.id[i]].push_back(i);
    for (auto &&c : components) {
        for (auto &&i : c) std::cout << i << " ";
        std::cout<< "\n";
    }
}
