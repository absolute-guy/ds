#include <iostream>
using namespace std;

class HashTable {
    int *table;
    int size;

public:
    HashTable(int s) {
        size = s;
        table = new int[size];

        for (int i = 0; i < size; i++) {
            table[i] = -1; // empty
        }
    }

    // Primary hash
    int hash1(int key) {
        return key % size;
    }

    // Secondary hash (VERY IMPORTANT)
    int hash2(int key) {
        return 1 + (key % (size - 1));
    }

    // INSERT
    void insert(int key) {
        int index1 = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < size; i++) {
            int newIndex = (index1 + i * step) % size;

            if (table[newIndex] == -1 || table[newIndex] == -2) {
                table[newIndex] = key;
                cout << "Inserted " << key << " at " << newIndex << endl;
                return;
            }
        }

        cout << "Table is full!\n";
    }

    // SEARCH
    void search(int key) {
        int index1 = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < size; i++) {
            int newIndex = (index1 + i * step) % size;

            if (table[newIndex] == -1) {
                break;
            }

            if (table[newIndex] == key) {
                cout << "Found at index: " << newIndex << endl;
                return;
            }
        }

        cout << "Not found\n";
    }

    // DELETE
    void remove(int key) {
        int index1 = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < size; i++) {
            int newIndex = (index1 + i * step) % size;

            if (table[newIndex] == -1) {
                break;
            }

            if (table[newIndex] == key) {
                table[newIndex] = -2; // deleted marker
                cout << "Deleted\n";
                return;
            }
        }

        cout << "Not found\n";
    }

    // DISPLAY
    void display() {
        cout << "\nHash Table:\n";
        for (int i = 0; i < size; i++) {
            if (table[i] == -1)
                cout << i << " -> EMPTY\n";
            else if (table[i] == -2)
                cout << i << " -> DELETED\n";
            else
                cout << i << " -> " << table[i] << endl;
        }
    }
};

int main() {
    HashTable h(10);

    // direct operations (no menu)
    h.insert(10);
    h.insert(20);
    h.insert(15);
    h.insert(7);
    h.insert(32);

    h.display();

    h.search(15);
    h.search(99);

    h.remove(20);

    h.display();

    return 0;
}