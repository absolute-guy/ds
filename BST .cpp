#include <iostream>
#include <algorithm>
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

    // ---------------- INSERT ----------------
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

    // ---------------- SEARCH ----------------
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

    // ---------------- MIN VALUE NODE ----------------
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    // ---------------- DELETE ----------------
    Node* deleteNode(Node* node, int key) {
        if (node == NULL)
            return node;

        if (key < node->data)
            node->left = deleteNode(node->left, key);

        else if (key > node->data)
            node->right = deleteNode(node->right, key);

        else {
            // Case 1: No child
            if (node->left == NULL && node->right == NULL)
                return NULL;

            // Case 2: One child
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

            // Case 3: Two children
            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }

        return node;
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    // ---------------- INORDER (LNR) ----------------
    void inorder(Node* node) {
        if (node == NULL)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    // ---------------- PREORDER (NLR) ----------------
    void preorder(Node* node) {
        if (node == NULL)
            return;

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void preorder() {
        preorder(root);
        cout << endl;
    }

    // ---------------- POSTORDER (LRN) ----------------
    void postorder(Node* node) {
        if (node == NULL)
            return;

        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    void postorder() {
        postorder(root);
        cout << endl;
    }

    // ---------------- LEVEL ORDER (BFS) ----------------
    void levelOrder() {
        if (root == NULL)
            return;

        Node* queue[100];
        int front = 0, rear = 0;

        queue[rear++] = root;

        while (front < rear) {
            Node* current = queue[front++];
            cout << current->data << " ";

            if (current->left != NULL)
                queue[rear++] = current->left;

            if (current->right != NULL)
                queue[rear++] = current->right;
        }

        cout << endl;
    }
};

// ---------------- Two Tree Compare ----------------
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

// ---------------- MAIN ----------------
int main() {
    BST tree,tree1;

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

    cout << "Inorder: ";
    tree.inorder();

    cout << "Preorder: ";
    tree.preorder();

    cout << "Postorder: ";
    tree.postorder();

    cout << "Level Order: ";
    tree.levelOrder();

    cout << "Search 7: " << (tree.search(7) ? "Found" : "Not Found") << endl;

    tree.deleteNode(5);
    tree1.deleteNode(5);

    cout << "After deleting 5 (Inorder): ";
    tree.inorder();

     if (isSame(tree.root,tree1.root))
        cout << "Trees are SAME" << endl;
    else
        cout << "Trees are DIFFERENT" << endl;

    return 0;
}