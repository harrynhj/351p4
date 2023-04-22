#include <iostream>

#include "PriorityQueue.h"

using namespace std;



int main() {
    PriorityQueue pq;
    for (int i = 0; i < 100; i++) {
        HuffmanNode* node = new HuffmanNode();
        node -> count = rand();
        pq.push(node);
    }
    
    for (int i = 0; i < 100; i++) {
        HuffmanNode* node;
        node = pq.top();
        cout << node->count << endl;
        pq.pop();
    }


    return 0;
}