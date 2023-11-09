#include "graph_lib.cpp"
#include <random>
using namespace std;

class DepthFirstSearch {
    public:
    vector<int> marked;
    int count;
    void operator()(Graph g, int i = 0) {
        marked = vector<int>(g.V, 0);
        dfs(g, 0);
    }
    void dfs(Graph g, int i) {
        marked[i] = 1;
        count++;
        for(auto c : g.adj[i])
            if(!marked[c])
                dfs(g, c);
    }
}DFS;

class DepthFirstSearchIterate {
    public:
    vector<int> marked;
    stack<int> st;
    int count;
    void operator()(Graph g, int i = 0) {
        marked = vector<int>(g.V, 0);
        st = stack<int>({i});
        marked[i] = 1;
        int tmp;
        while(!st.empty()) {
            tmp = st.top();
            st.pop();
            count++;
            for(auto c : g.adj[tmp])
                if(!marked[c]) {
                    st.push(c);
                    marked[c] = 1;
                }
        }
    }

}DFSI;

class DepthFirstPath {
    public:
    vector<int> marked;
    vector<int> edgeTo;
    int s;
    void operator()(Graph g, int i = 0) {
        marked = vector<int>(g.V, 0);
        edgeTo = vector<int>(g.V, -1);
        s = i;
        dfs(g, i); 
    }
    void dfs(Graph g, int i) {
        marked[i] = 1;
        for(auto c : g.adj[i])
            if(!marked[c]) {
                edgeTo[c] = i;
                dfs(g, c);
            }
    }
    bool hasPathTo(int i) {
        return marked[i];
    }
    deque<int> pathTo(int i) {
        deque<int> ans;
        for(; edgeTo[i] != -1; i = edgeTo[i])
            ans.push_front(i);
        ans.push_front(s);
        return ans;
    }
    void prt() {
        for(int i = 0; i < marked.size(); i++)
            if(hasPathTo(i))
                cout << i << " : " << pathTo(i);
    }
    // void prt() {
    //     stack<int> st;
    //     int tmp;
    //     for(int i = 0; i < marked.size(); i++) {
    //         st = stack<int>();
    //         for(int j = i; edgeTo[j] != -1; j = edgeTo[j])
    //             st.push(j);
    //         if(!st.size())
    //             continue;
    //         cout << i << " : " << s;
    //         while(st.size()) {
    //             tmp = st.top();
    //             st.pop();
    //             cout << '-' << tmp;
    //         }
    //         cout << '\n';
    //     }
    // }
}DFP;

class BreadthFirstPaths {
    public:
    vector<int> marked;
    vector<int> edgeTo;
    int start;
    void operator()(Graph g, int i = 0) {
        marked = vector<int>(g.V, 0);
        edgeTo = vector<int>(g.V, -1);
        start = i;
        bfs(g, i);
    }
    void bfs(Graph g, int i) {
        deque<int> dq;
        dq.push_back(i);
        marked[i] = 1;
        while(dq.size()) {
            int v = dq[0];
            dq.pop_front();
            for(auto c : g.adj[v])
                if(!marked[c]) {
                    edgeTo[c] = v;
                    marked[c] = 1;
                    dq.push_back(c);
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

class ConnectedComponent {
    public:
    vector<int> id;
    vector<int> marked;
    int count;
    void operator()(Graph g) {
        id = vector<int>(g.V, -1);
        marked = vector<int>(g.V, 0);
        count = 0;
        for(int i = 0; i < g.V; i++)
            if(!marked[i]) {
                dfs(g, i);
                count++;
            }
    }
    void dfs(Graph g, int i) {
        marked[i] = 1;
        id[i] = count;
        for(auto c : g.adj[i])
            if(!marked[c])
                dfs(g, c);
    }
    bool isConnected(int p, int q) {
        return id[p] == id[q];
    }
}CC;

class HasCycle {
    public:
    vector<int> marked;
    bool flag;
    bool operator()(Graph g) {
        marked = vector<int>(g.V, 0);
        for(int i = 0; i < g.V; i++)
            if(!marked[i])
                dfs(g, i, i);
        return flag;
    }
    void dfs(Graph g, int curr, int prev) {
        marked[curr] = 1;
        for(auto next : g.adj[curr]) {
            if(!marked[next])
                dfs(g, next, curr);
            else if(next != prev)
                flag = true;
        }
    }
}hasCycle;

class IsTwoColor {
    public:
    vector<int> marked;
    vector<int> color;
    bool flag;
    bool operator()(Graph g, int i = 0) {
        marked = vector<int>(g.V, 0);
        color = vector<int>(g.V, -1);
        flag = true;
        color[i] = 0;
        for(int i = 0; i < g.V; i++)
            if(!marked[i])
                dfs(g, i);
        return flag;
    }
    void dfs(Graph g, int i) {
        marked[i] = 1;
        for(auto c : g.adj[i])
            if(!marked[c]) {
                color[c] = !color[i];
                dfs(g, c);
            } else if(color[c] == color[i])
                flag = false;
    }
}isTwoColor;

int main() {

    cout << boolalpha;

    Graph g(15);
    g.addEdge(0, 1);
    g.addEdge(5, 6);


    cout << g;
    
    DFSI(g);
    cout << DFSI.marked;
    cout << DFSI.count << "\n\n";

    DFSI(g);
    cout << DFSI.marked;
    cout << DFSI.count << "\n\n";

    DFP(g);
    DFP.prt();

    BFP(g);
    BFP.prt();

    CC(g);
    cout << CC.id;
    
    cout << hasCycle(g) << '\n';

    cout << isTwoColor(g);

    return 0;

}