#include <iostream>
//#include <math.h>

void funcClassificaIMC (float fIMC, char* strIMC)
{
    // < 17             Muito abaixo do peso
    // 17 <= x < 18.5   Abaixo do peso
    // 18.5 <= x < 25   Peso normal
    // 25 <= x < 30     Acima do peso
    // 30 <= x < 35     Obesidade
    // 35 <= x < 40     Obesidade severa
    // 40 <= x          Obesidade mórbida

    // Aplicação da ideia de arvore binária utilizando apenas condicionais simples.

    if (fIMC < 30) {
        if (fIMC < 25) {
            if (fIMC < 18.5) {
                if (fIMC < 17) {
                    strIMC = "Muito abaixo do peso"; return;
                }
                strIMC = "Abaixo do peso"; return;
            }
            strIMC = "Peso Normal"; return;
        }
        strIMC = "Acima do peso"; return;
    }
    else {
        if (fIMC >= 35) {
            if (fIMC >= 40) {
                strIMC = "Obesidade mórbida"; return;
            }
            // strIMC = "Obesidade severa"; return;
            strIMC[0] = 'F'; return;
        }
        strIMC = "Obesidade"; return;
    }
}

int main()
{
    float fMassa, fAltura;
    char classificacao[21];
    char* pointer;
    pointer = (char*)malloc(21 * sizeof(char));

    std::cout << "Qual o seu peso? (kg)" << std::endl;
    std::cin >> fMassa;

    std::cout << "Qual a sua altura? (m)" << std::endl;
    std::cin >> fAltura;

    float IMC = fMassa / (fAltura * fAltura);



    std::cout << std::endl;
    std::cout << "Massa: " << fMassa << std::endl;
    std::cout << "Altura: " << fAltura << std::endl;
    std::cout << "IMC: " << IMC << std::endl;
    funcClassificaIMC(IMC, pointer);
    //std::cout << "O seu IMC indica: -> " << classificacao << " <-"<< std::endl;

    return 0;
}