#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// Asinatura de funções
void imprimirLosango(int iVal);                 // Problema 1
void imprimirChar(int iVal, char cEntrada);     // Problema 1
bool testarPrimalidade(int iVal);               // Problema 2
int contarPrimos(int iVal);                     // Problema 2
void criarTabuleiro(char ptrTabuleiro[7][8]);   // Problema 3
void exibirTabuleiro(char ptrTabuleiro[7][8]);  // Problema 3
void jogada(char ptrTabuleiro[7][8], char cCor, int iPosicao);  // Problema 3

// Main
int main() {
    // Problema 1
    cout << "=====================" << endl;
    cout << "Problema 1:" << endl;
    
    int iVal1;
    cout << "Informe a altura da pirâmide: "; 
    cin >> iVal1;

    cout << "Para n = " << iVal1 << ", temos:" << endl;
    imprimirLosango(iVal1);

    // Problema 2
    cout << endl;
    cout << "=====================" << endl;
    cout << "Problema 2:" << endl;

    int iVal2;
    // Primos são inteiros maiores que 1 não tenham divisores além de 1 e ele mesmo.
    cout << "Escolha um número inteiro entre [2, 99.999] para testar a primalidade: "; 
    cin >> iVal2;
    
    cout << testarPrimalidade(iVal2) << endl;
    cout << endl;

    int iVal3;
    cout << "Escolha um número m entre [2, 99.999]: ";
    cin >> iVal3;

    cout << "Existem " << contarPrimos(iVal3) << " números primos entre 1 e " << iVal3 << endl;

    // Problema 3
    cout << endl;
    cout << "=====================" << endl;
    cout << "Problema 3:" << endl;

    char tabuleiro[7][8];

    criarTabuleiro(tabuleiro);
    exibirTabuleiro(tabuleiro);
    cout << endl;

    bool jogando = true;
    while (jogando) {
        char cCor;
        cout << "Escolha a cor (L ou X): ";
        cin >> cCor;

        int iPosicao;
        cout << "Escolha a Posicao (L ou X): ";
        cin >> iPosicao;

        jogada(tabuleiro, cCor, iPosicao)
    }
    

    return 0;
}

// Funções auxiliares
// Problema 1
void imprimirLosango(int iNum) {
    int repeticoes = iNum*2 - 1;

    for(int i = 1; i <= repeticoes; i++) {
        // A quantidade de espaços é proporcional à distância do centro
        int iQtdEspacos = abs(iNum - i);
        int iQtdChar = 2 * (iNum - iQtdEspacos);

        imprimirChar(iQtdEspacos, ' ');
        imprimirChar(iQtdChar, '#'); 

        cout << endl;
    }

    return;
}

void imprimirChar(int iVal, char cEntrada) {
    for (int i = 1; i <= iVal; i++) {
        cout << cEntrada;
    }
}

// Problema 2
bool testarPrimalidade(int iVal) {
    if (iVal <= 1 || iVal >= 100000) {
        cout << "Escolha inválida. O número deve ser maior que 1 e menor que 100.000" << endl;
        return false;
    } 

    // Se um número não possui divisor menor que sua raiz quadrado, então ele é primo.
    for (int iDiv = 2; iDiv * iDiv <= iVal; iDiv++) {
        if (iVal % iDiv == 0) { 
            return false; // No caso do número possuir divisor.
        }
    }

    return true;
}

int contarPrimos(int iVal) {
    if (iVal == 1) {
        // 1 Não é primo, então a quantidade de primos retornada é 0.
        return 0;
    } else {
        int iTeste = testarPrimalidade(iVal);

        return iTeste + contarPrimos(iVal - 1);
    }
}

// Problema 3

void criarTabuleiro(char ptrTabuleiro[7][8]) {
    for (int iCol = 1; iCol <= 7; iCol++) {
        for (int iLin = 0; iLin <= 6; iLin++) {
            ptrTabuleiro[iLin][iCol] = 'O';
        }
    }   
}

void exibirTabuleiro(char ptrTabuleiro[7][8]) {
    for (int iCol = 1; iCol <= 7; iCol++) {
        for (int iLin = 0; iLin <= 6; iLin++) {
            cout << ptrTabuleiro[iLin][iCol] << " ";
        }
        cout << endl;
    }  
}

void jogada(char tabuleiro[7][8], char cCor, int iPosicao) {
    if (cCor != 'L' && cCor != 'X') {
        cout << "Jogada inválida!" << endl;
        exibirTabuleiro(tabuleiro);
        cout << endl;
    }

    for (int iLin = 6; iLin >= 0; iLin--) {
        if (tabuleiro[iLin][iPosicao] == 'O') {
            X
        }
    }
}