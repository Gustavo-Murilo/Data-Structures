#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// Definição das estruturas usadas
typedef struct Node{
    int iMatricula; 
    Node* ptrProximo;
} Node;

typedef struct Lista_Encadeada{
    Node* ptrElemento; 
} Lista_Encadeada;

// Assinaturas das funções
Lista_Encadeada* criarLista();      // Questão 1
void inserirElemento(Lista_Encadeada* stLista, int iMatricula); // Questão 1
void removerAluno(Lista_Encadeada* stLista, int iMatricula);    // Questão 2
void inverterExtremos(Lista_Encadeada* stLista);    // Questão 3
Lista_Encadeada* encontrarIntersec(Lista_Encadeada* stLista1, Lista_Encadeada* stLista2); // Questão 4
bool verificarCiclo(Lista_Encadeada* stLista);   // Questão 5
int verificarTamanhoCiclo(Lista_Encadeada* stLista);   // Questão Extra
void exibirLista(Lista_Encadeada* stLista);         // Opcional
void inserirElementosArray(Lista_Encadeada* stLista, int* arriMatriculas, int szTamanho); // Opcional

// Função principal (main)//* condition */* condition */
int main() {
    // Teste do caminho ideal
    Lista_Encadeada* stMatriculas1 = criarLista();
    for (int i = 1; i <= 10; i++) {
        inserirElemento(stMatriculas1, 24000+i); 
    }
    
    Lista_Encadeada* stMatriculas2 = criarLista();
    for (int i = 5; i <= 15; i+=2) {
        inserirElemento(stMatriculas2, 24000+i); 
    }


    // // Teste desfavoráveis
    // Lista_Encadeada* vazia;
    // inserirElemento(vazia, 2);

    exibirLista(stMatriculas1);
    inverterExtremos(stMatriculas1);
    exibirLista(stMatriculas1);
    exibirLista(stMatriculas2);
    cout << endl;

    cout << "Intersecção entre a lista 1 e 2 é:" << endl;
    Lista_Encadeada* stInter = encontrarIntersec(stMatriculas1, stMatriculas2);
    exibirLista(stInter);
    cout << endl;

    inverterExtremos(stMatriculas2);
    exibirLista(stMatriculas2);
    removerAluno(stMatriculas2, 24005);
    exibirLista(stMatriculas2);
    inverterExtremos(stMatriculas2);
    exibirLista(stMatriculas2);
    cout << endl;

    verificarCiclo(stMatriculas2);
    exibirLista(stMatriculas2);
    cout << endl;

    // crio ciclo
    stMatriculas2->ptrElemento->ptrProximo->ptrProximo = stMatriculas2->ptrElemento;
    verificarTamanhoCiclo(stMatriculas2);
    cout << endl;

    // crio ciclo
    stMatriculas2->ptrElemento->ptrProximo = stMatriculas2->ptrElemento;
    verificarTamanhoCiclo(stMatriculas2);
    cout << endl;

    // crio ciclo
    stMatriculas1->ptrElemento->ptrProximo->ptrProximo->ptrProximo->ptrProximo = stMatriculas1->ptrElemento;
    verificarTamanhoCiclo(stMatriculas1);
    cout << endl;

    // Crio lista a partir de array
    Lista_Encadeada* stLista3 = criarLista();
    int arrCarga[4] = {1, 2, 8, 9};
    inserirElementosArray(stLista3, arrCarga, 4);
    exibirLista(stLista3);

    return 0;
}

// Funções para a manipulção da lista encadeada

// Questão 1
Lista_Encadeada* criarLista() {
    Lista_Encadeada* lista = (Lista_Encadeada*) malloc(sizeof(Lista_Encadeada));
    lista->ptrElemento  = nullptr;

    return lista;
}

void inserirElemento(Lista_Encadeada* stLista, int iMatricula){
    // Criação de um novo nó
    Node* ptrNovo = (Node*) malloc(sizeof(Node));
    ptrNovo->iMatricula = iMatricula;
    ptrNovo->ptrProximo = nullptr;

    // Criação de nó para percorrer até o final da lista
    Node* ptrAtual = stLista->ptrElemento;

    // Se a lista estiver vazia  
    if(stLista->ptrElemento == nullptr) {
        stLista->ptrElemento = ptrNovo;
    } else {   
        while (ptrAtual->ptrProximo != nullptr) {
            ptrAtual = ptrAtual->ptrProximo;
        }

        ptrAtual->ptrProximo = ptrNovo;
    }
    
}

// Questão 2
void removerAluno(Lista_Encadeada* stLista, int iValor) {
    // Parto da premissa que cada matrícula aparece 1 vez na lista
    Node* ptrAtual = stLista->ptrElemento;
    Node* ptrAnterior = stLista->ptrElemento;

    if (ptrAtual == nullptr){
        // Caso onde a lista é vazia
        cout << "Lista vazia" << endl;
        return;
    } else if (ptrAtual->iMatricula == iValor) {
        // Caso onde o elemento é o primeiro da lista
        stLista->ptrElemento = ptrAtual->ptrProximo;
        cout << "A matrícula " << ptrAtual->iMatricula << " foi removida." << endl;
        free(ptrAtual);
    } else {
        // Demais casos
        while (ptrAtual->ptrProximo != nullptr && ptrAtual->iMatricula != iValor) {
            ptrAnterior = ptrAtual;
            ptrAtual = ptrAtual->ptrProximo;
        }
        
        // Se a matrícula foi encontradda
        if(ptrAtual->iMatricula == iValor) 
        {
            ptrAnterior->ptrProximo = ptrAtual->ptrProximo;
            cout << "A matrícula " << ptrAtual->iMatricula << " foi removida." << endl;
            free(ptrAtual);
        } else 
        {
            cout << "A matrícula " << iValor << " não está na lista." << endl;
        }
    }
}

// Questão 3
void inverterExtremos(Lista_Encadeada* stLista) {
    Node* ptrPrimeiro = stLista->ptrElemento;
    Node* ptrUltimo = stLista->ptrElemento;
    Node* ptrPenultimo = nullptr;

    // Não há nada a fazer com uma lista vazia ou unitária
    if(ptrPrimeiro == nullptr || ptrPrimeiro->ptrProximo == nullptr){
        return;
    }

    // Para evitar ciclos isolamos o caso de uma lista com 2 nós
    if(ptrPrimeiro->ptrProximo->ptrProximo == nullptr) {
        stLista->ptrElemento = ptrPrimeiro->ptrProximo;

        stLista->ptrElemento->ptrProximo = ptrPrimeiro;
        
        ptrPrimeiro->ptrProximo = nullptr;
        return;
    }

    // Percorre até o penúltimo elemento da lista
    while(ptrUltimo->ptrProximo != nullptr) {
        ptrPenultimo = ptrUltimo;
        ptrUltimo = ptrUltimo->ptrProximo;
    }

    // O ultimo passa a apontar para o mesmo que o primeiro
    ptrUltimo->ptrProximo = ptrPrimeiro->ptrProximo;

    // Passamos o último nó para o começo
    stLista->ptrElemento = ptrUltimo;

    // Para evitar um ciclo, o primeiro nó passa a não apontar para ninguem
    ptrPrimeiro->ptrProximo = nullptr;

    ptrPenultimo->ptrProximo = ptrPrimeiro;
}

// Questão 4
Lista_Encadeada* encontrarIntersec(Lista_Encadeada* stLista1, Lista_Encadeada* stLista2) {
    Lista_Encadeada* stIntersec = (Lista_Encadeada*) malloc(sizeof(Lista_Encadeada));

    Node* ptrLista1 = stLista1->ptrElemento;

    while (ptrLista1 != nullptr) {

        Node* ptrLista2 = stLista2->ptrElemento;
        
        while (ptrLista2 != nullptr) {
            if(ptrLista1->iMatricula == ptrLista2->iMatricula) {
                inserirElemento(stIntersec, ptrLista1->iMatricula);
            }
            ptrLista2 = ptrLista2->ptrProximo;
        }        
        ptrLista1 = ptrLista1->ptrProximo;
    }
    
    if (stIntersec->ptrElemento == nullptr) {
        free(stIntersec);
        return nullptr;
    }
    
    return stIntersec;
}


// Questão 5
bool verificarCiclo(Lista_Encadeada* stLista) {
    // Criamos dois ponteiros que percorrem a lista com "velocidades diferentes"
    Node* ptrPasso = stLista->ptrElemento;
    Node* ptrSalto = stLista->ptrElemento;

    while(ptrSalto->ptrProximo != nullptr && ptrSalto->ptrProximo->ptrProximo != nullptr) {
        ptrPasso = ptrPasso->ptrProximo;
        ptrSalto = ptrSalto->ptrProximo->ptrProximo;

        if(ptrSalto == ptrPasso) {
            cout << "Existe ciclo" << endl;
            return true;
        }
    }

    cout << "Não existe ciclo" << endl;
    return false;
}  

// Questão
int verificarTamanhoCiclo(Lista_Encadeada* stLista) {
    // Criamos dois ponteiros que percorrem a lista com "velocidades diferentes"
    Node* ptrPasso = stLista->ptrElemento;
    Node* ptrSalto = stLista->ptrElemento;
    int contador = 1;

    while(ptrSalto->ptrProximo != nullptr && ptrSalto->ptrProximo->ptrProximo != nullptr) {
        ptrPasso = ptrPasso->ptrProximo;
        ptrSalto = ptrSalto->ptrProximo->ptrProximo;
        
        if(ptrSalto == ptrPasso) {
            cout << "Existe ciclo de tamanho " << contador << endl;
            return contador;
        }
        contador++;
    }

    cout << "Não existe ciclo" << endl;
    return contador;

}  


// Opcional
void exibirLista(Lista_Encadeada* stLista) {
    if(stLista->ptrElemento == nullptr) 
    {
        cout << "Lista vazia" << endl;
    } 
    else if(stLista->ptrElemento != nullptr) 
    {
        Node* ptrAtual = stLista->ptrElemento;

        cout << "Lista: " << ptrAtual->iMatricula;

        while (ptrAtual->ptrProximo != nullptr) 
        {
            ptrAtual = ptrAtual->ptrProximo;

            cout << ", " << ptrAtual->iMatricula;
        }

        cout << "." << endl;
    }
}

void inserirElementosArray(Lista_Encadeada* stLista, int* arriMatriculas, int szTamanho) {
    if (arriMatriculas == nullptr) { return; } // Entrada inválida

    for(int i = 0; i < szTamanho; i++) {
        inserirElemento(stLista, arriMatriculas[i]);
    }
}