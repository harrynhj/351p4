#include<vector>

using namespace std;

struct HuffmanNode {
	int character;
	int count;
	HuffmanNode* zero;
	HuffmanNode* one;
};

class PriorityQueue {
private:
    vector<HuffmanNode*> heap;
    
    void heapify(int i) {
        long unsigned int left = 2 * i + 1;
        long unsigned int right = 2 * i + 2;
        int smallest = i;

        if (left < heap.size() && heap[left] -> count < heap[smallest] -> count)
            smallest = left;

        if (right < heap.size() && heap[right] -> count < heap[smallest] -> count)
            smallest = right;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
}

public:
    void push(HuffmanNode* node) {
        heap.push_back(node);
        int index = heap.size() - 1;
        int parent = (index - 1) / 2;

        while (index > 0 && heap[parent] -> count > heap[index] -> count) {
            swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void pop() {
        if (heap.empty())
            return;

        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
    }

    HuffmanNode* top() {
        return heap[0];
    }

    bool empty() {
        return heap.empty();
    }

    int size() {
        int size = heap.size();
        return size;
    }

    void printPQ() {
        for(auto x : heap)
            cout << x -> count << endl;
    }

};