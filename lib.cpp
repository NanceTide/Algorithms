#ifndef LIB_CPP
#define LIB_CPP
#include <ios>
#include <map>
#include <set>
#include <sal.h>
#include <ctime>
#include <stack>
#include <deque>
#include <vector>
#include <random>
#include <cassert>
#include <cstddef>
#include <ctype.h>
#include <ostream>
#include <iostream>
#include <typeinfo>
#include <algorithm>
using namespace std;

/*
⣿⣆⠱⣝⡵⣝⢅⠙⣿⢕⢕⢕⢕⢝⣥⢒⠅⣿⣿⣿⡿⣳⣌⠪⡪⣡⢑
⣿⣿⣦⠹⣳⣳⣕⢅⠈⢗⢕⢕⢕⢕⢕⢈⢆⠟⠋⠉⠁⠉⠉⠁⠈⠼⢐
⢰⣶⣶⣦⣝⢝⢕⢕⠅⡆⢕⢕⢕⢕⢕⣴⠏⣠⡶⠛⡉⡉⡛⢶⣦⡀⠐
⡄⢻⢟⣿⣿⣷⣕⣕⣅⣿⣔⣕⣵⣵⣿⣿⢠⣿⢠⣮⡈⣌⠨⠅⠹⣷⡀
⡵⠟⠈⢀⣀⣀⡀⠉⢿⣿⣿⣿⣿⣿⣿⣿⣼⣿⢈⡋⠴⢿⡟⣡⡇⣿⡇
⠁⣠⣾⠟⡉⡉⡉⠻⣦⣻⣿⣿⣿⣿⣿⣿⣿⣿⣧⠸⣿⣦⣥⣿⡇⡿⣰
⢰⣿⡏⣴⣌⠈⣌⠡⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣬⣉⣉⣁⣄⢖⢕
⢻⣿⡇⢙⠁⠴⢿⡟⣡⡆⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣵
⣄⣻⣿⣌⠘⢿⣷⣥⣿⠇⣿⣿⣿⣿⣿⣿⠛⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢄⠻⣿⣟⠿⠦⠍⠉⣡⣾⣿⣿⣿⣿⣿⣿⢸⣿⣦⠙⣿⣿⣿⣿⣿⣿⣿
⡑⣑⣈⣻⢗⢟⢞⢝⣻⣿⣿⣿⣿⣿⣿⣿⠸⣿⠿⠃⣿⣿⣿⣿⣿⣿⡿
⡵⡈⢟⢕⢕⢕⢕⣵⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣿⣿⣿⣿⣿⠿⠋⣀
⣿⣿⣿⢻⣿⣿⣿⣿⠻⣿⣿⡿⠿⠿⠿⣿⠻⡿⠻⠿⣿⡟⠛⠛⢛⣿⣿
⣿⠏⣼⢸⡄⢿⢋⢸⣷⣇⢻⣿⣿⣿⣿⣿⡗⣥⠂⢦⣿⣭⢩⡍⣭⣽⣿
⣿⣾⣛⣸⣿⣾⣾⣈⣛⣠⣿⣤⣤⣤⣤⣼⣴⣫⣶⣌⣻⣋⣼⣇⣋⣼⣿
*/

vector<int> randomInt(int n) {
    static default_random_engine randomIntEngine(clock());
    static uniform_int_distribution<int> randomIntDistribution;
    vector<int> ans;
    for(int i = 0; i < n; i++)
        ans.push_back(randomIntDistribution(randomIntEngine));
    return ans;
}

vector<int> randomInt(int n, int l, int r) {
    static default_random_engine randomIntEngine(clock());
    static uniform_int_distribution<int> randomIntDistirbution(l, r - 1);
    vector<int> ans;
    for(int i = 0; i < n; i++)
        ans.push_back(randomIntDistirbution(randomIntEngine));
    return ans;
}

vector<int> rangeInt(int lo, int hi, int step) {
    vector<int> ans;
    if(step > 0)
        for(; lo < hi; lo += step)
            ans.push_back(lo);
    else if(step < 0) 
        for(; lo > hi; lo += step)
            ans.push_back(lo);
    return ans;
}

vector<int> rangeInt(int lo, int hi) {
    vector<int> ans;
    for(; lo < hi; lo++) 
        ans.push_back(lo);
    return ans;
}

vector<int> rangeInt(int hi) {
    vector<int> ans;
    for(int lo = 0; lo < hi; lo++)
        ans.push_back(lo);
    return ans;
}

vector<int> sameInt(int time, int num) {
    vector<int> ans;
    for(int i = 0; i < num; i++)
        ans.push_back(i);
    return ans;
}

template <typename T> bool operator==(vector<T> l, vector<T> r) {
    if(l.size() != r.size())
        return false;
    for(int i = 0; i < l.size(); i++)
        if(l[i] != r[i])
            return false;
    return true;
}

template <typename T> ostream& operator<<(ostream& os, vector<T> &vec) {
    for(auto c : vec)
        cout << c << ' ';
    cout << '\n';
    return os;
}

template <typename T> ostream& operator<<(ostream& os, vector<T> &&vec) {
    for(auto c : vec)
        cout << c << ' ';
    cout << '\n';
    return os;
}

template <typename T> ostream& operator<<(ostream& os, deque<T> &dq) {
    for(auto c : dq)
        cout << c << ' ';
    cout << '\n';
    return os;
}

template <typename T> ostream& operator<<(ostream& os, deque<T> &&dq) {
    for(auto c : dq)
        cout << c << ' ';
    cout << '\n';
    return os;
}

template <typename T> ostream& operator<<(ostream& os, stack<T> st) {
    while(st.size()) {
        cout << st.top() << ' ';
        st.pop();
    }
    cout << '\n';
    return os;
}

#endif