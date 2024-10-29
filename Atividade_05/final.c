#include <stdio.h>
#include <stdlib.h>

int op_quick(int flag){
  static int op = 0;

  if (!flag){

    op++;
    return 0;
  } else{
    int temp = op;
    op = 0;
    return temp;
  }
}

int op_shell(int flag){
  static int op = 0;

  if (!flag){
    op++;
    return 0;
  } else{
    int temp = op;
    op = 0;
    return temp;
  }
}

void shell(int *v, int n){

    int gap = 1;

    while (gap <= n){
        gap *= 2;
    }
    gap = (gap / 2) - 1;

    while (gap > 0){
        for (int i = gap; i < n; i++){
            int x = v[i];
            int j = i - gap;
            op_shell(0);
            while (j >= 0 && v[j] > x){
                v[j + gap] = v[j];
                op_shell(0);
                j -= gap;
                op_shell(0);
            }
            if (j >= 0){
                op_shell(0);
            }

            v[j + gap] = x;
            op_shell(0);
        }
        gap /= 2;
    }
}


void quick(int *v, int f, int l){
    if (f >= l){
        return;
    }

    int m = (l + f) / 2;
    int pivot = v[m];
    int i = f;
    int j = l;
    while (1){

        while (v[i] < pivot){
            op_quick(0);
            i++;
        }
        op_quick(0);

        while (v[j] > pivot){
            op_quick(0);
            j--;
        }
        op_quick(0);

        if (i >= j){
            break;
        }

        int aux = v[i];
        op_quick(0);
        v[i] = v[j];
        op_quick(0);
        v[j] = aux;
        op_quick(0);
        i++;
        j--;
    }

    op_quick(0);

    quick(v, f, j);
    quick(v, j + 1, l);
}

int main(){
    int N;
    scanf("%d", &N);

    int *V_shell = (int *)malloc(N * sizeof(int));
    int *V_quick = (int *)malloc(N * sizeof(int));
    int *V_aux = (int *)malloc(N * sizeof(int));
    int c_shell, c_quick;


    for (int i = 0; i < N; i++){
        scanf("%d", &V_aux[i]);
    }


    for (int i = 1; i <=N; i++){
        for (int j = 0; j<N; j++){
            V_shell[j] = V_aux[j];
            V_quick[j] = V_aux[j];
        }

        shell(V_shell, i);
        quick(V_quick, 0, i-1);
        c_shell = op_shell(1);
        c_quick = op_quick(1);

        if (c_shell == c_quick){
            printf("-");
        }
        if (c_shell > c_quick){
            printf("Q");
        }
        if (c_shell < c_quick){
            printf("S");
        }
    }
    free(V_aux);
    free(V_quick);
    free(V_shell);
    return 0;
}
