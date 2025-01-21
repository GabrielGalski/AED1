#include <stdio.h>
#include <stdbool.h>

/*
====================
Can Place Flowers
Função para verificar se é possivel colocar as flores em um canteiro sem que as flores se repitam
====================
*/
bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n) {
    int count = 0;

    // primeiro loop para ler todas as posições do vetor
    for (int i = 0; i < flowerbedSize; i++) {
             // o if que verifica se as posições são validas para a flor ser plantada
            if (flowerbed[i] == 0 && 
                (i == 0 || flowerbed[i -1] == 0) && 
                (i == flowerbedSize - 1 || flowerbed[i + 1] == 0)) {

                flowerbed[i] = 1;  // planta a flor na posição i
                count++;           // contador + 1

                if (count >= n) {
                    return true;   // retorna true se o numero de flores plantas for maior ou igual o n
                }
            }
    } return count >= n;  //retorna true se conseguimos plantar n flores e finaliza   
}

    
/*
====================
main
função principal do programa
===================
*/
int main() {
    int flowerbed[] = { 1, 1, 0, 0, 0 };    
    int flowerbedSize = 5;
    int n = 1;                              
    
    if (canPlaceFlowers(flowerbed, flowerbedSize, n)) {
        printf("Flores plantadas\n");
    } else {
        printf("Sem espaço para plantar as flores\n");
    }
    
    return 0;
}

