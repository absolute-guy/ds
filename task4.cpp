#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    int height;

    Node(int k) {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

// ---------------- HEIGHT ----------------
int getHeight(Node* n) {
    return (n == nullptr) ? 0 : n->height;
}

// ---------------- MAX ----------------
int max(int a, int b) {
    return (a > b) ? a : b;
}

// ---------------- RIGHT ROTATION ----------------
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// ---------------- LEFT ROTATION ----------------
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// ---------------- BALANCE FACTOR ----------------
int getBalance(Node* n) {
    if (!n) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// ---------------- INSERT ----------------
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // LL
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// ---------------- RANGE SUM ----------------
int rangeSum(Node* root, int L, int R) {
    if (!root) return 0;

    // If node is smaller than L → go right
    if (root->key < L)
        return rangeSum(root->right, L, R);

    // If node is greater than R → go left
    if (root->key > R)
        return rangeSum(root->left, L, R);

    // Node is in range
    return root->key
         + rangeSum(root->left, L, R)
         + rangeSum(root->right, L, R);
}

// ---------------- MAIN ----------------
int main() {
    Node* root = nullptr;

    int arr[] = {200, 50, 300, 400, 700, 150};
    int n = 6;

    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    int L = 100, R = 500;

    int result = rangeSum(root, L, R);

    cout << "Sum of transactions in range ["
         << L << ", " << R << "] = "
         << result << endl;

    return 0;
}