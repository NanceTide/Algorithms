#include "graph_lib.cpp"
#include <deque>
#include <cfloat>
using namespace std;

template <typename T> class Heap { // 优先队列
    public:
    vector<T> vec;
    int n;
    Heap() : vec(), n(0) {vec.push_back(T());}
    void sink(int k) {
        for(int j = k << 1; j <= n; k = j, j <<= 1) {
            if(j < n && vec[j] > vec[j + 1])
                j++;
            if(vec[j] > vec[k])
                return;
            swap(vec[k], vec[j]);
        }
    }
    void swim(int k) {
        for(; k > 1 && vec[k] < vec[k >> 1]; k >>= 1)
            swap(vec[k], vec[k >> 1]);
    }
    void insert(T num) {
        vec.push_back(num);
        n++;
        swim(n);
    }
    T delMin() {
        T min = vec[1];
        vec[1] = vec[n];
        vec.pop_back();
        n--;
        sink(1);
        return min;
    }
    T min() {
        return vec[1];
    }
    void clear(T t) {
        vec.clear();
        n = 0;
        vec.push_back(t);
    }
};

template <typename T> class IndexHeap { // 索引优先队列
    public:
    vector<T> keys;
    vector<int> pq;
    vector<int> qp;
    int n;
    IndexHeap(int capacity) : keys(capacity + 1), pq(capacity + 1, -1), qp(capacity + 1, -1), n(0) {}
    IndexHeap() {}
    void exch(int i, int j) { // public
        swap(pq[i], pq[j]);
        qp[pq[i]] = i;
        qp[pq[j]] = j;
    }
    bool contains(int k) {
        return qp[k] != -1;
    }
    void insert(int k, T t) {
        if(contains(k))
            return;
        n++;
        keys[k] = t;
        pq[n] = k;
        qp[k] = n;
        swim(n);
    }
    int delMin() {
        int minIndex = pq[1];
        exch(1, n);
        qp[pq[n]] = -1;
        pq[n] = -1;
        n--;
        sink(1);
        return minIndex;
    }
    T operator[](int k) {
        if(!contains(k))
            throw;
        return keys[k];
    }
    T& min() {
        return keys[pq[1]];
    }
    void del(int k) {
        int index = qp[k];
        exch(k, n);
        qp[pq[n]] = -1;
        pq[n] = -1;
        n--;
        sink(k);
        swim(k);
    }
    void change(int k, T t) {
        keys[k] = t;
        swim(qp[k]);
        sink(qp[k]);
    }
    void sink(int k) {
        for(int j = k << 1; j <= n; k = j, j <<= 1) {
            if(j + 1 <= n && keys[pq[j]] > keys[pq[j + 1]])
                j++;
            if(keys[pq[k]] < keys[pq[j]])
                return;
            exch(k, j);
        }
    }
    void swim(int k) {
        for(; k > 1 && keys[pq[k >> 1]] > keys[pq[k]]; k >>= 1)
            exch(k >> 1, k);
    }
};

class LazyPrimMST {
    public:
    vector<int> marked;
    deque<Edge> mst;
    Heap<Edge> heap;
    deque<Edge> operator()(EdgeGraph g)  {
        marked = vector<int>(g.V, 0);
        mst.clear();
        heap.clear(Edge());
        visit(g, 0);
        while(heap.n) {
            Edge tmp = heap.delMin();
            int v = tmp.either();
            int w = tmp.other(v);
            if(marked[v] && marked[w])
                continue;
            mst.push_back(tmp);
            if(!marked[v])
                visit(g, v);
            if(!marked[w])
                visit(g, w);
        }
        return mst;
    }
    void visit(EdgeGraph g, int i) {
        marked[i] = 1;
        for(Edge c : g.adj[i])
            if(!marked[c.other(i)])
                heap.insert(c);
    }
}lazyPrim;

class PrimMST {
    public:
    vector<Edge> edgeTo;
    vector<double> distTo;
    vector<int> marked;
    IndexHeap<double> pq;
    vector<Edge> operator()(EdgeGraph g) {
        edgeTo = vector<Edge>(g.V, Edge(0, 0, 0.0));
        distTo = vector<double>(g.V, DBL_MAX);
        marked = vector<int>(g.V, 0);
        pq = IndexHeap<double>(g.V);
        distTo[0] = 0.0;
        pq.insert(0, 0.0);
        while(pq.n)
            visit(g, pq.delMin());
        return edgeTo;
    }
    void visit(EdgeGraph g, int i) {
        marked[i] = 1;
        for(Edge e : g.adj[i]) {
            int w = e.other(i);
            if(marked[w])
                continue;
            if(e.weight < distTo[w]) {
                edgeTo[w] = e;
                distTo[w] = e.weight;
                if(pq.contains(w))
                    pq.change(w, e.weight);
                else
                    pq.insert(w, e.weight);
            }
        }
    }
}prim;

int main() {

    ios::sync_with_stdio(false);
    int V, E;
    cin >> V >> E;
    int v, w;
    double weight;
    EdgeGraph g(V);
    for(int e = 0; e < E; e++) {
        cin >> v >> w >> weight;
        g.addEdge(v, w, weight);
    }

    cout << '\n';

    for(auto e : prim(g))
        cout << e.v << ' ' << e.w << ' ' << e.weight << '\n';

}
