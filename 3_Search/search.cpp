#include "search_lib.cpp"
#include <algorithm>
#include <iterator>
#include <random>
using namespace std;

template<typename Key, typename Value> class BinarySearch {
    public:
    Key *keys;
    Value *vals;
    int N;
    int capacity;
    BinarySearch<Key, Value>(int capacity) : capacity(capacity), N(0) {
        keys = new Key[capacity];
        vals = new Value[capacity];
    }
    int size() {
        return N;
    }
    int rank(Key key) {
        int lo = 0, hi = N - 1;
        while(lo <= hi) {
            int mid = lo + ((hi - lo) >> 1);
            if(key < keys[mid])
                hi = mid - 1;
            else if(key > keys[mid])
                lo = mid + 1;
            else
                return mid;
        }
        return lo;
    }
    int rank(Key key, int lo, int hi) {
        if(hi < lo)
            return lo;
        int mid = lo + ((hi - lo) >> 1);
        if(key < keys[mid])
            return rank(key, lo, mid - 1);
        else if(key > keys[mid])
            return rank(key, mid + 1, hi);
        else
            return mid;
    }
    bool isEmpty() {
        return N == 0;
    }
    Value& operator[](Key key) {
        if(isEmpty())
            return nullptr;
        int index = rank(key);
        if(index < N && keys[index] == key)
            return vals[index];
        else
            return nullptr;
    }
    void put(Key key, Value val) {
        int index = rank(key, 0, N - 1);
        if(index < N && keys[index] == key) {
            vals[index] = val;
        } else if(N + 1 < capacity) {
            for(int j = N; j > index; j--) {
                keys[j] = keys[j - 1];
                vals[j] = vals[j - 1];
            }
            keys[index] = key;
            vals[index] = val;
            N++;
        }
        return;
    }
    void prt() {
        for(int i = 0; i < N; i++)
            cout << i << '\t' << keys[i] << '\t' << vals[i] << '\n';
    }
};

template<typename Key, typename Value> class BST {
    public:
    BST() : root(nullptr) {}
    class Node {
        public:
        Key key;
        Value val;
        Node *left, *right;
        int N;
        Node(Key key, Value val, int N = 1) : key(key), val(val), N(N), left(nullptr), right(nullptr) {}
    } *root;

    int size(Node *x) {
        return x ? x->N : 0;
    }
    int size() {
        return size(root);
    }

    Node* put(Node *x, Key key, Value val) {
        if(!x)
            return new Node(key, val);
        if(key < x->key)
            x->left = put(x->left, key, val);
        else if(key > x->key)
            x->right = put(x->right, key, val);
        else if(key == x->key)
            x->val = val;
        x->N = size(x->left) + size(x->right) + 1;
        return x;
    }
    void put_(Key key, Value val) {
        if(!root) {
            root = new Node(key, val);
            return;
        }
        Node *curr = root, *prev = nullptr;
        while(curr) {
            prev = curr;
            if(curr->key < key)
                curr = curr->right;
            else if(curr->key > key)
                curr = curr->left;
            else if(curr->key == key) {
                curr->val = val;
                return;
            }
        }
        if(prev->key < key)
            prev->right = new Node(key, val);
        else if(prev->key > key)
            prev->left = new Node(key, val);
        curr = root;
        while(key != curr->key) {
            curr->N++;
            if(curr->key < key)
                curr = curr->right;
            else if(key < curr->key)
                curr = curr->left;
        }
    } 
    void put(Key key, Value val) {
        root = put(root, key, val);
    }

    Value get_(Key key) {
        Node *p = root;
        while(p) {
            if(p->key < key)
                p = p->right;
            else if(key < p->key)
                p = p->left;
            else if(key == p->key)
                return p->val;
        }
        return nullptr;
    }
    Value get(Node *x, Key key) {
        if(!x)
            return nullptr;
        if(key < x->key)
            return get(x->left, key);
        else if(x->key < key)
            return get(x->right, key);
        else
            return x->val;
    }
    Value operator[](Key key) {
        return get(root, key);
    }

    Node* floor(Node *x, Key key) {
        if(!x)
            return nullptr;
        if(key == x->key)
            return x;
        else if(key < x->key)
            return floor(x->left, key);
        auto t = floor(x->right, key);
        if(t)
            return t;
        else
            return x;
    }
    Key floor(Key key) {
        auto x = floor(root, key);
        if(!x)
            throw;
        else
            return x->key;
    }

    Node* ceil(Node *x, Key key) {
        if(!x)
            return nullptr;
        if(x->key < key)
            return ceil(x->right, key);
        if(x->key == key)
            return x;
        auto t = ceil(x->left, key);
        if(t)
            return t;
        else
            return x; 
    }
    Key ceil(Key key) {
        auto x = ceil(root, key);
        if(x)
            return x->key;
        else
            throw;
    }

    Node* select(Node* root, int index) {
        if(!root)
            return nullptr;
        int t = size(root->left);
        if(index > t)
            return select(root->right, index - t - 1);
        else if(index < t)
            return select(root->left, index);
        else
            return root;
    }
    Key select(int index) {
        assert(index <= root->N);
        return select(root, index)->key;
    }

    int rank(Node *root, Key key) {
        if(!root)
            return 0;
        int t = size(root->left);
        if(root->key < key)
            return rank(root->right, key) + 1 + t;
        else if(key < root->key)
            return rank(root->left, key);
        else
            return t;
    }
    int rank(Key key) {
        return rank(root, key);
    }

    Node* deleteMin(Node* root) {
        if(!root->left)
            return root->right;
        root->left = deleteMin(root->left);
        root->N = size(root->left) + size(root->right) + 1;
        return root;
    }
    void deleteMin() {
        root = deleteMin(root);
    }

    Node* deleteMax(Node* root) {
        if(!root->right)
            return root->left;
        root->right = deleteMax(root->right);
        root->N = size(root->left) + size(root->right) + 1;
        return root;
    }
    void deleteMax() {
        root = deleteMax(root);
    }

    Node* deleteEqual(Node* root, Key key) {
        if(!root)
            return nullptr;
        if(key < root->key)
            root->left = deleteEqual(root->left, key);
        else if(root->key < key)
            root->right = deleteEqual(root->right, key);
        else {
            if(!root->left)
                return root->right;
            else if(!root->right)
                return root->left;
            Node* t = root;
            root = min(t->right);
            root->right = deleteMin(t->right);
            root->left = t->left;
        }
        root->N = size(root->left) + size(root->right) + 1;
        return root;
    }
    void deleteEqual(Key key) {
        root = deleteEqual(root, key);
    }

    Node* min(Node* root) {
        if(root)
            if(root->left)
                return min(root->left);
            else
                return root;
        else
            return nullptr;
    }
    Key min() {
        if(!root) throw;
        return min(root)->key;
    }

    Node* max(Node* root) {
        if(root)
            if(root->right)
                return max(root->right);
            else
                return root;
        else
            return nullptr;
    }
    Key max() {
        if(!root) throw;
        return max(root)->key;
    }

    void keys(Node* root, vector<Key> &ans, Key lo, Key hi) {
        if(!root)
            return;
        if(lo < root->key)
            keys(root->left, ans, lo, hi);
        if(lo <= root->key && root->key <= hi)
            ans.push_back(root->key);
        if(root->key < hi)
            keys(root->right, ans, lo, hi);
    }
    vector<Key> keys(Key lo, Key hi) {
        vector<Key> ans;
        keys(root, ans, lo, hi);
        return ans;
    }
    vector<Key> keys() {
        return keys(min(), max());
    }

    void inOrderPrt(Node *x) {
        if(!x)
            return;
        inOrderPrt(x->left);
        cout << x->key << '\t' << x->val << '\t' << x->N << '\n';
        inOrderPrt(x->right);
    }
    void inOrderPrt() {
        inOrderPrt(root);
    }
};



int main() {

    auto vec = rangeInt(0, 100, 2);
    random_shuffle(vec.begin(), vec.end());

    // BinarySearch<int, int> binarysearch(200);
    // for(auto c : vec)
    //     binarysearch.put(c, -c);    
    // binarysearch.prt();

    BST<int, int> bst;
    for(auto c : vec)
        bst.put_(c, -c);
    bst.inOrderPrt();
    // for(auto c : rangeInt(0, 99))
    //     cout << bst.ceil(c) << ' ';
    // cout << '\n';
    // cout << bst.select(32) << '\n';
    // cout << bst.rank(25);
    bst.deleteMin();
    bst.inOrderPrt();
    bst.deleteEqual(24);
    bst.inOrderPrt();
    cout << bst.keys(); 


}