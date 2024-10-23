#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
int* matA; 
int** matB;
Node* inicio_lista;

int main(){
    int input = 0;
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
                printf("Finalizado. \n")

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
                printf("\nAlocando memória para uma matriz linha e uma matriz coluna:\n%d bytes/matriz\n%d elementos/matriz\n", cache_size/2, length_mat);
                matA = (int*) malloc(length_mat * sizeof(int));

                matB = (int**) malloc(length_mat * sizeof(int*));
                for(int i =0; i < length_mat; i++){
                    matB[i] = (int*) malloc(sizeof(int));
                }

                printf("Finalizado.\n\nPreenchendo as matrizes com valores aleatórios... ");
                // Preenchendo as matrizes com valores aleatórios (0-9 para evitar overflow na multiplicação)
                for(int i = 0; i < length_mat; i++){
                    matA[i]     = random_int(0, 9);
                    matB[i][0]  = random_int(0, 9);
                }
                printf("Finalizado.\n\n");

                /*// Print das matrizes linha e coluna 
                printf("A =\n[ ");
                for(int i = 0; i < length_mat; i++){
                    printf("%02d ", matA[i]);
                }
                printf("]\n\n");

                printf("B =\n");
                for(int i = 0; i < length_mat; i++){
                    printf("[ %02d ]\n", matB[i][0]);
                }*/

                int C = 0;
                for(int i = 0; i < length_mat; i++){
                    C += matA[i] * matB[i][0];
                }
                printf("A * B = [ %d ]\n\n", C);

                // Liberar memória alocada
                printf("Liberando memória alocada... ");
                for (int i = 0; i < length_mat; i++) {
                    free(matB[i]);
                }
                free(matB);
                free(matA);
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