#include "graph_lib.cpp"
#include <deque>
#include <ios>
#include <vector>
using namespace std;

class DepthFirstSearch {
    public:
    vector<int> marked;
    int count;
    void operator()(Digraph g, int i = 0) {
        marked = vector<int>(g.V, 0);
        count = 0;
        dfs(g, i);
    }
    void dfs(Digraph g, int i) {
        marked[i] = 1;
        count++;
        for(auto c : g.adj[i])
            if(!marked[c])
                dfs(g, c);
    }
}DFS;

class BreadthFirstPath {
    public:
    vector<int> marked;
    vector<int> edgeTo;
    int start;
    void operator()(Digraph g, int i = 0) {
        marked = vector<int>(g.V, 0);
        edgeTo = vector<int>(g.V, -1);
        start = i;
        marked[i] = 1;
        bfs(g); 
    }
    void bfs(Digraph g) {
        deque<int> dq;
        dq.push_back(start);
        while(dq.size()) {
            int curr = dq[0];
            dq.pop_front();
            for(auto next : g.adj[curr])
                if(!marked[next]) {
                    marked[next] = 1;
                    edgeTo[next] = curr;
                    dq.push_back(next);
                }
        }
    }
    bool hasPathTo(int i) {
        return marked[i];
    }
    deque<int> pathTo(int i) {
        deque<int> ans;
        for(; edgeTo[i] != -1; i = edgeTo[i])
            ans.push_front(i);
        ans.push_front(start);
        return ans;
    }
    void prt() {
        for(int i = 0; i < marked.size(); i++)
            if(hasPathTo(i))
                cout << i << " : " << pathTo(i);
    }
}BFP;

class DirectedCycle {
    public:
    vector<int> marked;
    vector<int> edgeTo;
    vector<int> onStack;
    stack<int> cycle;
    bool hasCycle() {
        return !cycle.empty();
    }
    bool operator()(Digraph g, int i = 0) {
        marked = vector<int>(g.V, 0);
        edgeTo = vector<int>(g.V, -1);
        onStack = vector<int>(g.V, 0);
        cycle = stack<int>();
        for(int j = 0; j < g.V; j++)
            if(!marked[j])
                dfs(g, j);
        return hasCycle();
    }
    void dfs(Digraph g, int curr) {
        onStack[curr] = 1;
        marked[curr] = 1;
        for(auto next : g.adj[curr]) {
            if(hasCycle())
                return;
            else if(!marked[next]) {
                edgeTo[next] = curr;
                dfs(g, next);
            } else if(onStack[next]) {
                for(int i = curr; i != next; i = edgeTo[i])
                    cycle.push(i);
                cycle.push(next);
                cycle.push(curr);
                return;
            }
        }
        onStack[curr] = 0;
    }
}hasDirectedCycle;

class Topological {
    public:
    vector<int> marked;
    stack<int> ans;
    stack<int> operator()(Digraph g) {
        marked = vector<int>(g.V, 0);
        ans = stack<int>();
        for(int i = 0; i < g.V; i++)
            if(!marked[i])
                dfs(g, i);
        return ans;
    }
    void dfs(Digraph g, int i) {
        marked[i] = 1;
        for(auto c : g.adj[i])
            if(!marked[c])
                dfs(g, c);
        ans.push(i);
    }
}topological;

class KosarajuSCC {
    public:
    vector<int> marked;
    vector<int> id;
    int count;
    void operator()(Digraph g) {
        marked = vector<int>(g.V, 0);
        id = vector<int>(g.V, -1);
        count = 0;
        stack<int> reverse = topological(g.reverse());
        while(reverse.size()) {
            int tmp = reverse.top();
            reverse.pop();
            if(!marked[tmp]) {
                dfs(g, tmp);
                count++;
            }
        }
    }
    void dfs(Digraph g, int i) {
        marked[i] = 1;
        id[i] = count;
        for(auto c : g.adj[i])
            if(!marked[c])
                dfs(g, c);
    }
    bool isConnected(int p, int q) {
        return id[p] == id[q];
    }
}SCC;

int main() {

    cout << boolalpha;

    Digraph g(13);
    g.addEdge(0, 1);
    g.addEdge(0, 5);
    g.addEdge(5, 4);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 5);
    g.addEdge(0, 6);
    g.addEdge(6, 4);
    g.addEdge(8, 7);
    g.addEdge(7, 6);
    g.addEdge(6, 9);
    g.addEdge(9, 10);
    g.addEdge(9, 12);
    g.addEdge(9, 11);
    g.addEdge(11, 12);
//
    g.addEdge(3, 2);
    g.addEdge(7, 8);


    cout << g;

    // DFS(g);
    // cout << DFS.marked;
    // cout << DFS.count << '\n';

    // BFP(g);
    // BFP.prt();

    cout << hasDirectedCycle(g) << '\n';
    cout << hasDirectedCycle.cycle;

    cout << topological(g);
    
    SCC(g);
    cout << SCC.id;

    return 0;

}