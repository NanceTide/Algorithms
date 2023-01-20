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

int main() {

    UnionFind unionfind(100);

    unionfind.connect(0, 1);
    unionfind.connect(0, 2);
    unionfind.connect(0, 3);
    unionfind.connect(99, 3);
    
    cout << boolalpha;
    cout << unionfind.isConnected(98, 2) << '\n';
    cout << unionfind.count;
    return 0;

}