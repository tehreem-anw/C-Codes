#include<iostream>
using namespace std;

class Stack{
    int* st;
    int* minst;
    int capacity;
    int topIdx;
    public:
    Stack(int cap){
        capacity = cap;
        st = new int [capacity];
        minst = new int [capacity];
        topIdx = -1;
    }
    bool isEmpty(){
        return topIdx == -1;
    }
    bool isFull(){
        return topIdx + 1 == capacity;
    }
    void push(int x){
        if(isFull()){
            cout << "Stack Overflow!" << endl;
            return;
        }
        topIdx++;       // Top Index incremented for both
        st[topIdx] = x;     // Pushed into st
        if(topIdx == 0){
            minst[topIdx] = x;
        }
        else{
            int currentMin = minst[topIdx - 1];    // If minst empty
            minst[topIdx] = (x < currentMin) ? x : currentMin;      // Comparing and updating/duplicating min element
        }
    }
    void pop(){
        if(isEmpty()){
            cout << "Stack Underflow!" << endl;
            return;
        }
        topIdx--;   // Tops of both deleted since we had copied the min element and indexing was same
    }
    int top(){
        if(isEmpty()){
            cout << "Stack is empty." << endl;
            return -1;
        }
        return st[topIdx];
    }
    int getMin(){
        if(isEmpty()){
            cout << "Stack is empty." << endl;
            return -1;
        }
        return minst[topIdx];
    }
    ~Stack(){
        delete[] st;
        delete[] minst;
    }
};

int main() {
    Stack minStack(10000);

    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);

    cout << "Current Min: " << minStack.getMin() << endl; // Output: -3

    minStack.pop();

    cout << "Top Element: " << minStack.top() << endl;    // Output: 0
    cout << "Current Min: " << minStack.getMin() << endl; // Output: -2

    return 0;
}
