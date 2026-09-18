#include <iostream>
using namespace std;

// Node structure for linked list
struct Node {
    char data;
    Node* next;

    Node(char val) {
        data = val;
        next = nullptr;
    }
};

class DynamicQueue {
private:
    Node* front; // Points to the first item (head)
    Node* rear;  // Points to the last item (tail)
    int number;  // Tracks total number of elements

public:
    // Constructor
    DynamicQueue() {
        front = nullptr;
        rear = nullptr;
        number = 0;
    }

    // Destructor to free all allocated memory
    ~DynamicQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Check if queue is empty[cite: 4]
    bool isEmpty() {
        return front == nullptr;
    }

    // Dynamic queue is never full as long as heap memory is available[cite: 4]
    bool isFull() {
        return false;
    }

    // Enqueue: Adds an item to the rear[cite: 4]
    void enqueue(char x) {
        Node* newNode = new Node(x);
        
        if (isEmpty()) {
            front = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        
        number++;
        cout << "Enqueued: " << x << endl;
    }

    // Dequeue: Removes and returns item from front[cite: 4]
    char dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow!\n"; // Underflow check[cite: 4]
            return '\0';
        }

        Node* temp = front;
        char x = temp->data;
        front = front->next; // Move front pointer to the next node[cite: 4]

        // If the queue becomes empty after removal, reset rear to nullptr[cite: 4]
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp; // Free memory
        number--;
        return x;
    }

    // Peek at the front element without removing it[cite: 4]
    char getFront() {
        if (isEmpty()) {
            cout << "Queue is Empty!\n";
            return '\0';
        }
        return front->data;
    }

    // Peek at the rear element without removing it[cite: 4]
    char getRear() {
        if (isEmpty()) {
            cout << "Queue is Empty!\n";
            return '\0';
        }
        return rear->data;
    }

    // Returns active element count
    int getCount() {
        return number;
    }
};

int main() {
    DynamicQueue q;

    q.enqueue('E');
    q.enqueue('K');
    q.enqueue('G');

    cout << "Front item: " << q.getFront() << endl; // Output: E
    cout << "Rear item: " << q.getRear() << endl;   // Output: G

    cout << "Dequeued: " << q.dequeue() << endl;   // Removes E
    cout << "New Front item: " << q.getFront() << endl; // Output: K

    return 0;
}
