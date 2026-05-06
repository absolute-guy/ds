#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = NULL;
    }
};

Node* table[10] = {NULL};

void insert(int x) {
    int idx = x % 10;

    Node* newNode = new Node(x);
    newNode->next = table[idx];
    table[idx] = newNode;
}

int countNodes(Node* head) {
    int cnt = 0;
    while (head != NULL) {
        cnt++;
        head = head->next;
    }
    return cnt;
}

void copyToArray(Node* head, int arr[]) {
    int i = 0;
    while (head != NULL) {
        arr[i++] = head->data;
        head = head->next;
    }
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

Node* arrayToList(int arr[], int n) {
    Node* head = NULL;

    for (int i = n - 1; i >= 0; i--) {
        Node* newNode = new Node(arr[i]);
        newNode->next = head;
        head = newNode;
    }

    return head;
}

void sortBucket(int idx) {
    Node* head = table[idx];

    if (head == NULL || head->next == NULL)
        return;

    int n = countNodes(head);

    int* arr = new int[n];

    copyToArray(head, arr);

    quickSort(arr, 0, n - 1);

    table[idx] = arrayToList(arr, n);

    delete[] arr;
}

void printTable() {
    for (int i = 0; i < 10; i++) {
        cout << i << " : ";
        Node* temp = table[i];

        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
}

int main() {
    insert(30);
    insert(20);
    insert(10);
    insert(40);
    insert(50);

    printTable();

    sortBucket(0);

    printTable();

    return 0;
}