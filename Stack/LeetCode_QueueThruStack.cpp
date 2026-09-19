#include<iostream>
#include<string>
using namespace std;

class Stack{
    int *arr;
    int size;
    int top;
    public:
    Stack(int s){
        size = s;
        arr = new int[size];
        top = 0;
    }
    bool isEmpty(){
        return top == -1;
    }
    bool isFull(){
        return top == size;
    }
    void push(int x){
        if(isFull()){
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[top] = x;
        top++;
    }
    int pop(){
        if(isEmpty()){
            cout << "Queue Underflow!" << endl;
            return -1;
        }
        top--;
        int val = arr[top];
        return val;
    }
    int get_top(){
        if(isEmpty()){return '\0';}
        return arr[top - 1];
    }
    ~Stack(){
        delete[] arr;
    }
};

class Queue{
    Stack s1; //Input stack (push)
    Stack s2; //Output stack (pop)
    int capacity; 
    int count;
    void shift(){
        if(s2.isEmpty()){
            while(!s1.isEmpty()){
                s2.push(s1.pop());
            }
        }
    }
    public:
    bool isEmpty(){
        return count == 0;
    }
    bool isFull(){
        return count == capacity;
    }
    Queue(int size): s1(size), s2(size), capacity(size), count(0){}
    void push(int val){
        if(isFull()){
            cout << "Queue Overflow!" << endl;
            return;
        }
        s1.push(val);
        count++;
    }
    int pop(){
        if(isEmpty()){
            cout << "Queue Underflow!" << endl;
            return -1;
        }
        shift();
        int val = s2.pop();
        count--;
        return val;
    }
    int peek(){
        if(isEmpty()){
            cout << "Queue is empty." << endl;
            return -1;
        }
        shift();
        return s2.get_top();
    }
};

int main() {
    Queue q(2); // Set tiny capacity of 2 for testing

    // Test Underflow
    q.pop(); // Output: Queue Underflow!

    // Fill Queue
    q.push(10);
    q.push(20);

    // Test Overflow
    q.push(30); // Output: Queue Overflow!

    // Valid Operations
    cout << "Popped: " << q.pop() << endl; // Output: 10
    q.push(30);                            // Succeeds now because elementCount became 1

    return 0;
}
