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

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
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

    mergeSort(arr, 0, n - 1);

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