#include <iostream>
using namespace std;

const int SIZE = 101;

class HashTable {
private:
    struct Entry {
        int sum;
        int a, b;
        bool occupied;
    };

    Entry table[SIZE];

    int hash(int key) {
        return abs(key) % SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            table[i].occupied = false;
        }
    }

    bool insert(int sum, int a, int b, int &x1, int &y1, int &x2, int &y2) {
        int idx = hash(sum);

        while (table[idx].occupied) {

            if (table[idx].sum == sum) {
                int p1 = table[idx].a;
                int p2 = table[idx].b;

                // ensure all elements are distinct
                if (p1 != a && p1 != b && p2 != a && p2 != b) {
                    x1 = p1; y1 = p2;
                    x2 = a;  y2 = b;
                    return true;
                }
                return false;
            }

            idx = (idx + 1) % SIZE;
        }

        table[idx].sum = sum;
        table[idx].a = a;
        table[idx].b = b;
        table[idx].occupied = true;

        return false;
    }
};

// ---------------- MAIN ----------------
int main() {
    int arr[] = {3, 4, 7, 1, 2, 9, 8};
    int n = 7;

    HashTable ht;

    bool found = false;
    int x1, y1, x2, y2;

    for (int i = 0; i < n && !found; i++) {
        for (int j = i + 1; j < n && !found; j++) {

            int sum = arr[i] + arr[j];

            if (ht.insert(sum, arr[i], arr[j], x1, y1, x2, y2)) {
                found = true;

                cout << "(" << x1 << ", " << y1 << ") and ("
                     << x2 << ", " << y2 << ")\n";
            }
        }
    }

    if (!found) {
        cout << "No pairs found\n";
    }

    return 0;
}