#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Struct de nó da lista encadeada.
typedef struct Node{
    int valor;
    struct Node *anterior;
    struct Node *proximo;
}Node;

// Função para criar nó da lista. 
// Ponteiros de proximo elemento e elemento anterior iniciam em NULL por padrão.
Node* criarNode(int valor){
    Node* novo = (Node *)malloc(sizeof(Node));
    novo -> valor = valor;
    novo -> proximo = NULL;
    novo -> anterior = NULL;
    return novo;
}

// Exclui a lista por completo, libera a memória.
void excluirLista(Node** inicio){
    Node* atual = *inicio;
    Node* prox;

    while(atual != NULL){
        prox = atual->proximo;
        free(atual);
        atual = prox;
    }

    *inicio = NULL;
}

// Retorna um int aleatório entre o range definido por min e max.
unsigned long random_int(unsigned long min, unsigned long max){
    unsigned long range = max - min + 1UL;
    unsigned long randA = rand();
    unsigned long randB = rand();
    unsigned long randVal = ((randA << 15) | randB) % range;
    return min + randVal; 
}

// Troca os valores contidos nos endereços de a e b.
void troca(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

// Pivô mediana de 3
void median_pivot(int* array, int inicio, int fim) {
    // Encontrar o índice médio
    int indiceMedio = (inicio + fim) / 2;

    // Encontrar o valor mediano
    if (array[inicio] <= array[indiceMedio] && array[inicio] >= array[fim]) {
        
    } else if (array[indiceMedio] <= array[inicio] && array[indiceMedio] >= array[fim]) {
        troca(&array[inicio], &array[indiceMedio]);
    } else {
        troca(&array[inicio], &array[fim]);
    }
}

// Particionamento de Lomuto
int partition_lomuto(int C[], int left, int right){
    int chave = C[left];
    int storeindex = left + 1;  // Índice do menor elemento

    for (int i = left+1; i <= right; i++){
        // Se elemento atual é menor ou igual ao pivô
        if (C[i] < chave){
            troca(&C[i], &C[storeindex]);
            storeindex++;    // Incrementa índice do menor elemento
        }
    }
    troca(&C[left], &C[storeindex-1]);
    return (storeindex-1);
}

// Quicksort, pivô mediana de 3, particionamento de Lomuto
void quicksort(int c[], int i, int f){
    int p; // Índice do pivô
    if(f > i){
        median_pivot(c, i, f);
        p = partition_lomuto(c, i, f);

        quicksort(c, i, p-1);
        quicksort(c, p+1, f);
    }
}

// Printa as primeiras e últimas N 
void printFirstLastNpos(int N, int length, int arr[]){
    printf("(0 - %d):\n", N);
    for(int i = 0; i < N; i++){
        printf("%d ", arr[i]);
    }
    printf("...\n\n");

    printf("(%d - %d):\n... ", length-N, length);
    for(int i = N; i > 0; i--){
        printf("%d ", arr[length - i]);
    }
    printf("\n\n");
}

void limpaBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
