#include<iostream>
using namespace std;

struct Node{
    char data;
    Node* next;
};

class DynamicStack{
    Node* top;
    public:
    DynamicStack(){
        top = NULL;
    }
    bool isEmpty(){
        return top == NULL;
    }
    void push(char x){
        Node* newNode = new Node();
        newNode->data = x;
        newNode->next = top;
        top = newNode;
    }
    void pop(char &x){
        if(isEmpty()){
            cout << "Stack Underflow!" << endl;
            return;
        }
        Node* temp = top;
        x = top->data;
        top = top->next;
        delete temp;
    }
    char get_top(){
        if(isEmpty()){
            cout << "Stack is empty!" << endl;
            return '\0';
        }
        return top->data;
    }
    ~DynamicStack(){
        while(!isEmpty()){
            char xyz;
            pop(xyz);
        }
    }
};
