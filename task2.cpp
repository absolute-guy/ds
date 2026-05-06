#include <iostream>
#include <string>
#include <climits>
using namespace std;

struct Node {
    int id;
    string desc;
    Node *left, *right;

    Node(int i, string d) {
        id = i;
        desc = d;
        left = right = nullptr;
    }
};

// ---------------- INSERT ----------------
Node* insert(Node* root, int id, string desc) {
    if (!root) return new Node(id, desc);

    if (id < root->id)
        root->left = insert(root->left, id, desc);
    else if (id > root->id)
        root->right = insert(root->right, id, desc);

    return root;
}

// ---------------- INORDER PRINT ----------------
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->id << " (" << root->desc << ") ";
    inorder(root->right);
}

// ---------------- K ITEMS IN RANGE ----------------
void printKRange(Node* root, int low, int high, int &k) {
    if (!root || k == 0) return;

    if (root->id > low)
        printKRange(root->left, low, high, k);

    if (k > 0 && root->id >= low && root->id <= high) {
        cout << root->id << " ";
        k--;
    }

    if (root->id < high)
        printKRange(root->right, low, high, k);
}

// ---------------- CLOSEST VALUE ----------------
void closestUtil(Node* root, int target, int &closest) {
    if (!root) return;

    if (abs(root->id - target) < abs(closest - target))
        closest = root->id;

    if (target < root->id)
        closestUtil(root->left, target, closest);
    else
        closestUtil(root->right, target, closest);
}

// ---------------- FIND MIN VALUE NODE ----------------
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// ---------------- DELETE NODE ----------------
Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->id)
        root->left = deleteNode(root->left, key);
    else if (key > root->id)
        root->right = deleteNode(root->right, key);
    else {
        // node found
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->id = temp->id;
        root->desc = temp->desc;
        root->right = deleteNode(root->right, temp->id);
    }

    return root;
}

// ---------------- DELETE MULTIPLES ----------------
void deleteMultiples(Node* &root, int n, int m) {
    if (!root || m == 0) return;

    // inorder traversal to find multiples
    if (root->left)
        deleteMultiples(root->left, n, m);

    if (m > 0 && root->id % n == 0) {
        int toDelete = root->id;
        root = deleteNode(root, toDelete);
        m--;
    }

    if (root && root->right)
        deleteMultiples(root->right, n, m);
}

// ---------------- MAIN ----------------
int main() {
    Node* root = nullptr;

    // Sample data
    root = insert(root, 10, "A");
    root = insert(root, 20, "B");
    root = insert(root, 30, "C");
    root = insert(root, 40, "D");
    root = insert(root, 50, "E");
    root = insert(root, 60, "F");

    cout << "Initial BST:\n";
    inorder(root);
    cout << "\n\n";

    // ---------------- K RANGE ----------------
    int k = 2;
    cout << "K items in range [10,50]: ";
    printKRange(root, 10, 50, k);
    cout << "\n\n";

    // ---------------- CLOSEST ITEM ----------------
    int target = 43;
    int closest = INT_MAX;
    closestUtil(root, target, closest);

    cout << "Closest item to " << target << " = " << closest << "\n\n";

    // ---------------- DELETE MULTIPLES ----------------
    int n = 20, m = 2;
    deleteMultiples(root, n, m);

    cout << "BST after deleting multiples of " << n << ":\n";
    inorder(root);
    cout << "\n";

    return 0;
}