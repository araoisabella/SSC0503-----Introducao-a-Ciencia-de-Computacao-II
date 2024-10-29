#include <stdio.h>
#include <stdlib.h>

void insercao (int vet[], int n, int *trocas, int *comp){
    *comp = 0;
    *trocas = 0;
    for (int i = 1; i < n; i++){
        int x = vet[i];
        int j = i - 1;
        (*trocas)++;

        while (j >= 0 && vet[j] > x){
            vet[j + 1] = vet[j];
            j--;
            (*comp)++;
            (*trocas)++;
        }
        if (j >= 0 && vet[j] <= x){
            (*comp)++;
        }
        vet[j + 1] = x;
        (*trocas)++;
    }
}

void merge (int vet[], int c, int f, int b[], int *trocas, int *comp){

    if (c>=f){
        return;

    } else {

        int m = (c+f)/2;
        merge(vet, c, m, b, trocas, comp);
        merge(vet, m+1, f, b, trocas, comp);
        int i1 = c;
        int i2 = m+1;
        int j = c;

        while(i1 <= m && i2 <= f){

            (*comp)++;

            if(vet[i1] <= vet[i2]){
                b[j] = vet[i1];
                i1++;
                (*trocas)++;

            } else {
                b[j] = vet[i2];
                i2++;
                (*trocas)++;
            }
            j++;

        }

        while(i1 <= m){
            b[j] = vet[i1];
            i1++;
            j++;
            (*trocas)++;

        }
        while(i2 <= f){
            b[j] = vet[i2];
            i2++;
            j++;
            (*trocas)++;
        }

        for(int i = c; i <= f; i++){
            vet[i] = b[i];
            (*trocas)++;

        }
    }
}

void mergesort (int vet[], int n, int *trocas, int *comp){
    int *b = (int *)malloc(sizeof(int) * n);
    merge (vet, 0, n-1, b, trocas, comp);
    free(b);
}


int main(){

    int Q;
    scanf("%d", &Q);

    int **matriz = (int **)malloc(Q * sizeof(int *));
    int **matriz_merge = (int **)malloc(Q * sizeof(int *));

    int i, j;
    int *tam = (int *)malloc(Q * sizeof(int));

    for (i = 0; i < Q; i++){
        int n;
        scanf("%d", &n);
        matriz[i] = (int *)malloc(n * sizeof(int));
        matriz_merge[i] = (int *)malloc(n * sizeof(int));
        tam[i] = n;
    }

    for(i = 0; i < Q; i++){
        for (j = 0; j < tam[i]; j++){
            scanf("%d", &matriz[i][j]);
            matriz_merge[i][j] = matriz[i][j];
        }
    }

    for (i = 0; i < Q; i++){
        int trocas_insercao = 0;
        int comp_insercao = 0;
        int trocas_merge = 0;
        int comp_merge = 0;

        insercao (matriz[i], tam[i], &trocas_insercao, &comp_insercao);
        mergesort(matriz_merge[i], tam[i], &trocas_merge, &comp_merge);

        printf("I %d %d %d\n", tam[i], trocas_insercao, comp_insercao);
        printf("M %d %d %d\n", tam[i], trocas_merge, comp_merge);
    }


    for (i = 0; i < Q; i++) {
        free(matriz[i]);
        free(matriz_merge[i]);
    }

    free(matriz);
    free(matriz_merge);

    return 0;
}
