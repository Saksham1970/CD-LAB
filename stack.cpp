#include <iostream>
using namespace std;

class Stack {
    private:
        static const int maxSize = 100;	// Maximum size of the stack
        int arr[maxSize]; // Array to store stack elements
        int top; // Index of the top element
        
    public:
        Stack() {
            top = -1; // Initialize top to -1 (empty stack)
        }
    
    // Function to push an element onto the stack
    void push(int value) {
        if (top >= maxSize - 1) {
        cout << "Stack Overflow. Cannot push " << value << "." << endl;
        return;
        }
        arr[++top] = value;
    }
    
    // Function to pop an element from the stack
    void pop() {
        if (isEmpty()) {
        cout << "Stack Underflow. Cannot pop from an empty stack." << endl;
        return;
        }
        top--;
    }
    
    // Function to get the top element of the stack
    int peek() {
        if (isEmpty()) {
        cout << "Stack is empty." << endl;
        return -1;
        }
        return arr[top];
    }
    
    // Function to check if the stack is empty
    bool isEmpty() {
        return top == -1;
    }
};

int main() {
    Stack myStack;
    myStack.push(5);
    myStack.push(10);
    myStack.push(15);
    cout << "Top element: " << myStack.peek() << endl;
    myStack.pop();
    cout << "Top element after pop: " << myStack.peek() << endl;
    myStack.pop();
    cout << "Top element after pop: " << myStack.peek() << endl;
    myStack.pop();
    cout << "Top element after pop: " << myStack.peek() << endl;
    return 0;
}
