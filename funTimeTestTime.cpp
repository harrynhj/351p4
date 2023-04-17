#include <iostream>

#include "PriorityQueue.h"

using namespace std;

int main() {
    pair<int,int> pp1 = make_pair(1, 1);
    pair<int,int> pp2 = make_pair(2, 2);
    pair<int,int> pp3 = make_pair(3, 3);
    pair<int,int> pp4 = make_pair(4, 4);

    PriorityQueue *pq = new PriorityQueue;
    cout << pq -> size() << endl;
    pq -> emplace(pp1);
    // pq -> print();
    
    cout << pq -> size() << endl;
    pq -> emplace(pp2);
    // pq -> print();
    
    cout << pq -> size() << endl;
    pq -> emplace(pp3);
    // pq -> print();

    cout << pq -> size() << endl;
    pq -> emplace(pp4);
    // pq -> print();

    //pq -> print();

    return 0;
}