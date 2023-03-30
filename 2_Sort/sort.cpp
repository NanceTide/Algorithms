#include "sort_lib.cpp"
#include <set>
using namespace std;

class BubbleSort : public SortList {
    public:
    BubbleSort(vector<int> vec) : SortList(vec) {}
    void sort() {
        for(int i = 0; i < vec.size() - 1; i++)
            for(int j = 0; j < vec.size() - i - 1; j++)
                if(vec[j] > vec[j + 1])
                    swap(vec[j], vec[j + 1]);
    }
};

class InsertSort : public SortList {
    public:
    InsertSort(vector<int> vec) : SortList(vec) {}
    void sort() {
        for(int i = 1; i < vec.size(); i++)
            for(int j = i; j && vec[j - 1] > vec[j]; j--)
                swap(vec[j], vec[j - 1]);
    }
};

class SelectionSort : public SortList {
    public:
    SelectionSort(vector<int> vec) : SortList(vec) {}
    void sort() {
        for(int i = 0; i < vec.size(); i++) {
            int minIndex = i;
            for(int j = i; j < vec.size(); j++)
                if(vec[j] < vec[minIndex])
                    minIndex = j;
            swap(vec[minIndex], vec[i]);
        }
    }
};

class QuickSort : public SortList {
    public:
    QuickSort(vector<int> vec) : SortList(vec) {}
    void sort() {
        sort(0, vec.size() - 1);
    }
    void sort(int lo, int hi) {
        if(lo >= hi)
            return;
        int mid = partition(lo, hi);
        sort(lo, mid - 1);
        sort(mid + 1, hi);
    }
    int partition(int lo, int hi) {
        int pivot = vec[lo];
        while(lo < hi) {
            while(vec[hi] >= pivot && lo < hi)
                hi--;
            vec[lo] = vec[hi];
            while(vec[lo] <= pivot && lo < hi)
                lo++;
            vec[hi] = vec[lo];
        }
        vec[lo] = pivot;
        return lo;
    }
};

class ShellSort : public SortList {
    public:
    ShellSort(vector<int> vec) : SortList(vec) {}
    void sort() {
        auto delta = getDelta();
        for(auto p = delta.rbegin(); p != delta.rend(); p++) {
            for(int i = *p; i < vec.size(); i++) {
                for(int j = i; j >= *p && vec[j] < vec[j - *p]; j -= *p)
                    swap(vec[j], vec[j - *p]);
            }
        }
    }
    vector<int> getDelta() {
        vector<int> delta;
        int h = 1;
        while(h < vec.size() / 3) {
            delta.push_back(h);
            h = h * 3 + 1;
        }
        return delta;
    }
};

class MergeSort : public SortList {
    public:
    vector<int> aux;
    MergeSort(vector<int> vec) : SortList(vec), aux(vec.size()) {}
    void sort() {
        sort(0, vec.size() - 1);
    }
    void sort(int lo, int hi) {
        if(lo >= hi)
            return;
        int mid = lo + ((hi - lo) >> 1);
        sort(lo, mid);
        sort(mid + 1, hi);
        merge(lo, mid, hi);
    }
    void merge(int lo, int mid, int hi) {
        int i = lo, j = mid + 1;
        for(int k = lo; k <= hi; k++)
            aux[k] = vec[k];
        for(int k = lo; k <= hi; k++) {
            if(i > mid)
                vec[k] = aux[j++];
            else if(j > hi)
                vec[k] = aux[i++];
            else if(aux[i] < aux[j])
                vec[k] = aux[i++];
            else
                vec[k] = aux[j++];
        }
    }
};

class MergeSortWithInsert : public SortList {
    public:
    vector<int> aux;
    MergeSortWithInsert(vector<int> vec) : SortList(vec), aux(vec.size()) {}
    void sort() {
        sort(0, vec.size() - 1);
    }
    void sort(int lo, int hi) {
        if(hi - lo < 12) {
            insertSort(lo, hi);
            return;
        } else if(lo >= hi)
            return;
        int mid = lo + ((hi - lo) >> 1);
        sort(lo, mid);
        sort(mid + 1, hi);
        merge(lo, mid, hi);
    }
    void merge(int lo, int mid, int hi) {
        int i = lo, j = mid + 1;
        for(int k = lo; k <= hi; k++)
            aux[k] = vec[k];
        for(int k = lo; k <= hi; k++) {
            if(i > mid)
                vec[k] = aux[j++];
            else if(j > hi)
                vec[k] = aux[i++];
            else if(aux[i] < aux[j])
                vec[k] = aux[i++];
            else
                vec[k] = aux[j++];
        }
    }
    void insertSort(int lo, int hi) {
        for(int i = lo + 1; i <= hi; i++)
            for(int j = i; j > lo && vec[j - 1] > vec[j]; j--)
                swap(vec[j - 1], vec[j]);
    }
};

class MergeBUSort : public SortList {
    public:
    vector<int> aux;
    MergeBUSort(vector<int> vec) : SortList(vec), aux(vec.size()) {}
    void sort() {
        for(int sz = 1; sz < vec.size(); sz <<= 1)
            for(int lo = 0; lo < vec.size() - sz; lo += sz * 2)
                merge(lo, lo + sz - 1, min(lo + sz * 2, (int)vec.size()) - 1);
    }
    void merge(int lo, int mid, int hi) {
        int i = lo, j = mid + 1;
        for(int k = lo; k <= hi; k++)
            aux[k] = vec[k];
        for(int k = lo; k <= hi; k++) {
            if(i > mid)
                vec[k] = aux[j++];
            else if(j > hi)
                vec[k] = aux[i++];
            else if(aux[i] < aux[j])
                vec[k] = aux[i++];
            else
                vec[k] = aux[j++];
        }
    }
};

class HeapSort : public SortList {
    public:
    int n;
    HeapSort(vector<int> vec) :  SortList(vec),  n(vec.size() - 1) {}
    void sort() {
        for(int i = n >> 1; i; i--)
            sink(i);
        while(n > 1) {
            swap(vec[1], vec[n--]);
            sink(1);
        }
    }
    void sink(int k) {
        for(int j = k << 1; j <= n; k = j, j = k << 1) {
            if(j < n && vec[j] < vec[j + 1])
                j++;
            if(vec[j] < vec[k])
                return;
            swap(vec[j], vec[k]);
        }
    }
    void swim(int k) {
        for(; k > 1 && vec[k] > vec[k >> 1]; k >>= 1)
            swap(vec[k], vec[k >> 1]);
    }
    void insert(int k) {
        vec.push_back(k);
        swim(vec.size() - 1);
        n++;
    }
    int delMax() {
        int max = vec[1];
        vec[1] = vec[vec.size() - 1];
        vec.pop_back();
        n--;
        sink(1);
        return max;
    }
};

class Quick3Way : public SortList {
    public:
    Quick3Way(vector<int> vec) : SortList(vec) {}
    void sort() {
        sort(0, vec.size() - 1);
    }
    void sort(int lo, int hi) {
        if(hi <= lo) 
            return;
        int lt = lo, i = lo + 1, gt = hi;
        int pivot = vec[lo];
        while(i <= gt) {
            if(vec[i] < pivot)
                swap(vec[i++], vec[lt++]);
            else if(pivot < vec[i])
                swap(vec[i], vec[gt--]);
            else
                i++;
        }
        sort(lo, lt - 1);
        sort(gt + 1, hi);
    }
};

class QuickSortBetter : public SortList {
    public:
    QuickSortBetter(vector<int> vec) : SortList(vec) {}
    void sort() {
        sort(0, vec.size() - 1);
    }
    int partition(int lo, int hi) {
        insertSort(lo, lo + 2 );
        lo = lo + 1;
        int pivot = vec[lo];
        while(lo < hi) {
            while(lo < hi && vec[hi] >= pivot)
                hi--;
            vec[lo] = vec[hi];
            while(lo < hi && vec[lo] <= pivot)
                lo++;
            vec[hi] = vec[lo];
        }
        vec[lo] = pivot;
        return lo;
    }
    void insertSort(int lo, int hi) {
        for(int i = lo + 1; i <= hi; i++)
            for(int j = i; j > lo && vec[j] < vec[j - 1]; j--)
                swap(vec[j], vec[j - 1]);
    }
    void sort(int lo, int hi) {
        if(hi - lo <= 8) {
            insertSort(lo, hi);
            return;
        }
        int i = partition(lo, hi);
        sort(lo, i - 1);
        sort(i + 1, hi);
    }
};

int main() {

    int num = 1024000;
    BubbleSort bubblesort(randomInt(num));
    InsertSort insertsort(randomInt(num));
    SelectionSort selectionsort(randomInt(num));
    QuickSort quicksort(randomInt(num));
    ShellSort shellsort(randomInt(num));
    MergeSort mergesort(randomInt(num));
    MergeSortWithInsert mergesortwithinsert(randomInt(num));
    MergeBUSort mergebusort(randomInt(num));
    // check(bubblesort);
    // check(insertsort);
    // check(selectionsort);
    check(quicksort);
    check(shellsort);
    check(mergesort);
    check(mergesortwithinsert);
    check(mergebusort);

    // HeapSort heapsort(randomInt(100));
    // heapsort.sort();
    // cout << heapsort;
    // cout << is_sorted(heapsort.vec.begin() + 1, heapsort.vec.end());

    // auto vec = randomInt(num, 0, 10);
    // QuickSort quick2(vec);
    // Quick3Way quick3(vec);
    // check(quick2);
    // check(quick3);

    // auto vec = randomInt(num);
    // QuickSort quickori(vec);
    // QuickSortBetter quickbet(vec);
    // check(quickori);
    // check(quickbet);

    return 0;

}