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
            table[i] = -1;
        }
    }

    int hashFunc(int key) {
        return key % size;
    }

    // INSERT
    void insert(int key) {
        int index = hashFunc(key);
        int start = index;

        while (table[index] != -1 && table[index] != -2) {
            index = (index + 1) % size;

            if (index == start) {
                cout << "Table full!\n";
                return;
            }
        }

        table[index] = key;
    }

    // SEARCH
    void search(int key) {
        int index = hashFunc(key);
        int start = index;

        while (table[index] != -1) {
            if (table[index] == key) {
                cout << "Found at index: " << index << endl;
                return;
            }

            index = (index + 1) % size;

            if (index == start) break;
        }

        cout << "Not found\n";
    }

    // DELETE
    void remove(int key) {
        int index = hashFunc(key);
        int start = index;

        while (table[index] != -1) {
            if (table[index] == key) {
                table[index] = -2;
                cout << "Deleted\n";
                return;
            }

            index = (index + 1) % size;

            if (index == start) break;
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
    HashTable h(7);

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