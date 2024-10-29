#include <stdio.h>
#include <stdlib.h>

void bolha (int vet[], int n){

    int c, i, j;

    for (i = n-1; i >= 1; i--){
        c = -1;
        for (j = 0; j < i; j++){
            printf("C %d %d\n", j, j+1);
            if (vet[j] > vet[j+1]){
                c = j;
                int temporario = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = temporario;
                printf("T %d %d\n", j, j+1);
            }
        }
    }
}

void selecao (int vet[], int n){
    int i, j, m, temporario;
    for (i = 0; i < n-1; i++){
        m = i;
        for (j = i + 1; j < n; j++){
            printf("C %d %d\n", m, j);
            if (vet[j] < vet[m]){
                m = j;
            }
        }
        temporario = vet[i];
        vet[i] = vet[m];
        vet[m] = temporario;

        if (m != i){
            printf("T %d %d\n", i, m);
        }
        
    }
}

int main(){

    char metodo_ordenacao[8];
    scanf("%s", &metodo_ordenacao);

    int n;
    scanf("%d", &n);

    int x;
    int *lista = (int *)malloc(n*sizeof(int));

    for (x = 0; x < n; x++){
        scanf("%d", &lista[x]);
    }

    if (strcmp(metodo_ordenacao, "bolha") == 0){

        bolha(lista, n);
    }
    else if (strcmp(metodo_ordenacao, "selecao") == 0){

        selecao(lista, n);
    }


    for (x = 0; x < n; x++){
        printf("%d ", lista[x]);
    }

    free(lista);
}
