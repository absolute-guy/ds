#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;

    Node(int k) {
        key = k;
        left = right = nullptr;
    }
};

// ---------------- INSERT ----------------
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// ---------------- COUNT NODES ----------------
int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ---------------- FIND KTH INORDER ----------------
void kthInorder(Node* root, int &k, int &result) {
    if (!root) return;

    kthInorder(root->left, k, result);

    k--;
    if (k == 0) {
        result = root->key;
        return;
    }

    kthInorder(root->right, k, result);
}

// ---------------- MEDIAN ----------------
double findMedian(Node* root) {
    int n = countNodes(root);

    int k1, k2;
    int result1 = 0, result2 = 0;

    if (n % 2 == 1) {
        int k = (n + 1) / 2;
        kthInorder(root, k, result1);
        return result1;
    }
    else {
        int k = n / 2;
        kthInorder(root, k, result1);

        k = n / 2 + 1;
        kthInorder(root, k, result2);

        return (result1 + result2) / 2.0;
    }
}

// ---------------- MAIN ----------------
int main() {
    Node* root = nullptr;

    // Example BST
    int arr[] = {50, 30, 70, 20, 40, 60, 80};

    for (int x : arr)
        root = insert(root, x);

    cout << "Median of BST = " << findMedian(root) << endl;

    return 0;
}