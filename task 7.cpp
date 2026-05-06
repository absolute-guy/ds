#include <iostream>
using namespace std;

const int MAX = 100;

// ---------------- PACKAGE STRUCT ----------------
struct Package {
    string id;
    int time;
};

// ---------------- MIN HEAP CLASS ----------------
class MinHeap {
private:
    Package heap[MAX];
    int size;

public:
    MinHeap() {
        size = 0;
    }

    void swap(Package &a, Package &b) {
        Package temp = a;
        a = b;
        b = temp;
    }

    void insert(string id, int time) {
        int i = size;
        heap[i] = {id, time};
        size++;

        // heapify up
        while (i != 0 && heap[(i - 1) / 2].time > heap[i].time) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void heapify(int i) {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < size && heap[l].time < heap[smallest].time)
            smallest = l;

        if (r < size && heap[r].time < heap[smallest].time)
            smallest = r;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }

    Package extractMin() {
        Package root = heap[0];

        heap[0] = heap[size - 1];
        size--;

        heapify(0);

        return root;
    }

    bool isEmpty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }

    Package get(int i) {
        return heap[i];
    }
};

// ---------------- STACK CLASS ----------------
class Stack {
private:
    Package arr[MAX];
    int top;

public:
    Stack() {
        top = -1;
    }

    void push(Package p) {
        arr[++top] = p;
    }

    Package pop() {
        return arr[top--];
    }

    bool isEmpty() {
        return top == -1;
    }

    int getTop() {
        return top;
    }
};

// ---------------- MAIN ----------------
int main() {
    MinHeap heap;

    // Initial packages
    heap.insert("pkg1", 45);
    heap.insert("pkg2", 20);
    heap.insert("pkg3", 35);
    heap.insert("pkg4", 10);
    heap.insert("pkg5", 50);
    heap.insert("pkg6", 30);
    heap.insert("pkg7", 25);

    cout << "First 3 Packages to Process (Earliest Arrival): ";

    Package processed[3];

    for (int i = 0; i < 3; i++) {
        processed[i] = heap.extractMin();
        cout << processed[i].id << " ";
    }

    cout << "\n";

    Stack st;

    while (!heap.isEmpty()) {
        st.push(heap.extractMin());
    }

    cout << "Remaining Packages (Latest Arrival): ";

    // Stack already gives reverse order (latest first)
    while (!st.isEmpty()) {
        Package p = st.pop();
        cout << p.id << " ";
    }

    cout << "\n";

    return 0;
}