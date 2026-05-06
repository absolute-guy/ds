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

    bool search(Node* node, int key) {
        if (node == NULL)
            return false;

        if (node->data == key)
            return true;

        if (key < node->data)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    bool search(int key) {
        return search(root, key);
    }

    Node* minValueNode(Node* node) {
        while (node && node->left != NULL)
            node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, int key) {
        if (node == NULL)
            return NULL;

        if (key < node->data)
            node->left = deleteNode(node->left, key);

        else if (key > node->data)
            node->right = deleteNode(node->right, key);

        else {
            if (node->left == NULL && node->right == NULL)
                return NULL;

            else if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }

        return node;
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

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
};



// ================= FIXED TREE COMPARISON =================
bool isSame(Node* a, Node* b) {
    if (a == NULL && b == NULL)
        return true;

    if (a == NULL || b == NULL)
        return false;

    if (a->data != b->data)
        return false;

    return isSame(a->left, b->left) &&
           isSame(a->right, b->right);
}



// ================= MAIN =================
int main() {
    BST tree, tree1;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);
    tree.insert(7);
    tree.insert(12);

    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);
    tree1.insert(2);
    tree1.insert(7);
    tree1.insert(12);

    cout << "Tree 1 Inorder: ";
    tree.inorder();

    cout << "Tree 2 Inorder: ";
    tree1.inorder();

    tree.deleteNode(5);
    tree1.deleteNode(5);

    cout << "After deletion Tree 1: ";
    tree.inorder();

    cout << "After deletion Tree 2: ";
    tree1.inorder();

    if (isSame(tree.root, tree1.root))
        cout << "Trees are SAME" << endl;
    else
        cout << "Trees are DIFFERENT" << endl;

    return 0;
}