#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

class BST {
public:
    Node* root;

    BST() {
        root = NULL;
    }

    // INSERT
    Node* insert(Node* node, int key) {
        if (node == NULL)
            return new Node(key);

        if (key < node->data)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);

        return node;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    // INORDER
    void inorder(Node* node) {
        if (node == NULL) return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    // PREORDER
    void preorder(Node* node) {
        if (node == NULL) return;

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void preorder() {
        preorder(root);
        cout << endl;
    }

    // POSTORDER
    void postorder(Node* node) {
        if (node == NULL) return;

        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    void postorder() {
        postorder(root);
        cout << endl;
    }

    // HEIGHT
    int height(Node* node) {
        if (node == NULL)
            return 0;

        int lh = height(node->left);
        int rh = height(node->right);

        return max(lh, rh) + 1;
    }

    int height() {
        return height(root);
    }

    // BFS / LEVEL ORDER
    void BFS() {
        if (root == NULL) return;

        Node* queue[100];
        int front = 0, rear = 0;

        queue[rear++] = root;

        while (front < rear) {
            Node* curr = queue[front++];
            cout << curr->data << " ";

            if (curr->left != NULL)
                queue[rear++] = curr->left;

            if (curr->right != NULL)
                queue[rear++] = curr->right;
        }

        cout << endl;
    }
};