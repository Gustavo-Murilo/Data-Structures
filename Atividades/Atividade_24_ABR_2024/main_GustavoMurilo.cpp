// College Assignament
// Subject: Data Strcutures
// Student: Gustavo Murilo Cavalcante Carvalho

#include <iostream>

using namespace std;

typedef struct Node{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void insertFront(Node**, int);
void insertEnd(Node**, int);
void insertAfter(Node*, int);
void deleteNode(Node**, Node*);
void displayList(Node*);

// Exercícios
void InsertBefore(Node*, int);
void deleteNodebyValue(Node**, int);
Node* searchNodebyValue(Node**, int);


// ==================== FEITO EM SALA ====================

int main(){
    Node* head = nullptr;
    displayList(head);
    cout << "=================================" << endl;
    insertEnd(&head, 0);
    insertEnd(&head, 1);
    insertEnd(&head, 2);
    insertEnd(&head, 5);
    insertEnd(&head, 7);
    insertEnd(&head, 42);
    // displayList(head);   
    // insertFront(&head, 13);
    // displayList(head);  
    // deleteNode(&head, head->ptrNext->ptrNext);
    // displayList(head); 
}

Node* createNode(int iPayload){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->iPayload = iPayload;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;

    return temp;
}

void displayList(Node* node){
    if(node == nullptr)
    {
        cout << "Lista Vazia: não é possível realizar displayList" << endl;
        return;
    }
    if (node->ptrPrev != nullptr)
    {
        cout << "Meio ou fim da Lista: Não é possível realizar displayList" << endl;
        return;
    }

    Node* temp = node;

    cout << "Payload: ";

    // Percorremos a lista até seu fim (ptrNext do último nó é NULL)
    while (temp != nullptr)
    {
        cout << temp->iPayload << " ";
        temp = temp->ptrNext;
    }

    cout << endl;
}

void insertFront(Node** head, int iPayload){
    Node* newNode = createNode(iPayload);
    //newNode->ptrPrev = nullptr;

    if (*head != nullptr)
    {
        (*head)->ptrPrev = newNode;
        newNode->ptrNext = (*head);
        (*head) = newNode;
        return;
    }

    (*head) = newNode;
}

void insertEnd(Node** head, int iPayload){
    Node* newNode = createNode(iPayload);
    //newNode->ptrNext = nullptr;

    if(*head == nullptr)
    {
        //newNode->ptrPrev = nullptr;
        (*head) = newNode;
        return;
    }
    Node* temp = (*head);

    // Prercorremos a lista até seu fim (ptrNext do último nó é NULL)
    while(temp->ptrNext != nullptr) temp = temp->ptrNext;

    newNode->ptrPrev = temp; //newNode aponta para o fim da lista
    temp->ptrNext = newNode; // antigo último elemento aponta para o novo nó
}

void insertAfter(Node* ptrLocation, int iPayload)
{
    if (ptrLocation == nullptr)
    {
        cout << "Location é NULL." << endl;
        return;
    }
    Node* newNode = createNode(iPayload);

    //Corrigir nó a ser inserido
    newNode->ptrNext = ptrLocation->ptrNext;
    newNode->ptrPrev = ptrLocation;

    //Corrigir o ponto de inserção
    ptrLocation->ptrNext = newNode;

    if(newNode->ptrNext != nullptr) newNode->ptrNext->ptrPrev = newNode;
}

void deleteNode(Node** head, Node* ptrDelete)
{
    if (*head == nullptr || ptrDelete == nullptr)
    {
        cout << "Não foi possível remover." << endl;
        return;
    }

    //Caso o ptrDelete seja o primeiro elemento da lista
    if(*head == ptrDelete) (*head) = ptrDelete->ptrNext;

    //Se o ptrDelete não é o último nó
    if(ptrDelete->ptrNext != nullptr) ptrDelete->ptrNext->ptrPrev = ptrDelete->ptrPrev;

    //Se o ptrDelete não é o primeiro nó
    if(ptrDelete->ptrPrev != nullptr) ptrDelete->ptrPrev->ptrNext = ptrDelete->ptrNext;

    free(ptrDelete);
}

// ============================ EXERCÍCIOS ============================

// Exercício 1. Elaborar a função void insertBefore(Node*, int);
void insertBefore(Node* ptrLocation, int iData) {
    if (ptrLocation == nullptr) {
        cout << "O ponteiro fornecido é NULL" << endl;
        return;
    }

    Node* ptrNew = createNode(iData);

    // Altera os elementos "vizinhos" do novo nó
    ptrNew->ptrPrev = ptrLocation->ptrPrev;
    ptrNew->ptrNext = ptrLocation;
    
    // Altera os elementos "vizinhos" do nós que já estavam na lista
    if (ptrLocation->ptrPrev != nullptr) {
        ptrLocation->ptrPrev->ptrNext = ptrNew;
    }
    ptrLocation->ptrPrev = ptrNew;
}

// Exercício 2. Elaborar a função void deleteNodebyValue(Node**, int);
void deleteNodebyValue(Node** ptrLocation, int iData) {
    Node* ptrFound = searchNodebyValue(ptrLocation, iData);

    if (ptrFound == nullptr) {
        cout << "A lista não possui um nó com esse valor" << endl;
        return;
    }

    deleteNode(ptrLocation, ptrFound);
}


// Exercício 3. Elaborar a função Node* searchNodebyValue(Node**, int);
Node* searchNodebyValue(Node** ptrLocation, int iData) {
    if (*ptrLocation == nullptr) {
        cout << "Lista Vazia: não é possível procurar o nó" << endl;
        return nullptr;
    }
    
    Node* ptrUp = *ptrLocation;
    Node* ptrDown = (*ptrLocation)->ptrPrev;

    // Percorre a lista para frente em busca do nó
    while (ptrUp != nullptr) {
        if (ptrUp->iPayload == iData) {
            return ptrUp; // Retorna o nó encontrado
        }
        ptrUp = ptrUp->ptrNext;
    }

    // Percorre a lista para trás em busca do nó
    while (ptrDown != nullptr) {
        if (ptrDown->iPayload == iData) {
            return ptrDown; // Retorna o nó encontrado
        }
        ptrDown = ptrDown->ptrPrev;
    }    

    // Caso não ache o nó, informa o ocorrido e retorna NULL
    cout << "Nó não encontrado" << endl;
    return nullptr;
}