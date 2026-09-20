#include <iostream>
using namespace std;

class Stack {
private:
    int* arr;
    int topIdx;
    int capacity;

public:
    Stack(int cap) {
        capacity = cap;
        arr = new int[capacity];
        topIdx = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    bool isEmpty() { return topIdx == -1; }
    bool isFull() { return topIdx == capacity - 1; }

    void push(int val) {
        if (isFull()) return;
        arr[++topIdx] = val;
    }

    int pop() {
        if (isEmpty()) return -1;
        return arr[topIdx--];
    }

    int top() {
        if (isEmpty()) return -1;
        return arr[topIdx];
    }
};

void nextGreaterElement(int nums1[], int size1, int nums2[], int size2, int result[]) {
    // 1. Dynamically find maximum value in nums2 to allocate exact array size needed
    int maxVal = 0;
    for (int i = 0; i < size2; i++) {
        if (nums2[i] > maxVal) {
            maxVal = nums2[i];
        }
    }

    // 2. Allocate direct-address lookup array dynamically
    int* nge = new int[maxVal + 1];
    for (int i = 0; i <= maxVal; i++) {
        nge[i] = -1; // Default -1 for all numbers
    }

    Stack st(size2); // Custom stack for monotonic processing

    // 3. Process nums2 left to right
    for (int i = 0; i < size2; i++) {
        int current = nums2[i];

        // While current number is larger than waiting numbers on stack
        while (!st.isEmpty() && current > st.top()) {
            int poppedVal = st.pop();
            nge[poppedVal] = current; // Save answer in master key
        }

        st.push(current);
    }

    // 4. Fill result array matching nums1 query order
    for (int i = 0; i < size1; i++) {
        result[i] = nge[nums1[i]];
    }

    // Free memory
    delete[] nge;
}

int main() {
    int nums2[] = {1, 3, 4, 2};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);

    int nums1[] = {4, 1, 2};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);

    int result[3];

    nextGreaterElement(nums1, size1, nums2, size2, result);

    cout << "Result: [ ";
    for (int i = 0; i < size1; i++) {
        cout << result[i] << " ";
    }
    cout << "]\n"; // Output: [ -1 3 -1 ]

    return 0;
}
