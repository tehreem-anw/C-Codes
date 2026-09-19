#include<iostream>
using namespace std;

class Queue{
    int *arr;
    int rear;
    int front;
    int capacity;
    int count;
    public:
    Queue(int cap){
        capacity = cap;
        arr = new int [capacity];
        rear = front = -1;
        count = 0;
    }
    bool isEmpty(){
        return count == 0;
    }
    bool isFull(){
        return count == capacity;
    }
    int size(){
        return count;
    }
    void enqueue(int val){
        if(isFull()){
            cout << "Queue Overflow!" << endl;
            return;
        }
        if(isEmpty()){
            front = rear = 0;
            
        }
        else{
            rear = (rear + 1) % capacity;
        }
        arr[rear] = val;
        count++;
    }
    int dequeue(){
        if(isEmpty()){
            cout << "Queue Underflow!" << endl;
            return -1;
        }
        int val = arr[front];
        if(front == rear){
            front = rear = -1;
        }
        else{
            front = (front + 1) % capacity;
        }
        count--;
        return val;
    }
    int get_front(){
        if(isEmpty()){
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return arr[front];
    }
    ~Queue(){
        delete[] arr;
    }
};

class Stack{
    Queue q;
    public:
    Stack(int cap): q(cap){}
    void push(int val){
        if(q.isFull()){
            cout << "Stack Overflow!" << endl;
            return;
        }
        q.enqueue(val);
        int existingElements = q.size();
        for(int i = 0; i < existingElements; i++){
            int frontVal = q.dequeue();
            q.enqueue(frontVal);
        }
    }
    int pop(){
        if(q.isEmpty()){
            cout << "Stack Underflow!" << endl;
            return -1;
        }
        return q.dequeue();
    }
    int top(){
        if(q.isEmpty()){
            cout << "Stack is empty." << endl;
            return -1;
        }
        return q.get_front();
    }
};

int main() {
    Stack st(10);

    st.push(10);
    st.push(20);
    st.push(30);

    cout << "Top element: " << st.top() << endl; // Output: 30
    cout << "Popped: " << st.pop() << endl;      // Output: 30
    cout << "Popped: " << st.pop() << endl;      // Output: 20
    cout << "New Top: " << st.top() << endl;     // Output: 10
    cout << "Popped: " << st.pop() << endl;      // Output: 10

    // Test underflow
    st.pop(); // Output: Stack Underflow!

    return 0;
}
