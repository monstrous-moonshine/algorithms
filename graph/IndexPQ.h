#include <vector>

template <typename T, typename Compare = std::less<T>>
struct IndexPQ {
    IndexPQ(int maxN) : keys(maxN), pq(maxN), qp(maxN, -1) {}
    void insert(int i, T key) {
        qp[i] = size_;
        pq[size_] = i;
        keys[size_] = key;
        swim(size_++);
    }
    void change(int i, T key) {
        keys[qp[i]] = key;
        swim(qp[i]);
        sink(qp[i]);
    }
    T top() const { return pq[0]; }
    void pop() {
        qp[pq[0]] = -1;
        pq[0] = pq[size_ - 1];
        keys[0] = keys[size_ - 1];
        qp[pq[0]] = 0;
        size_--;
        sink(0);
    }
    bool empty() const { return size_ == 0; }
    int size() const { return size_; }
    int count(int i) const { return qp[i] != -1; }
    T operator[](int i) const { return keys[qp[i]]; }
private:
    int size_{};
    std::vector<T> keys;
    std::vector<int> pq;
    std::vector<int> qp;
    void swim(int k) {
        while (k > 0 && compare((k-1)/2, k)) {
            swap((k-1)/2, k);
            k = (k-1)/2;
        }
    }
    void sink(int k) {
        while (2*k+1 <= size_) {
            int j = 2*k+1;
            if (j < size_ && compare(j, j+1)) j++;
            if (!compare(k, j)) break;
            swap(k, j);
            k = j;
        }
    }
    bool compare(int i, int j) {
        return Compare{}(keys[i], keys[j]);
    }
    void swap(int i, int j) {
        std::swap(keys[i], keys[j]);
        std::swap(pq[i], pq[j]);
        std::swap(qp[pq[i]], qp[pq[j]]);
    }
};
