#include <iostream>
using namespace std;

class MaxHeap {
    int arr[100];
    int size;

public:
    MaxHeap() {
        size = 0;
    }

    void insert(int value) {
        size++;
        arr[size] = value;

        int i = size;

        // Heapify Up
        while (i > 1 && arr[i/2] < arr[i]) {
            swap(arr[i], arr[i/2]);
            i = i/2;
        }
    }

    void deleteRoot() {
        if (size == 0) return;

        arr[1] = arr[size];
        size--;

        int i = 1;

        // Heapify Down
        while (true) {
            int largest = i;
            int left = 2*i;
            int right = 2*i + 1;

            if (left <= size && arr[left] > arr[largest])
                largest = left;

            if (right <= size && arr[right] > arr[largest])
                largest = right;

            if (largest != i) {
                swap(arr[i], arr[largest]);
                i = largest;
            } else break;
        }
    }

    void print() {
        for (int i = 1; i <= size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main() {
    MaxHeap h;
    h.insert(10);
    h.insert(20);
    h.insert(5);
    h.insert(30);

    h.print();

    h.deleteRoot();
    h.print();
}