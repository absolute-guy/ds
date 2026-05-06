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

// Get height
int getHeight(Node* n) {
    return n ? n->height : 0;
}

// Get balance factor
int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

// Right rotate
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left rotate
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Insert function
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

    // Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Inorder traversal
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " (BF=" << getBalance(root) << ")  ";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    int arr[] = {10, 5, 15, 3, 7};
    for (int x : arr)
        root = insert(root, x);

    root = insert(root, 12);

    cout << "Inorder traversal with balance factors:\n";
    inorder(root);

    cout << "\nHeight of tree: " << getHeight(root) << endl;

    return 0;
}