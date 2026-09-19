#include<iostream>
#include<string>
using namespace std;

class Stack{
    char *arr;
    int size;
    int top;
    public:
    Stack(int s){
        size = s;
        arr = new char[size];
        top = 0;
    }
    bool isEmpty(){
        return top == 0;
    }
    bool isFull(){
        return top == size;
    }
    void push(char x){
        if(isFull()){
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[top] = x;
        top++;
    }
    void pop(){
        if(isEmpty()){
            cout << "Stack Underflow!" << endl;
            return; 
        }
        top--;
    }
    char get_top(){
        if(isEmpty()){return '\0';}
        return arr[top-1];
    }
};
bool validParenthesis(string str){
    int n = str.length();
    Stack s1(n);
    for(int i = 0; i < n; i++){
        char x = str[i];
        // 1. Opening Bracket
        if(x == '{' || x == '[' || x == '('){
            s1.push(x);
        }
        // 2. Closing Bracket
        else{
            // A) More Closing than Opening
            if(s1.isEmpty()){
                return false;
            }
            // B) Match top with current Closing
            char topChar = s1.get_top();
            if(topChar == '(' && x == ')' || topChar == '[' && x == ']' || topChar == '{' && x == '}'){
                s1.pop();
            }
            else{
                return false;
            }
        }
    }
    return s1.isEmpty();
}
int main() {
    string s1 = "()[{}]";
    string s2 = "([)]";

    cout << s1 << " : " << (validParenthesis(s1) ? "Valid" : "Invalid") << endl; // Output: Valid
    cout << s2 << " : " << (validParenthesis(s2) ? "Valid" : "Invalid") << endl; // Output: Invalid

    return 0;
}
