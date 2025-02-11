#include <vector>
struct UnionFind {
    UnionFind(int n) : count_(n), id(n), sz(n, 1) {
        for (int i = 0; i < n; i++) id[i] = i;
    }
    void join(int p, int q) {
        int i = find(p);
        int j = find(q);
        if (i == j) return;
        if (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i]; }
        else               { id[j] = i; sz[i] += sz[j]; }
        count_--;
    }
    int find(int p) const {
        while (id[p] != p) p = id[p];
        return p;
    }
    bool connected(int p, int q) const { return find(p) == find(q); }
    int count() const { return count_; }
private:
    int count_;
    std::vector<int> id;
    std::vector<int> sz;
};
