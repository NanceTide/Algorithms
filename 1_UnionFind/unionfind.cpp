#include "C:\Users\Nonce\Documents\VisualStudioCode\Lesson\Algorithms\lib.cpp"
#include <ios>
using namespace std;

class UnionFind_DepthWeighted {
    public:
    vector<int> id;
    vector<int> depth;
    int count;
    UnionFind_DepthWeighted(int num) : id(rangeInt(num)), depth(num, 1), count(num) {}
    bool isConnected(int p, int q) {
        return find(p) == find(q);
    }
    int find(int index) {
        while(index != id[index])
            index = id[index];
        return index;
    }
    void connect(int p, int q) {
        int pIndex = find(p);
        int qIndex = find(q);
        if(qIndex == pIndex)
            return;
        if(depth[pIndex] < depth[qIndex])
            id[pIndex] = qIndex;
        else if(depth[pIndex] > depth[qIndex])
            id[qIndex] = pIndex;
        else {
            id[pIndex] = qIndex;
            depth[qIndex]++;
        }
        count--;
    }
};

class UnionFind {
    public:
    vector<int> id;
    vector<int> sz;
    int count;
    UnionFind(int num) : id(rangeInt(num)), sz(num, 1), count(num) {}
    bool connected(int p, int q) {
        return find(p) == find(q);
    }
    int find(int index) {
        while(index != id[index])
            index = id[index];
        return index;
    }
    void connect(int p, int q) {
        int pIndex = find(p);
        int qIndex = find(q);
        if(pIndex == qIndex)
            return;
        if(sz[pIndex] < sz[qIndex]) {
            id[pIndex] = qIndex;
            sz[qIndex] += sz[pIndex];
        } else {
            id[qIndex] = pIndex;
            sz[pIndex] += sz[qIndex];
        }
        count--;
    }
};

class UnionFind_ { // 路径压缩且大小加权的
    public:
    vector<int> parent;
    vector<int> size;
    int count;
    UnionFind_(int num) : parent(rangeInt(num)), size(num, 1), count(num) {}
    int find(int index) {
        int root = index;
        while(parent[root] != root)
            root = parent[root];
        while(index != parent[index]) {
            int tmp = parent[index];
            parent[index] = root;
            index = tmp;
        }
        return root;
    }
    bool isConnected(int p, int q) {
        return find(p) == find(q);
    }
    void connect(int p, int q) {
        int pIndex = find(p);
        int qIndex = find(q);
        if(pIndex == qIndex)
            return;
        if(size[pIndex] < size[qIndex]) {
            parent[pIndex] = qIndex;
            size[qIndex] += size[pIndex];
        }
        else {
            parent[qIndex] = pIndex;
            size[pIndex] += size[qIndex];
        }
        count--;
    }
};

int main() {

    int num;
    cin >> num;
    UnionFind_ unionfind(num);
    for(int i = 0; i < 900; i++) {
        int p, q;
        cin >> p >> q;
        unionfind.connect(p, q);
    }
    
    cout << boolalpha;
    cout << '\n';
    cout << unionfind.parent;
    cout << unionfind.count;
    return 0;

}