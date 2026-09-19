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
        return top == 0;
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
        top--;
        int val = arr[top];
        return val;
    }
    char get_top(){
        if(isEmpty()){return '\0';}
        return arr[top-1];
    }
    ~Stack(){
        delete[] arr;
    }
};

int ERP(string tokens[], int size){
    Stack s1(size);
    for(int i = 0; i < size; i++){
        string x = tokens[i];
        // 1. If operator
        if(x == "+" || x == "-" || x == "*" || x == "/"){
            int b = s1.pop();
            int a = s1.pop();
            if(x == "+") {s1.push(a + b);}
            else if(x == "-") {s1.push(a - b);}
            else if(x == "*") {s1.push(a * b);}
            else if(x == "/") {s1.push(a/b);}
        }
        // 2. If number
        else{
            s1.push(stoi(x)); // Integer conversion
        }
    }
    return s1.pop();
}

int main() {
    // Test Case 1: ((2 + 1) * 3) = 9
    string tokens1[] = {"2", "1", "+", "3", "*"};
    int size1 = 5;
    cout << "Result 1: " << ERP(tokens1, size1) << endl; // Output: 9

    // Test Case 2: (4 + (13 / 5)) = 6
    string tokens2[] = {"4", "13", "5", "/", "+"};
    int size2 = 5;
    cout << "Result 2: " << ERP(tokens2, size2) << endl; // Output: 6

    return 0;
}
