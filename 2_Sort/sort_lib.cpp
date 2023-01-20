#include "C:\Users\Nonce\Documents\VisualStudioCode\Lesson\Algorithms\lib.cpp"
using namespace std;

class SortList {
    public:
    vector<int> vec;
    SortList(vector<int> vec) : vec(vec) {}
    int& operator[](int index) {return vec[index];}
    virtual void sort() {}
};

ostream& operator<<(ostream &os, SortList list) {
    for(auto i : list.vec)
        os << i << ' ';
    os << '\n';
    return os;
}

const char* lstripNum(const char* str) {
    while(isdigit(*str))
        str++;
    return str;
}

template <typename T> void check(T &list) {
    vector<int> origin = list.vec;
    auto timeBegin = clock();
    list.sort();
    auto timeEnd = clock();
    sort(origin.begin(), origin.end());
    cout << boolalpha;
    cout << lstripNum(typeid(list).name()) << '\n';
    cout << "Is equal     : " << (origin == list.vec) << '\n';
    cout << "Is sorted    : " << is_sorted(list.vec.begin(), list.vec.end()) << '\n'; 
    cout << "Time consume : " << timeEnd - timeBegin << '\n';
} 