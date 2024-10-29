#include <stdio.h>
#include <stdlib.h>

//Grupo: Gabriel Costa (14785489), Isabella Arão (9265732), Marina Fagundes (9265405)

void merge(int a[], int c, int f, int b[])
{
    int i1;
    if (c >= f) //comeco = fim
    {
        return;
    }
    else
    {
        int m = (c + f)/2;
        merge(a, c, m, b);
        merge(a, m + 1, f, b);
        i1 = c;
        int i2 = m + 1;
        int j = c;
        while (i1 <= m && i2 <= f)
        {
            if (a[i1] <= a[i2])
            {
                b[j] = a[i1];
                i1++;
            }
            else
            {
                b[j] = a[i2];
                i2++;
            }
            j++;
        }
        while (i1 <= m)
        {
            b[j] = a[i1];
            i1++;
            j++;
        }
        while (i2 <= f)
        {
            b[j] = a[i2];
            i2++;
            j++;
        }
    }
    for (i1 = c; i1 <= f; i1++)
    {
        a[i1] = b[i1];
    }
}

void mergesort(int a[], int n)
{
    int *b = (int*) malloc(sizeof(int)*n);
    if (b == NULL)
    {
        printf("Erro na alocacao da memoria!\n");
        return;
    }
    merge(a, 0, n - 1, b);
    free(b);
}

int buscaBinaria (int a[], int n, int x){
    int c = 0;
    int f = n - 1;
    while (c <= f){
        int m = (c + f)/2;
        if(a[m] == x){
            return 1;
        } else if (a[m] > x) {
            f = m - 1;
        } else {
            c = m + 1;
        }
    }
    return 0;
}


int main() {
    int n;
    int n_buscas;
    int elemento_buscado;

    scanf("%d", &n);
    int *vetor = (int*) malloc(sizeof(int)*n);

    if (vetor == NULL)
    {
        printf("Erro na alocacao da memoria!\n");
        return 1;
    }
    int pos;


    for (pos = 0; pos < n; pos++)
    {
        scanf("%d", &vetor[pos]);
    }

    mergesort(vetor, n);
    scanf("%d", &n_buscas);

    for (int i = 0; i < n_buscas; i++){
        scanf("%d", &elemento_buscado);
        if (buscaBinaria (vetor, n, elemento_buscado)){
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    free(vetor);
    return 0;
}
