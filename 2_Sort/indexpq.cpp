#include "sort_lib.cpp"
#include <algorithm>
using namespace std;

template <typename T> class IndexMinPQ {
    public:
    IndexMinPQ(int max_n) : 
        max_n(max_n), 
        n(0), 
        keys(max_n + 1), 
        pq(max_n + 1), 
        qp(max_n + 1, -1) {}
    
    bool contains(int i) {
        return qp[i] != -1;
    }
    void insert(int i, T key) {
        if(contains(i))
            throw;
        n++;
        keys[i] = key;
        pq[n] = i;
        qp[i] = n;
        swim(n);
    }
    int del_min() {
        if(n == 0)
            throw;
        int min_index = pq[1];
        exchange(1, n);
        n--;
        sink(1);
        qp[min_index] = -1;
        return min_index;
    }
    int size() {
        return n;
    }
    void change(int i, T key) {
        keys[i] = key;
        swim(qp[i]);
        sink(qp[i]);
    }
    void del(int i) {
        exchange(qp[i], n--);
        swim(qp[i]);
        sink(qp[i]);
        qp[i] = -1;
    }
    T min() {
        return keys[pq[1]];
    }

    private:
    int max_n;
    int n;
    vector<T> keys; // 元素的权重值
    vector<int> pq; // 优先队列
    vector<int> qp; // qp[i]代表索引值为i的元素在优先队列中的位置

    void exchange(int k, int j) { // k, j 是堆序列
        swap(pq[k], pq[j]);
        qp[pq[k]] = k;
        qp[pq[j]] = j;
    }
    void swim(int k) { // k 是堆序列
        for(; k > 1 && keys[pq[k]] < keys[pq[k / 2]]; k /= 2)
            exchange(k, k / 2);
    }
    void sink(int k) { // k 是堆序列
        for(int j = 2 * k; j <= n; k = j, j *= 2) {
            if(j + 1 <= n && keys[pq[j]] > keys[pq[j + 1]])
                j++;
            if(keys[pq[k]] < keys[pq[j]])
                break;
            exchange(k, j);
        }
    }

};

int main() {

    IndexMinPQ<int> pq(10);
    pq.insert(3, 5);
    pq.insert(7, 2);
    pq.insert(8, -1);
    pq.insert(1, 8);
    pq.insert(5, 6);
    pq.insert(9, 4);
    pq.insert(4, 7);
    pq.insert(6, 9);
    pq.insert(2, 1);
    pq.insert(0, 3);
    while(pq.size()) {
        cout << "min element: " << pq.min() << endl;
        pq.del_min();
    }

    cout << endl;
    pq.insert(3, 5);
    pq.insert(7, 2);
    pq.insert(8, -1);
    pq.insert(1, 8);
    pq.insert(5, 6);
    pq.insert(9, 4);
    pq.insert(4, 7);
    pq.insert(6, 9);
    pq.insert(2, 1);
    pq.insert(0, 3);
    pq.change(9, 100);
    while(pq.size()) {
        cout << "min element: " << pq.min() << endl;
        pq.del_min();
    }
    return 0;

}