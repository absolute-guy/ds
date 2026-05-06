#include <iostream>
#include <algorithm>
using namespace std;

// ---------------- NODE (HASH ENTRY) ----------------
struct Entry {
    int mark;
    int freq;
    bool occupied;
};

// ---------------- HASH TABLE ----------------
class HashTable {
    Entry* table;
    int size;
    int count;

public:
    HashTable(int s) {
        size = s;
        table = new Entry[size];
        count = 0;

        for (int i = 0; i < size; i++) {
            table[i].occupied = false;
            table[i].freq = 0;
            table[i].mark = 0;
        }
    }

    int h1(int key) {
        return key % size;
    }

    int h2(int key) {
        return 1 + (key % (size - 1));
    }

    float loadFactor() {
        return (float)count / size;
    }

    void insert(int key);
    void rehash();
    void print();
};

// ---------------- INSERT ----------------
void HashTable::insert(int key) {
    if (loadFactor() > 0.7)
        rehash();

    int idx = h1(key);
    int step = h2(key);
    int i = 0;

    while (table[(idx + i * step) % size].occupied &&
           table[(idx + i * step) % size].mark != key) {
        i++;
    }

    int pos = (idx + i * step) % size;

    if (!table[pos].occupied) {
        table[pos].mark = key;
        table[pos].freq = 1;
        table[pos].occupied = true;
        count++;
    } else {
        table[pos].freq++;
    }
}

// ---------------- REHASH ----------------
void HashTable::rehash() {
    int oldSize = size;
    Entry* oldTable = table;

    size = size * 2;
    table = new Entry[size];
    count = 0;

    for (int i = 0; i < size; i++) {
        table[i].occupied = false;
        table[i].freq = 0;
        table[i].mark = 0;
    }

    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i].occupied) {
            for (int j = 0; j < oldTable[i].freq; j++)
                insert(oldTable[i].mark);
        }
    }

    delete[] oldTable;
}



// ---------------- MERGE SORT HELPERS ----------------
void merge(int mark[], int freq[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* Lm = new int[n1];
    int* Lf = new int[n1];
    int* Rm = new int[n2];
    int* Rf = new int[n2];

    for (int i = 0; i < n1; i++) {
        Lm[i] = mark[l + i];
        Lf[i] = freq[l + i];
    }

    for (int i = 0; i < n2; i++) {
        Rm[i] = mark[m + 1 + i];
        Rf[i] = freq[m + 1 + i];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (Lf[i] < Rf[j] ||
           (Lf[i] == Rf[j] && Lm[i] < Rm[j])) {
            mark[k] = Lm[i];
            freq[k] = Lf[i];
            i++;
        } else {
            mark[k] = Rm[j];
            freq[k] = Rf[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        mark[k] = Lm[i];
        freq[k] = Lf[i];
        i++; k++;
    }

    while (j < n2) {
        mark[k] = Rm[j];
        freq[k] = Rf[j];
        j++; k++;
    }

    delete[] Lm;
    delete[] Lf;
    delete[] Rm;
    delete[] Rf;
}

void mergeSort(int mark[], int freq[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(mark, freq, l, m);
        mergeSort(mark, freq, m + 1, r);
        merge(mark, freq, l, m, r);
    }
}

// ---------------- PRINT ----------------
void HashTable::print() {
    int mark[100];
    int freq[100];
    int n = 0;

    for (int i = 0; i < size; i++) {
        if (table[i].occupied) {
            mark[n] = table[i].mark;
            freq[n] = table[i].freq;
            n++;
        }
    }

    mergeSort(mark, freq, 0, n - 1);

    cout << "Sorted Marks by Frequency:\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << mark[i]
             << ": " << freq[i] << " students\n";
    }
}

// ---------------- MAIN ----------------
int main() {
    int marks[] = {85, 90, 75, 85, 60, 90, 85, 75};
    int n = 8;

    HashTable ht(7);

    for (int i = 0; i < n; i++)
        ht.insert(marks[i]);

    ht.print();

    return 0;
}