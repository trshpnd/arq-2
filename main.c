#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "t1_utils.h"

/*** Definir aqui o tamanho da cache, em bytes. ****/
#define L1_size 256000
#define L2_size 1000000
#define L3_size 8000000
/***************************************************/

// Range máximo dos numeros aleatórios gerados.
// Preferível que exceda o tamanho do array, menos números repetidos.
#define MAX_RANGE 10000000

const int cache_size = L1_size + L2_size + L3_size + 1000000; // + 1MB para exceder cache.
const int length = cache_size/sizeof(int);
const int length_list = cache_size/sizeof(Node);
const int length_mat = length/2;

int* arr;
Node* inicio_lista;

int main(){
    int input = 0;              // Input usuário (menu)
    int n = sqrt(length_mat);   // Dimensão das matrizes quadradas
    srand(time(NULL));

    do{
        printf("1. Ordenação de array por quicksort.\n");
        printf("2. Busca em profundidade em linked list.\n");
        printf("3. Multiplicação de matrizes.\n");
        printf("4. Sair.\n");

        if(scanf("%d", &input) != 1){
            printf("Entrada inválida. Tente novamente.\n");
            limpaBuffer();
            continue;  
        };

        limpaBuffer();

        switch(input){

            case 1: 
                /* ----- Algoritmo de ordenação com array (vetor) ----- */
                printf("\nAlocando memória para o array... ");
                arr = (int*) malloc(length * sizeof(int));
                printf("Finalizado. \n");

                // Preenchendo o array com valores aleatórios, de 0 a MAX_RANGE
                for(int i = 0; i < length; i++){
                    arr[i] = random_int(0, MAX_RANGE);
                }
                printf("Array preenchido.\n\n");
                printFirstLastNpos(10, length, arr);

                printf("Realizando algoritmo de quicksort... ");
                quicksort(arr, 0, length);

                printf("Array ordenado.\n\n");
                printFirstLastNpos(10, length, arr);

                // Libera a memória
                free(arr);
                break;

            case 2: 
                /* ----- Busca em profundidade em linked list ----- */
                // Criação do primeiro nó da lista. Endereço de referência para
                // encontrar os demais elementos relacionados.
                inicio_lista = criarNode(random_int(0, MAX_RANGE));
                Node* anterior = inicio_lista;
                int ultimo;

                // Criação da lista, geração de valores aleatórios em cada um dos nós
                for(int i = 0; i < length_list; i++){
                    Node* novoNodo = criarNode(random_int(0, MAX_RANGE));
                    ultimo = novoNodo->valor;

                    anterior->proximo = novoNodo;
                    novoNodo->anterior = anterior;
                    anterior = novoNodo;
                }

                printf("\nLista duplamente encadeada criada. Valor contido no último nó: %d \n", ultimo);
                printf("Realizando busca em profundidade pelo valor do último nó... ");

                Node* atual = inicio_lista;
                while(atual->proximo != NULL){
                    atual = atual->proximo;
                    ultimo = atual->valor;
                }

                printf("Finalizado.\nÚltimo elemento da lista: %d\n", ultimo);
                printf("Excluindo lista... ");

                // Libera a memória
                excluirLista(&inicio_lista);
                printf("Lista excluída com sucesso.\n\n");
                break;

            case 3: 
                /* ----- Multiplicação de matrizes ----- */
                // Alocação de memória para as matrizes
                printf("\nAlocando memória para uma matriz nxn:\n%d bytes/matriz\n%d elementos/matriz\n", cache_size/2, length_mat);
                int **matA = allocateMatrix(n);
                int **matB = allocateMatrix(n);
                int **matC = allocateMatrix(n);

                // Preenchendo as matrizes com valores aleatórios (0-9 para evitar overflow na multiplicação)
                printf("Finalizado.\n\nPreenchendo as matrizes com valores aleatórios... ");
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < n; j++){
                        matA[i][j] = random_int(0, 9);
                        matB[i][j] = random_int(0, 9);
                    }
                }
                printf("Finalizado.\n\nRealizar multiplicação por matriz transposta?\n0 - Não\n1 - Sim\n");
                if(scanf("%d", &input) != 1){
                    printf("Entrada inválida. Tente novamente.\n");
                    limpaBuffer();
                    continue;
                }

                limpaBuffer();
                printf("Realizando multiplicação... ");

                switch(input){
                    case 0:
                        // Multiplicação padrão
                        multiplyMatrices(n, matA, matB, matC, false);
                        break;
                    case 1:
                        // Multiplicação por matriz transposta
                        multiplyMatrices(n, matA, matB, matC, true);
                        break;
                    default:
                        printf("Entrada inválida.\n\n");
                        break;
                }
                printf("Finalizado.\n\n");

                // Print das matrizes (apenas debug)
                /*
                printf("A =\n");
                printMatrix(n, matA);
                printf("\n\n");

                printf("B =\n");
                printMatrix(n, matB);
                printf("\n\n");

                printf("Res =\n");
                printMatrix(n, matC);
                printf("\n\n");
                */

                // Liberar memória alocada
                printf("Liberando memória alocada... ");
                freeMatrix(matA, n);
                freeMatrix(matB, n);
                freeMatrix(matC, n);
                printf("Finalizado.\n\n");
                break;

            case 4:
                printf("Saindo.\n ");
                break;

            default:
                printf("Entrada inválida.\n\n");
                break;
        }

    }while(input != 4);

    return 0;
}