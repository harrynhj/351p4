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
        int largest = i;
        if (left < heap.size() && heap[left]->count > heap[largest]->count) {
            largest = left;
        }
        if (right < heap.size() && heap[right]->count > heap[largest]->count) {
            largest = right;
        }
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }
public:
    void push(HuffmanNode* node) {
        heap.push_back(node);
        int index = heap.size() - 1;
        int parent = (index - 1) / 2;
        while (index > 0 && heap[parent]->count < heap[index]->count) {
            swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void pop() {
        if (heap.empty()) {
            return;
        }
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
};