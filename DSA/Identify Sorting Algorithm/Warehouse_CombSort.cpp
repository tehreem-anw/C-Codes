#include <iostream>

using namespace std;

// Function to perform Comb Sort
void combSort(int arr[], int n) {
    int gap = n;
    double shrink = 1.3;
    bool swapped = true;
    int pass = 1;

    // Continue loop while gap is greater than 1 or a swap occurred in the last pass
    while (gap > 1 || swapped) {
        // Gap calculation using your notebook logic
        gap = (gap / shrink < 1.0) ? 1 : gap / shrink;

        swapped = false;

        // Compare elements separated by the current gap
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                // Swap elements in-place
                int temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;

                swapped = true;
            }
        }

        // Display gap and array state after each pass
        cout << "Pass " << pass++ << " (Gap = " << gap << "): ";
        for (int k = 0; k < n; k++) {
            cout << arr[k] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of packages: ";
    cin >> n;

    // Dynamically allocate memory for input weights
    int* weights = new int[n];

    cout << "Enter package weights:\n";
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    // Display original input array
    cout << "\nOriginal array: ";
    for (int i = 0; i < n; i++) {
        cout << weights[i] << " ";
    }
    cout << "\n\n--- Sorting Process ---\n";

    // Perform Comb Sort
    combSort(weights, n);

    // Display final sorted array
    cout << "\nFinal sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << weights[i] << " ";
    }
    cout << endl;

    // Free allocated memory
    delete[] weights;

    return 0;
}
