#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

typedef struct Node {
    int iValue;
    Node* ptrNext;
} Node;

typedef struct Stack {
    Node* ptrTop;
} Stack;

Stack* newStack();
void pushStack(Stack* const stack, int iValue);

int main() {
    Stack* stack = newStack();

    cout << "A" << endl;
}

Stack* newStack() {
    Stack* temp = (Stack*) malloc(sizeof(Stack));
    temp->ptrTop->ptrNext = nullptr;
    
    return temp;
}

// void pushStack(Stack* const stack, int iValue) {
//     curr

//     if (stack->ptrNext == nullptr) {

//     }

//     while (stack->ptrNext != nullptr) {

//     }
    
// }