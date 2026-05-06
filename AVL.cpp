#include <iostream>
#include <algorithm>
using namespace std;

// Node structure
struct Node {
    int data;
    int height;
    Node *left, *right;

    Node(int value) {
        data = value;
        height = 1;
        left = right = nullptr;
    }
};

// Get height
int getHeight(Node* root) {
    return (root == nullptr) ? 0 : root->height;
}

// Get balance factor
int getBalance(Node* root) {
    return (root == nullptr) ? 0 : getHeight(root->left) - getHeight(root->right);
}

// Right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

// Left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

// Insert
Node* insertAVL(Node* root, int value) {
    if (root == nullptr)
        return new Node(value);

    if (value < root->data)
        root->left = insertAVL(root->left, value);
    else if (value > root->data)
        root->right = insertAVL(root->right, value);
    else
        return root; // no duplicates

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // LL
    if (balance > 1 && value < root->left->data)
        return rightRotate(root);

    // RR
    if (balance < -1 && value > root->right->data)
        return leftRotate(root);

    // LR
    if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL
    if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Get minimum node
Node* getMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

// Delete
Node* deleteAVL(Node* root, int value) {
    if (root == nullptr)
        return root;

    if (value < root->data)
        root->left = deleteAVL(root->left, value);
    else if (value > root->data)
        root->right = deleteAVL(root->right, value);
    else {
        // node found

        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = getMin(root->right);
            root->data = temp->data;
            root->right = deleteAVL(root->right, temp->data);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // LL
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder traversal
void inorder(Node* root) {
    if (root == nullptr)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Main
int main() {
    Node* root = nullptr;

    // Insert
    root = insertAVL(root, 1);
    root = insertAVL(root, 5);
    root = insertAVL(root, 3);
    root = insertAVL(root, 4);
    root = insertAVL(root, 2);

    cout << "Inorder before deletion: ";
    inorder(root);

    // Delete
    root = deleteAVL(root, 3);

    cout << "\nInorder after deletion: ";
    inorder(root);

    return 0;
}