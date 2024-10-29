#include <stdio.h>

//Grupo: Gabriel Costa (14785489), Isabella Arão (9265732), Marina Fagundes (9265405)

#define REMOVIDO -2
#define VAZIO -3
#define NAO_ENCONTRADO -1

void inicializa_tabela(int tabela[], int m) {
    for (int i = 0; i < m; i++) {
        tabela[i] = VAZIO;
    }
}

int hash(unsigned int k, int x, int m) {
    return (k + x) % m;
}

int pesquisar(unsigned int k, int tabela[], int m) {
    for (int i = 0; i < m; i++) {
        int pos = hash(k, i, m);
        
        if (tabela[pos] == VAZIO) {
            return NAO_ENCONTRADO;
        } else if (tabela[pos] == k) {
            return pos; 
        }
    }
    return NAO_ENCONTRADO;
}

void inserir(unsigned int k, int tabela[], int m) {
    if (pesquisar(k, tabela, m) == NAO_ENCONTRADO) {
        for (int i = 0; i < m; i++) {
            int pos = hash(k, i, m);
        
            if (tabela[pos] == VAZIO || tabela[pos] == REMOVIDO) {
                tabela[pos] = k;
                return;
            }
        }
    }
    
    
}

void remover(unsigned int k, int tabela[], int m) {
    int pos = pesquisar(k, tabela, m);
    
    if (pos != NAO_ENCONTRADO) {
        tabela[pos] = REMOVIDO;
    }
}

int main() {
    int m;
    scanf("%d", &m);
    
    int tabela[m];
    inicializa_tabela(tabela, m);
    
    
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        unsigned int k;
        scanf("%u", &k);
        inserir(k, tabela, m);
    }
    
    int d;
    scanf("%d", &d);
    for (int i = 0; i < d; i++) {
        unsigned int k;
        scanf("%u", &k);
        remover(k, tabela, m);
    }
    
    int b;
    scanf("%d", &b);
    for (int i = 0; i < b; i++) {
        unsigned int k;
        scanf("%u", &k);
        printf("%d ", pesquisar(k, tabela, m));
    }

    return 0;
}
