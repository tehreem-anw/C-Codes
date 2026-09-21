#include <iostream>
#include <string>

using namespace std;

// -------------------------------------------------------------
// CLASS 1: ProductNode
// -------------------------------------------------------------
class ProductNode {
public:
    int id;
    string name;
    string category;
    double price;
    ProductNode* next;

    ProductNode(int i, string n, string c, double p) 
        : id(i), name(n), category(c), price(p), next(nullptr) {}
};

// -------------------------------------------------------------
// CLASS 2: ProductList
// -------------------------------------------------------------
class ProductList {
private:
    // RECURSIVE HELPER FUNCTION
    ProductNode* mergeRecursive(ProductNode* p1, ProductNode* p2) {
        // Base cases
        if (p1 == nullptr) return p2;
        if (p2 == nullptr) return p1;

        if (p1->id < p2->id) {
            p1->next = mergeRecursive(p1->next, p2);
            return p1;
        } 
        else if (p2->id < p1->id) {
            p2->next = mergeRecursive(p1, p2->next);
            return p2;
        } 
        else {
            // Duplicate Product ID encountered!
            if (p1->price <= p2->price) {
                // Keep p1, delete p2
                ProductNode* p2Next = p2->next;
                delete p2; 
                p1->next = mergeRecursive(p1->next, p2Next);
                return p1;
            } else {
                // Keep p2, delete p1
                ProductNode* p1Next = p1->next;
                delete p1; 
                p2->next = mergeRecursive(p1Next, p2->next);
                return p2;
            }
        }
    }

public:
    ProductNode* head;

    ProductList() : head(nullptr) {}

    ~ProductList() {
        clear();
    }

    void clear() {
        ProductNode* curr = head;
        while (curr != nullptr) {
            ProductNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
    }

    // Inserts node while keeping list sorted by Product ID
    void insertSorted(int id, string name, string category, double price) {
        ProductNode* newNode = new ProductNode(id, name, category, price);

        if (head == nullptr || id < head->id) {
            newNode->next = head;
            head = newNode;
            return;
        }

        ProductNode* curr = head;
        while (curr->next != nullptr && curr->next->id < id) {
            curr = curr->next;
        }

        newNode->next = curr->next;
        curr->next = newNode;
    }

    void display() const {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        ProductNode* curr = head;
        while (curr != nullptr) {
            cout << "ID: " << curr->id 
                 << " | Name: " << curr->name 
                 << " | Category: " << curr->category 
                 << " | Price: $" << curr->price << "\n";
            curr = curr->next;
        }
    }

    int getCount() const {
        int count = 0;
        ProductNode* curr = head;
        while (curr != nullptr) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    double getTotalValue() const {
        double total = 0.0;
        ProductNode* curr = head;
        while (curr != nullptr) {
            total += curr->price;
            curr = curr->next;
        }
        return total;
    }

    // Public method to kick off the recursive merge
    void mergeSorted(ProductList& list1, ProductList& list2) {
        clear();
        head = mergeRecursive(list1.head, list2.head);

        // Disown nodes from branch lists so they aren't deleted twice
        list1.head = nullptr;
        list2.head = nullptr;
    }
};

// -------------------------------------------------------------
// HELPER & MAIN
// -------------------------------------------------------------
void populateBranch(ProductList& branch, const string& branchName) {
    int count;
    cout << "Enter number of products for " << branchName << ": ";
    cin >> count;

    for (int i = 0; i < count; i++) {
        int id;
        string name, category;
        double price;

        cout << "\nProduct " << (i + 1) << " Details:\n";
        cout << "Product ID: ";
        cin >> id;
        cin.ignore();
        cout << "Product Name: ";
        getline(cin, name);
        cout << "Category: ";
        getline(cin, category);
        cout << "Price: $";
        cin >> price;

        branch.insertSorted(id, name, category, price);
    }
}

int main() {
    ProductList glowCare;
    ProductList beautyHub;
    ProductList masterList;

    cout << "=== BRANCH 1: GLOWCARE ===\n";
    populateBranch(glowCare, "GlowCare");

    cout << "\n=== BRANCH 2: BEAUTYHUB ===\n";
    populateBranch(beautyHub, "BeautyHub");

    cout << "\n=== GlowCare List ===\n";
    glowCare.display();

    cout << "\n=== BeautyHub List ===\n";
    beautyHub.display();

    // Perform recursive merge
    masterList.mergeSorted(glowCare, beautyHub);

    cout << "\n=== FINAL MASTER LIST ===\n";
    masterList.display();

    cout << "\nTotal Remaining Products: " << masterList.getCount() << "\n";
    cout << "Total Inventory Value: $" << masterList.getTotalValue() << "\n";

    return 0;
}
