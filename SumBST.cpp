#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Insert in BST
Node* insert(Node* root, int val) {
    if (root == NULL) return new Node(val);

    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);

    return root;
}

// Function to calculate sum
int findSum(Node* root) {
    if (root == NULL)
        return 0;

    return root->data + findSum(root->left) + findSum(root->right);
}

int main() {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);

    cout << "Sum of BST: " << findSum(root);

    return 0;
}