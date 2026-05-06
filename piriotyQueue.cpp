#include <iostream>
using namespace std;

struct Node {
    int value;
    int priority;
    Node* next;

    Node(int v, int p) {
        value = v;
        priority = p;
        next = NULL;
    }
};

class PriorityQueue {
    Node* front;

public:
    PriorityQueue() {
        front = NULL;
    }

    // Insert function
    void insert(int val, int pri) {
        Node* newNode = new Node(val, pri);

        // Agar queue empty ho ya new node ki priority zyada ho
        if (front == NULL || pri > front->priority) {
            newNode->next = front;
            front = newNode;
        } 
        else {
            Node* temp = front;

            // Correct position find karo
            while (temp->next != NULL && temp->next->priority >= pri) {
                temp = temp->next;
            }

            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    // Remove highest priority
    void remove() {
        if (front == NULL) {
            cout << "Queue empty hai\n";
            return;
        }

        Node* temp = front;
        front = front->next;
        delete temp;
    }

    // Peek (top element)
    int peek() {
        if (front == NULL) {
            cout << "Queue empty hai\n";
            return -1;
        }
        return front->value;
    }

    // Display
    void display() {
        Node* temp = front;
        while (temp != NULL) {
            cout << "(" << temp->value << ", " << temp->priority << ") ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    PriorityQueue pq;

    pq.insert(10, 1);
    pq.insert(20, 3);
    pq.insert(30, 2);

    cout << "Queue: ";
    pq.display();

    cout << "Top: " << pq.peek() << endl;

    pq.remove();

    cout << "After remove: ";
    pq.display();

    return 0;
}