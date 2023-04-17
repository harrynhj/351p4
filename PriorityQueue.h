#include <iostream>
#include <vector>

using namespace std;

class PriorityQueue {
    public:
    int length;
    vector<pair<int, int> > heap;

    // PriorityQueue(pair<int, int> pair, vector<string> data) {
    
    PriorityQueue() {
        length = 0;

    }
    // ~PriorityQueue() { }

    void sortHelper(vector<pair<int, int>>& heap) {

    }
    struct sorter {
        bool operator()(pair<int, int>& left, pair<int, int>& right) {
            return left.second > right.second;
        }
    };

    void emplace(pair<int, int> k) {
        heap.push_back(k);
        sort(heap.begin(), heap.end(), sorter());
        print();
        length++;
    }

    void pop() {
        heap.erase(heap.begin());
    }

    pair<int,int> top() {
        return heap[0];
    }

    bool empty() {
        if(size() == 0)
            return true;
        return false;
    }

    int size() {
        return this -> length;
    }

    void print() {
        for(pair<int, int> l : heap)
            cout << l.first << " " << l.second << endl;
    }

};