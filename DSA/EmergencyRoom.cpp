#include <iostream>
#include <string>

using namespace std;

// -------------------------------------------------------------
// CLASS 1: Patient
// Pure class with public members for direct access.
// -------------------------------------------------------------
class Patient {
public:
    string id;
    int severity;

    Patient() : id(""), severity(0) {}
    Patient(string i, int s) : id(i), severity(s) {}
};

// -------------------------------------------------------------
// CLASS 2: ArrayQueue
// Custom FIFO Queue implemented using a Circular Array.
// -------------------------------------------------------------
class ArrayQueue {
private:
    Patient* arr;
    int front;
    int rear;
    int count;
    int capacity;

public:
    ArrayQueue(int cap = 100) {
        capacity = cap;
        arr = new Patient[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~ArrayQueue() {
        delete[] arr;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == capacity;
    }

    void enqueue(Patient p) {
        if (isFull()) {
            cout << "Error: Queue is full! Cannot add patient " << p.id << "\n";
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = p;
        count++;
    }

    Patient dequeue() {
        if (isEmpty()) {
            return Patient("", 0);
        }
        Patient p = arr[front];
        front = (front + 1) % capacity;
        count--;
        return p;
    }
};

// -------------------------------------------------------------
// CLASS 3: EmergencyRoom
// Manages 3 distinct queues for Critical (1), Serious (2), Normal (3)
// -------------------------------------------------------------
class EmergencyRoom {
private:
    ArrayQueue criticalQueue; // Severity 1
    ArrayQueue seriousQueue;  // Severity 2
    ArrayQueue normalQueue;   // Severity 3

public:
    EmergencyRoom(int queueCapacity = 100) 
        : criticalQueue(queueCapacity), 
          seriousQueue(queueCapacity), 
          normalQueue(queueCapacity) {}

    // Adds patient to the appropriate severity queue
    void arrive(const string& id, int severity) {
        Patient p(id, severity);

        if (severity == 1) {
            criticalQueue.enqueue(p);
            cout << "Patient " << id << " (Critical) added to queue.\n";
        } else if (severity == 2) {
            seriousQueue.enqueue(p);
            cout << "Patient " << id << " (Serious) added to queue.\n";
        } else if (severity == 3) {
            normalQueue.enqueue(p);
            cout << "Patient " << id << " (Normal) added to queue.\n";
        } else {
            cout << "Invalid severity level (" << severity << ") for Patient " << id << "!\n";
        }
    }

    // Treats the highest priority patient available
    void treat() {
        if (!criticalQueue.isEmpty()) {
            Patient p = criticalQueue.dequeue();
            cout << ">>> TREATING Patient " << p.id << " [CRITICAL]\n";
        } else if (!seriousQueue.isEmpty()) {
            Patient p = seriousQueue.dequeue();
            cout << ">>> TREATING Patient " << p.id << " [SERIOUS]\n";
        } else if (!normalQueue.isEmpty()) {
            Patient p = normalQueue.dequeue();
            cout << ">>> TREATING Patient " << p.id << " [NORMAL]\n";
        } else {
            cout << ">>> No patients waiting to be treated.\n";
        }
    }
};

// -------------------------------------------------------------
// MAIN FUNCTION
// -------------------------------------------------------------
int main() {
    EmergencyRoom er(100);

    int n;
    cout << "Enter total number of operations: ";
    cin >> n;

    cout << "\nEnter operations (ARRIVE <ID> <SEVERITY> or TREAT):\n";

    for (int i = 0; i < n; i++) {
        string op;
        cin >> op;

        if (op == "ARRIVE") {
            string id;
            int severity;
            cin >> id >> severity;
            er.arrive(id, severity);
        } else if (op == "TREAT") {
            er.treat();
        } else {
            cout << "Unrecognized operation: " << op << "\n";
        }
    }

    return 0;
}
