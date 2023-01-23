#include "C:\Users\Nonce\Documents\VisualStudioCode\Lesson\Algorithms\lib.cpp"
#include <algorithm>
#include <random>
using namespace std;

class Graph {
    public:
    int V;
    int E;
    vector<vector<int>> adj;
    Graph(int V) : V(V), E(0), adj(V, vector<int>()) {}
    void addEdge(int i, int j) {
        adj[i].push_back(j);
        adj[j].push_back(i);
        E++;
    }
    int degree(int i) {
        return adj[i].size();
    }
    int maxDegree() {
        int max = 0;
        for(auto c : adj)
            max = std::max(max, (int) c.size());
        return max;
    }
    double averageDegree() {
        return 2.0 * E / V;
    }
    int numberSelfLoop() {
        int num = 0;
        for(int i = 0; i < V; i++)
            for(auto j : adj[i])
                if(i == j)
                    num++;
        return num / 2;
    }
};

class Digraph {
    public:
    int V;
    int E;
    vector<vector<int>> adj;
    Digraph(int V) : V(V), E(0), adj(V, vector<int>()) {}
    void addEdge(int i, int j) {
        adj[i].push_back(j);
        E++;
    }
    Digraph reverse() {
        Digraph ans(V);
        for(int i = 0; i < V; i++)
            for(auto j : adj[i])
                ans.addEdge(j, i);
        return ans;
    }
};

class Edge {
    public:
    int v;
    int w;
    double weight;
    Edge(int v, int w, double weight) : v(v), w(w), weight(weight) {}
    Edge() {}
    int either() {
        return v;
    }
    int other(int i) {
        if(i == v)
            return w;
        else if(i == w)
            return v;
        else
            throw;
    }
};

bool operator<(Edge a, Edge b) {
    return a.weight < b.weight;
}

bool operator>(Edge a, Edge b) {
    return a.weight > b.weight;
}

bool operator<=(Edge a, Edge b) {
    return a.weight <= b.weight;
}

bool operator>=(Edge a, Edge b) {
    return a.weight >= b.weight;
}

class EdgeGraph {
    public:
    int V;
    int E;
    vector<vector<Edge>> adj;
    EdgeGraph(int V) : V(V), E(0), adj(V, vector<Edge>()) {}
    void addEdge(int v, int w, double weight) {
        adj[v].push_back(Edge(v, w, weight));
        adj[w].push_back(Edge(w, v, weight));
        E++;
    }
    void addEdge(Edge e){
        int v = e.either();
        int w = e.other(v);
        adj[v].push_back(Edge(v, w, e.weight));
        adj[w].push_back(Edge(w, v, e.weight));
        E++;
    }
};

ostream& operator<<(ostream &os, Graph &g) {
    for(int i = 0; i < g.V; i++) {
        cout << i << " : ";
        for(auto j : g.adj[i])
            cout << j << ' ';
        cout << '\n';
    }
    return os;
}

ostream& operator<<(ostream &os, Digraph &g) {
    for(int i = 0; i < g.V; i++) {
        cout << i << " : ";
        for(auto j : g.adj[i])
            cout << j << ' ';
        cout << '\n';
    }
    return os;
}