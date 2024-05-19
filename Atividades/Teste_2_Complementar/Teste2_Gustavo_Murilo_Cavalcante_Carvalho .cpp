#include<iostream>

using std::cout;
using std::endl;


// ---------------- Estruturas ----------------
typedef struct Node
{
    int iID;
    Node* ptrNext = nullptr;
    Node* ptrPrev = nullptr;
} Node;

typedef struct CircleList
{
    Node* ptrHead;
} CircleList;


// ---------------- Assinaturas das funções ---------------- 
// item 1-a 
Node* createNode(int);
CircleList* createCircleListByArray(int, int*);
int nextTheList(CircleList*);
int backTheList(CircleList*);
// item 1-b
void deleteNode(CircleList*, int);
void deleteList(CircleList*);
// item 1-c
CircleList* mergeLists(CircleList*, CircleList*);
// item 2
bool isThereCicle(Node*);
// item 3
CircleList* helpOuroboros(int, int);

// ---------------- Main ---------------- 
int main()
{
    // Questão 1
    cout << "====== Item 1 ======" << endl;

    // Cria uma lista duplamente encadeada circular
    int arriValues_1[3] = {1, 3, 5};
    int iSize_1 = sizeof(arriValues_1) / sizeof(int);
    CircleList* CircleList_1 = createCircleListByArray(iSize_1, arriValues_1);

    // Cria uma lista duplamente encadeada circular
    int arriValues_2[6] = {2, 7, 4, 7, 8, 9};
    int iSize_2 = sizeof(arriValues_2) / sizeof(int);
    CircleList* CircleList_2 = createCircleListByArray(iSize_2, arriValues_2);

    // Imprime as listas previamente criadas
    cout << "Lista Circular 1 : "; 
    for (int i = 1; i <= iSize_1; i++) 
    {
        cout << "-[" << nextTheList(CircleList_1) << "]";
    }  
    cout << "-" << endl;

    cout << "Lista Circular 2 : "; 
    for (int i = 1; i <= iSize_2; i++) 
    {
        cout << "-[" << nextTheList(CircleList_2) << "]";
    }  
    cout << "-" << endl;

    // Deleto um nó da lista 2
    deleteNode(CircleList_2, 7);
    cout << "Os nós com ID = 7 foram apagados da lista 2" << endl;

    // Cria uma lista mesclada
    CircleList* CircleListMerged = mergeLists(CircleList_1, CircleList_2);

    // Imprime a lista mesclada
    cout << "Lista Mesclada   : "; 
    for (int i = 1; i <= iSize_1 + iSize_2 - 2; i++) 
    {
        cout << "-[" << nextTheList(CircleListMerged) << "]";
    }  
    cout << "-" << endl;

    // Questão 2
    cout << endl << "====== Item 2 ======" << endl;
    
    // Cria uma lista duplamente encadeada
    Node* ptrHead_DLL = createNode(100);
    Node* ptrCurr_2 = ptrHead_DLL;
    for (int i = 1; i <= 5; i++)
    {
        Node* ptrTemp_2 = createNode(100 + i);

        ptrCurr_2->ptrNext = ptrTemp_2;
        ptrTemp_2->ptrPrev = ptrCurr_2;
    }

    cout << "A lista 1 possui um ciclo? [" << isThereCicle(CircleList_1->ptrHead) << "], (0 = false, 1 = true)" << endl;
    cout << "A lista 2 possui um ciclo? [" << isThereCicle(ptrHead_DLL) << "], (0 = false, 1 = true)" << endl;


    // Questão 3
    cout << endl << "====== Item 3 ======" << endl;
    
    int n = 3;
    int iValorFinal = 320;

    CircleList* CListOuroboros = helpOuroboros(iValorFinal, n);
    cout << "Ouroboros com valor final " << iValorFinal << " e n = " << n << endl;
    cout << "Lista inicial : ["; 
    for (int i = 1; i < n; i++)
    {
        cout << nextTheList(CListOuroboros) << ", ";
    }  
    cout << nextTheList(CListOuroboros) << "]" << endl;


    // Apaga as listas criadas
    deleteList(CircleList_1);
    deleteList(CircleList_2);
    deleteList(CircleListMerged);
    deleteList(CListOuroboros);

    return 0;
}


// ---------------- Definição das funções ---------------- 
// ======= Item 1-a =======
Node* createNode(int iValue)
{
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->iID = iValue;

    return newNode;
}

CircleList* createCircleListByArray(int iSize, int* arriValues)
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
    
    do
    {
        if (ptrCurr->iID == iValue)
        {
            if (ptrCurr == CList->ptrHead)
            {
                CList->ptrHead = ptrCurr->ptrNext;
            }

            Node* ptrAux = ptrCurr;

            // Relaciona os nós ignorando o nó atual
            ptrCurr->ptrPrev->ptrNext = ptrCurr->ptrNext;
            ptrCurr->ptrNext->ptrPrev = ptrCurr->ptrPrev;

            // Avança o nó atual
            ptrCurr = ptrCurr->ptrNext;

            free(ptrAux);
        }
        else 
        { 
            ptrCurr = ptrCurr->ptrNext; 
        }
    } while (ptrCurr != CList->ptrHead);
}

void deleteList(CircleList* CList)
{
    Node* ptrCurr = CList->ptrHead;
    
    while (ptrCurr != CList->ptrHead)
    {
        deleteNode(CList, nextTheList(CList));
    }
}


// ======= Item 1-c =======
CircleList* mergeLists(CircleList* CList_1, CircleList* CList_2)
{
    bool unread_1 = true;
    bool unread_2 = true;

    Node* ptrCurr_1 = CList_1->ptrHead;
    Node* ptrCurr_2 = CList_2->ptrHead;

    CircleList* ptrMerged = (CircleList*) malloc(sizeof(CircleList));
    
    // Adiciona o primeiro nó
    ptrMerged->ptrHead = createNode(ptrCurr_1->iID); 
    Node* ptrCurrList = ptrMerged->ptrHead;
    Node* ptrLast = ptrCurrList;

    ptrCurr_1 = ptrCurr_1->ptrNext;
    ptrCurrList = ptrCurrList->ptrNext;
    
    // Percorre as listas originais adicionando seus valores à nova lista
    while (unread_1 || unread_2) 
    {
        if (unread_2)
        {
            ptrCurrList = createNode(ptrCurr_2->iID);

            // Atualiza ligações
            ptrLast->ptrNext = ptrCurrList;
            ptrCurrList->ptrPrev = ptrLast;

            // Atualiza ponteiros
            ptrLast = ptrCurrList;
            ptrCurrList = ptrCurrList->ptrNext;
            ptrCurr_2 = ptrCurr_2->ptrNext;

            // Verifica se a lista foi lida por completo
            if (ptrCurr_2 == CList_2->ptrHead ) { unread_2 = false; }
        }

        if (unread_1)
        {
            ptrCurrList = createNode(ptrCurr_1->iID);
            
            // Atualiza ligações
            ptrLast->ptrNext = ptrCurrList;
            ptrCurrList->ptrPrev = ptrLast;

            // Atualiza ponteiros
            ptrLast = ptrCurrList;
            ptrCurrList = ptrCurrList->ptrNext;
            ptrCurr_1 = ptrCurr_1->ptrNext;

            // Verifica se a lista foi lida por completo
            if (ptrCurr_1 == CList_1->ptrHead ) { unread_1 = false; }
        }
    } 

    // Fecha o anel (a lista duplamente encadeada)
    ptrLast->ptrNext = ptrMerged->ptrHead;
    ptrMerged->ptrHead->ptrPrev = ptrLast;

    return ptrMerged;
}


// ======= Item 2 =======
bool isThereCicle(Node* ptrHead) {
    // Criamos dois ponteiros que percorrem a lista com "velocidades diferentes"
    Node* ptrStep = ptrHead;
    Node* ptrJump = ptrHead; // Ponteiro que avança pulando 1 nó

    // Verifica se há ciclo no sentido: começo --> fim
    while(ptrJump->ptrNext != nullptr && ptrJump->ptrNext->ptrNext != nullptr) {
        ptrStep = ptrStep->ptrNext;
        ptrJump = ptrJump->ptrNext->ptrNext;

        if(ptrJump == ptrStep) {
            return true; // Existe ciclo
        }
    }
    
    // Se não houver ciclo nesse sentido, leva os vetores até o fim da lista
    for(; ptrJump->ptrNext != nullptr; ptrJump = ptrJump->ptrNext); 
    ptrStep = ptrJump;
    
    // Verifica se há ciclo no sentido: começo <-- fim
    while(ptrJump->ptrPrev != nullptr && ptrJump->ptrPrev->ptrPrev != nullptr) {
        ptrStep = ptrStep->ptrPrev;
        ptrJump = ptrJump->ptrPrev->ptrPrev;
        
        if(ptrJump == ptrStep) {
            return true; // Existe ciclo
        }
    }

    return false; // Não existe ciclo
}  


// ======= Item 3 =======
CircleList* helpOuroboros(int iFinal, int iSize) 
{
    // Cria um array para representar a lista inicial
    int arriValues[iSize];
    
    arriValues[0] = iFinal;

    for (int i = 1; i < iSize; i++)
    {
        // Calcula os valores a e b
        int a = 0;
        int b, iResto;

        iResto = arriValues[0];

        // Enquanto o head atual for divisivel por 2 :
        while (iResto % 2 == 0)
        {
            iResto = iResto / 2;
            a++; 
        }

        // Atualiza o head atual
        a = a + 1;
        arriValues[0] = a;

        // Calcula o i-ésimo valor no Ouroboros
        b =  (iResto - 1) / 2;
        arriValues[i] = b;
    }

    return createCircleListByArray(iSize ,arriValues);
}