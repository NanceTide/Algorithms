#include "graph_lib.cpp"
#include <deque>
using namespace std;

template <typename T> class Heap {
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

class LazyPrimMST {
    public:
    vector<int> marked;
    deque<Edge> mst;
    Heap<Edge> heap;

    deque<Edge> operator()(EdgeGraph g)  {
        marked = vector<int>(g.V, 0);
        mst.clear();
        heap.vec.clear();
        heap.n = 0;
        // heap.vec.push_back(Edge(0, 0, 0));
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
}LPrim;

int main() {

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

    for(auto e : LPrim(g))
        cout << e.v << ' ' << e.w << ' ' << e.weight << '\n';
    
}