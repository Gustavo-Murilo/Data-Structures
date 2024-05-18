#include<iostream>

using std::cout;
using std::endl;


// ---------------- Estruturas ----------------
typedef struct Node
{
    int iID;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

typedef struct CircleList
{
    Node* ptrHead;
} CircleList;


// ---------------- Assinaturas das funções ---------------- 
// item 1-a 
Node* createNode(int);
CircleList* createListByArray(int, int*);
int nextTheList(CircleList*);
int backTheList(CircleList*);
// item 1-b
void deleteNode(CircleList*, int);
void deleteList(CircleList*);
// item 1-c
CircleList* appendLists(CircleList*, CircleList*);
// item 2
// item 3

// ---------------- Main ---------------- 
int main()
{
    int arriValues_1[4] = {1, 2, 3, 4};
    int iSize_1 = sizeof(arriValues_1) / sizeof(int);
    
    CircleList* CList_1 = createListByArray(iSize_1, arriValues_1);
    
    cout<< endl;
    for (int i = 0; i <= iSize_1; i++)
    {
        cout << nextTheList(CList_1) << ", ";
    }
    
    cout<< endl;
    for (int i = 0; i <= iSize_1; i++)
    {
        cout << backTheList(CList_1) << ", ";
    }
    cout<< endl;
    
    return 0;
}


// ---------------- Definição das funções ---------------- 
// ======= Item 1-a =======
Node* createNode(int iValue)
{
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->iID = iValue;
    newNode->ptrNext = nullptr;
    newNode->ptrPrev = nullptr;
    
    return newNode;
}

CircleList* createListByArray(int iSize, int* arriValues)
{
    CircleList* ptrCList = (CircleList*) malloc(sizeof(CircleList));
    ptrCList->ptrHead = createNode(arriValues[0]);
    
    // Cria ponteiros auxiliares
    Node* ptrCurr = ptrCList->ptrHead;
    Node* ptrTemp;
    
    // Adiciona os outros nós
    for (int iIndex = 1; iIndex < iSize; iIndex++)
    {
        ptrTemp = createNode(arriValues[iIndex]);
        ptrCurr->ptrNext = ptrTemp;
        ptrTemp->ptrPrev = ptrCurr;
        
        ptrCurr = ptrCurr->ptrNext;
    }
    
    // Fecha o anel (a lista duplamente encadeada)
    ptrCurr->ptrNext = ptrCList->ptrHead;
    ptrCList->ptrHead->ptrPrev = ptrCurr;
    
    return ptrCList;
}

int nextTheList(CircleList* CList)
{
    int iValue = CList->ptrHead->iID; // Salva o ID
    CList->ptrHead = CList->ptrHead->ptrNext; // Avança a lista

    return iValue;
}

int backTheList(CircleList* CList)
{
    int iValue = CList->ptrHead->iID; // Salva o ID
    CList->ptrHead = CList->ptrHead->ptrPrev; // Retrocede a lista

    return iValue;
}


// ======= Item 1-b =======
void deleteNode(CircleList* CList, int iValue)
{
    Node* ptrCurr = CList->ptrHead;
    
    while (ptrCurr->ptrNext != CList->ptrHead)
    {
        if (ptrCurr->iID == iValue)
        {
            Node* ptrAux = ptrCurr->ptrPrev;
            ptrAux->ptrNext = ptrCurr->ptrNext;
            ptrCurr->ptrNext->ptrPrev = ptrAux;
            
            free(ptrCurr);
        }
    }
}

void deleteList(CircleList* CList)
{
    Node* ptrCurr = CList->ptrHead;
    
    while (CList->ptrHead != nullptr)
    {
        deleteNode(CList, nextTheList(CList));
    }
}


// ======= Item 1-c =======
CircleList* appendLists(CircleList* CList_1, CircleList* CList_2)
{
    ptrCurr_1 = CList_1->ptrHead;
    ptrCurr_2 = CList_2->ptrHead;
    
    CircleList* ptrNewCList = (CircleList*) malloc(sizeof(CircleList));
    ptrNewCList->ptrHead = createNode(ptrCurr_1->iID);
    Node* ptrCurrList = ptrNewCList->ptrHead;
    
    while (ptrCurr_2->ptrNext != CList_2->ptrHead)
    {
        ptrCurrList->ptrNext = createNode(ptrCurr_2->iID);
        ptrCurrList = ptrCurrList->ptrNext;
        
        ptrCurr_2 = ptrCurr_2->ptrNext;
        
        if (ptrCurr_1->ptrNext != CList_1->ptrHead)
        {
            ptrCurrList->ptrNext = createNode(ptrCurr_1->iID);
            ptrCurrList = ptrCurrList->ptrNext;
            
            ptrCurr_1 = ptrCurr_1->ptrNext;
        }
    }
}


// ======= Item 2 =======


// ======= Item 3 =======