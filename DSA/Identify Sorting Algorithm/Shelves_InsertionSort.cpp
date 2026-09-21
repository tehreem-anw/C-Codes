#include <iostream>
using namespace std;

// Function to perform Insertion Sort on dynamic array
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Function to print array elements
void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of shelves: ";
    cin >> n;

    // Dynamically allocate initial array
    int* shelves = new int[n];

    cout << "Enter book capacity of each shelf:\n";
    for (int i = 0; i < n; i++) {
        cin >> shelves[i];
    }

    int pos, newCapacity;
    cout << "Enter position to add the new shelf (0 to " << n << "): ";
    cin >> pos;

    cout << "Enter capacity of the new shelf: ";
    cin >> newCapacity;

    // Validate position index
    if (pos < 0 || pos > n) {
        cout << "Invalid insertion position!" << endl;
        delete[] shelves;
        return 1;
    }

    // Allocate a larger dynamic array (n + 1)
    int* newShelves = new int[n + 1];

    // Copy elements and insert the new shelf at specified position
    for (int i = 0; i < pos; i++) {
        newShelves[i] = shelves[i];
    }
    
    newShelves[pos] = newCapacity;

    for (int i = pos; i < n; i++) {
        newShelves[i + 1] = shelves[i];
    }

    // Free memory of original array
    delete[] shelves;

    // Output Original shelf state (as placed after insertion)
    cout << "\nOriginal shelf capacities: ";
    for (int i = 0; i < n; i++) {
        // Displaying original entries before insertion for display exactness
        if (i < pos) cout << newShelves[i] << " ";
        else cout << newShelves[i + 1] << " ";
    }
    cout << endl;

    cout << "Shelves after adding new shelf: ";
    printArray(newShelves, n + 1);

    // Apply Insertion Sort
    insertionSort(newShelves, n + 1);

    cout << "Shelves after sorting: ";
    printArray(newShelves, n + 1);

    // Deallocate new array
    delete[] newShelves;

    return 0;
}
