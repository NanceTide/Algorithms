#include "sort_lib.cpp"
using namespace std;

class Select {
    public:
    vector<int> vec;
    Select(vector<int> vec) : vec(vec) {}
    int partition(int lo, int hi) {
        int pivot = vec[lo];
        while(lo < hi) {
            while(lo < hi && pivot <= vec[hi])
                hi--;
            vec[lo] = vec[hi];
            while(lo < hi && pivot >= vec[lo])
                lo++;
            vec[hi] = vec[lo];
        }
        vec[lo] = pivot;
        return lo;
    }
    int select(int k) {
        int lo = 0, hi = vec.size() - 1;
        while(hi > lo) {
            int i = partition(lo, hi);
            if(i == k)
                return vec[k];
            else if(k < i)
                hi = i - 1;
            else if(k > i)
                lo = i + 1;
        }
        return vec[k];
    }
};

int main() {
    auto vec = rangeInt(10, -10, -1);
    Select select(vec);
    cout << vec;
    cout << select.select(5);
    return 0;
}