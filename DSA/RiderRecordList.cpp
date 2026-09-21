#include <iostream>
#include <string>

using namespace std;

// Node Class for Circular Linked List
class RiderNode {
private:
    int riderID;
    string name;
    int assignedOrders;
    RiderNode* next;

    // Grant CircularRiderList access to private members
    friend class CircularRiderList;

public:
    RiderNode(int id, string n, int orders) {
        riderID = id;
        name = n;
        assignedOrders = orders;
        next = nullptr;
    }

    // Getters and Setters
    int getRiderID() const { 
        return riderID; 
    }
    
    string getName() const { 
        return name; 
    }
    
    int getAssignedOrders() const { 
        return assignedOrders; 
    }
    
    void setAssignedOrders(int orders) { 
        assignedOrders = orders; 
    }
    
    RiderNode* getNext() const { 
        return next; 
    }
};

// Circular Linked List Class
class CircularRiderList {
private:
    RiderNode* head;

public:
    CircularRiderList() {
        head = nullptr;
    }

    // Destructor to prevent memory leaks
    ~CircularRiderList() {
        if (head == nullptr) return;
        
        RiderNode* curr = head;
        RiderNode* nextNode = nullptr;
        
        // Break circle for safe deletion
        do {
            nextNode = curr->next;
            delete curr;
            curr = nextNode;
        } while (curr != head);
        
        head = nullptr;
    }

    // 1. Count total riders
    int countRiders() const {
        if (head == nullptr) return 0;
        
        int count = 0;
        RiderNode* temp = head;
        do {
            count++;
            temp = temp->next;
        } while (temp != head);
        
        return count;
    }

    // 2. Insert at Beginning
    void insertAtBeginning(int id, string name, int orders) {
        RiderNode* newNode = new RiderNode(id, name, orders);
        
        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
            return;
        }

        RiderNode* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }

        newNode->next = head;
        temp->next = newNode;
        head = newNode;
    }

    // 3. Insert at End
    void insertAtEnd(int id, string name, int orders) {
        RiderNode* newNode = new RiderNode(id, name, orders);
        
        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
            return;
        }

        RiderNode* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->next = head;
    }

    // 4. Insert at Specific Position (1-based index)
    void insertAtPosition(int pos, int id, string name, int orders) {
        int total = countRiders();

        if (pos < 1 || pos > total + 1) {
            cout << "Invalid Position!\n";
            return;
        }

        if (pos == 1) {
            insertAtBeginning(id, name, orders);
            return;
        }

        if (pos == total + 1) {
            insertAtEnd(id, name, orders);
            return;
        }

        RiderNode* newNode = new RiderNode(id, name, orders);
        RiderNode* temp = head;

        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // 5. Delete from Beginning
    void deleteFromBeginning() {
        if (head == nullptr) {
            cout << "List is empty!\n";
            return;
        }

        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }

        RiderNode* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }

        RiderNode* toDelete = head;
        head = head->next;
        temp->next = head;
        delete toDelete;
    }

    // 6. Delete from End
    void deleteFromEnd() {
        if (head == nullptr) {
            cout << "List is empty!\n";
            return;
        }

        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }

        RiderNode* temp = head;
        RiderNode* prev = nullptr;

        while (temp->next != head) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = head;
        delete temp;
    }

    // 7. Delete from Specific Position
    void deleteFromPosition(int pos) {
        int total = countRiders();

        if (pos < 1 || pos > total) {
            cout << "Invalid Position!\n";
            return;
        }

        if (pos == 1) {
            deleteFromBeginning();
            return;
        }

        RiderNode* temp = head;
        RiderNode* prev = nullptr;

        for (int i = 1; i < pos; i++) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
        delete temp;
    }

    // 8. Search for a Rider by ID
    RiderNode* searchRider(int id) const {
        if (head == nullptr) return nullptr;

        RiderNode* temp = head;
        do {
            if (temp->riderID == id) return temp;
            temp = temp->next;
        } while (temp != head);

        return nullptr;
    }

    // 9. Update Rider Information
    void updateRider(int id, int newOrders) {
        RiderNode* rider = searchRider(id);
        if (rider != nullptr) {
            rider->setAssignedOrders(newOrders);
            cout << "Rider ID " << id << " updated successfully!\n";
        } else {
            cout << "Rider with ID " << id << " not found!\n";
        }
    }

    // 10. Display All Riders
    void displayAll() const {
        if (head == nullptr) {
            cout << "No riders in the circular list.\n";
            return;
        }

        RiderNode* temp = head;
        cout << "\n--- KFC Delivery Riders ---\n";
        do {
            cout << "ID: " << temp->riderID << " | Name: " << temp->name 
                 << " | Orders: " << temp->assignedOrders << "\n";
            temp = temp->next;
        } while (temp != head);
    }

    // 11. Traverse starting from a selected rider ID
    void traverseFromRider(int startID) const {
        RiderNode* startNode = searchRider(startID);

        if (startNode == nullptr) {
            cout << "Rider ID " << startID << " not found!\n";
            return;
        }

        cout << "\nTraversing circular list starting from Rider ID " << startID << ":\n";
        RiderNode* temp = startNode;
        do {
            cout << "ID: " << temp->riderID << " | Name: " << temp->name 
                 << " | Orders: " << temp->assignedOrders << "\n";
            temp = temp->next;
        } while (temp != startNode);
    }
};

int main() {
    CircularRiderList kfcRiders;

    // Insertion Demonstrations
    kfcRiders.insertAtEnd(101, "Ali", 3);
    kfcRiders.insertAtEnd(102, "Bilal", 5);
    kfcRiders.insertAtBeginning(100, "Zaid", 2);
    kfcRiders.insertAtPosition(2, 103, "Usman", 4);

    kfcRiders.displayAll();
    cout << "Total Riders: " << kfcRiders.countRiders() << "\n";

    // Traversal from specific rider
    kfcRiders.traverseFromRider(103);

    // Update Rider
    kfcRiders.updateRider(102, 8);

    // Deletion Demonstrations
    cout << "\nDeleting from beginning...\n";
    kfcRiders.deleteFromBeginning();

    cout << "Deleting from end...\n";
    kfcRiders.deleteFromEnd();

    kfcRiders.displayAll();

    return 0;
}
