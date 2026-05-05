#include <iostream>
using namespace std;

// 📌 Node
class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = NULL;
    }
};

class HashTable {
    int size;
    Node** table;
    int totalElements;

public:
    HashTable(int s) {
        size = s;
        table = new Node*[size];
        totalElements = 0;

        for (int i = 0; i < size; i++)
            table[i] = NULL;
    }

    // 🔑 Hash Function
    int hashFunction(int key) {
        return key % size;
    }

    // ➕ INSERT (at END)
    void insert(int key) {
        int index = hashFunction(key);
        Node* newNode = new Node(key);

        if (table[index] == NULL) {
            table[index] = newNode;
        }
        else {
            Node* temp = table[index];

            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newNode;
        }

        totalElements++;
    }

    // 🔍 SEARCH
    bool search(int key) {
        int index = hashFunction(key);

        Node* temp = table[index];

        while (temp != NULL) {
            if (temp->data == key)
                return true;
            temp = temp->next;
        }

        return false;
    }

    // ❌ DELETE
    void remove(int key) {
        int index = hashFunction(key);

        Node* curr = table[index];
        Node* prev = NULL;

        while (curr != NULL) {
            if (curr->data == key) {
                if (prev == NULL)
                    table[index] = curr->next;
                else
                    prev->next = curr->next;

                delete curr;
                totalElements--;
                return;
            }

            prev = curr;
            curr = curr->next;
        }
    }

    // ✏️ UPDATE (replace old value with new value)
    void update(int oldKey, int newKey) {
        int index = hashFunction(oldKey);

        Node* temp = table[index];

        while (temp != NULL) {
            if (temp->data == oldKey) {
                temp->data = newKey;
                return;
            }
            temp = temp->next;
        }
    }

    // 📊 DISPLAY
    void display() {
        for (int i = 0; i < size; i++) {
            cout << i << " -> ";

            Node* temp = table[i];

            while (temp != NULL) {
                cout << temp->data << " -> ";
                temp = temp->next;
            }

            cout << "NULL" << endl;
        }
    }

    // 📌 TOTAL ELEMENTS
    int count() {
        return totalElements;
    }

    // 🧹 CLEAR TABLE
    void clear() {
        for (int i = 0; i < size; i++) {
            Node* temp = table[i];

            while (temp != NULL) {
                Node* del = temp;
                temp = temp->next;
                delete del;
            }

            table[i] = NULL;
        }

        totalElements = 0;
    }

    // ❓ CHECK EMPTY
    bool isEmpty() {
        return totalElements == 0;
    }
};

// ---------------- MAIN ----------------
int main() {
    HashTable ht(5);

    ht.insert(10);
    ht.insert(15);
    ht.insert(20);
    ht.insert(25);
    ht.insert(30);

    cout << "Initial Table:\n";
    ht.display();

    cout << "\nSearch 20: " << (ht.search(20) ? "Found" : "Not Found") << endl;

    ht.update(20, 99);
    cout << "\nAfter Update (20 -> 99):\n";
    ht.display();

    ht.remove(15);
    cout << "\nAfter Deletion:\n";
    ht.display();

    cout << "\nTotal Elements: " << ht.count() << endl;

    cout << "\nIs Empty? " << (ht.isEmpty() ? "Yes" : "No") << endl;

    ht.clear();
    cout << "\nAfter Clear:\n";
    ht.display();

    return 0;
}