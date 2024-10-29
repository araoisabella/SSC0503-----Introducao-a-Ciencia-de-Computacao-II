//Grupo: Gabriel Costa (14785489), Isabella Arão (9265732), Marina Fagundes (9265405)

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int bool;

typedef struct TipoGrafo { //grafo com matriz de adjacência
    int vertices;
    int arestas;
    int **matriz_adj;
} TipoGrafo;

TipoGrafo criarGrafo(int v) { //inicializar o grafo
    TipoGrafo g;
    g.vertices = v;
    g.arestas = 0;

    //alocar matriz de adjacência e inicializar com -1
    g.matriz_adj = (int **)malloc(v * sizeof(int *));
    for (int i = 0; i < v; i++) {
        g.matriz_adj[i] = (int *)malloc(v * sizeof(int));
        for (int j = 0; j < v; j++) {
            g.matriz_adj[i][j] = -1; //inicializa com -1
        }
    }

    return g;
}

void criarAresta(TipoGrafo *gr, int vi, int vf, int p) { //criar arestas do grafo
    if (!gr) {
        return;
    }
    if (vf < 0 || vf >= gr->vertices || vi < 0 || vi >= gr->vertices) {
        return;
    }

    gr->matriz_adj[vi][vf] = p; //adicionar aresta na matriz de adjacências
    gr->arestas++;
}

void imprimir(TipoGrafo *gr) { //imprimir o grafo
    if (!gr) {
        return;
    }
    printf("Vertices: %d, Arestas: %d\n", gr->vertices, gr->arestas);

    for (int i = 0; i < gr->vertices; i++) {
        for (int j = 0; j < gr->vertices; j++) {
            printf("%3d ", gr->matriz_adj[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void limparGrafo(TipoGrafo *gr) { //liberar memória do grafo
    if (!gr) {
        return;
    }

    //liberar matriz de adjacência
    for (int i = 0; i < gr->vertices; i++) {
        free(gr->matriz_adj[i]);
    }
    free(gr->matriz_adj);
}


int max(int x, int y) { //retorna o máximo entre dois valores
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

int elementoExiste(int linhas, int colunas, int i, int j) {
    //verifica se o elemento da cache de linhas x colunas, nos índices i e j existe
    if (i >= 0 && i < linhas && j >= 0 && j < colunas) {
        return 1;  //o elemento existe
    } else {
        return 0;  //o elemento não existe
    }
}

int coordenadaParaIndice(int colunas, int i, int j) {
    //converte as coordenadas para um índice, que será usado na função percurso_pd_aux
    return i * colunas + j;
}

int percurso_pd_aux(int **cache, TipoGrafo *percurso, int linhas, int colunas) {
    cache[0][0] = 0;
    for (int i = 0; i < linhas; i++) { //método iterativo
        for (int j = 0; j < colunas; j++) {
            //preencher a cache
            //lembrar que a pessoa só pode ir para baixo ou para a direita
            int esquina_atual = coordenadaParaIndice(colunas, i, j); //índice da esquina atual
            int esquina_de_cima = coordenadaParaIndice(colunas, i - 1, j); //índice da esquina de cima
            int esquina_da_esquerda = coordenadaParaIndice(colunas, i, j - 1); //índice da esquina da esquerda
            int amigos_de_cima = 0, amigos_da_esquerda = 0;;
            
            //verificar se o elemento é um endereço válido na cache
            if(elementoExiste(linhas, colunas, i - 1, j) == 1) {
                amigos_de_cima = cache[i - 1][j] + percurso->matriz_adj[esquina_de_cima][esquina_atual]; //atualiza o número de amigos que você cumprimentou passando pelo caminho de cima
            }
            
            //verificar se o elemento é um endereço válido na cache
            if(elementoExiste(linhas, colunas, i, j - 1) == 1) {
                amigos_da_esquerda = cache[i][j - 1] + percurso->matriz_adj[esquina_da_esquerda][esquina_atual];
                //atualiza o número de amigos que você cumprimentou passando pelo caminho da esquerda
            }
            
            cache[i][j] = max(amigos_de_cima, amigos_da_esquerda); //quero encontrar o número máximo de amigos que é possível cumprimentar
        }
    }

    return cache[linhas - 1][colunas - 1];
}


int percurso_pd(TipoGrafo *percurso, int linhas, int colunas, int vertice) {
    //cache bidimensional em que, em cache[i][j], i representa a esquina da qual o usuário saiu e j representa a esquina em que ele chegou
    int **cache = (int **)malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++) {
        cache[i] = (int *)malloc((colunas) * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            cache[i][j] = -1; //inicializa a cache com um valor inválido
        }
    }
    
    int res = percurso_pd_aux(cache, percurso, linhas, colunas);
    
    //liberar memória da cache
    for (int i = 0; i < linhas; i++) {
        free(cache[i]);
    }
    
    free(cache);
    
    return res;
}
int main(void) {
    int linhas, colunas, esquinas;

    //leitura da quantidade de linhas e colunas
    scanf("%d", &linhas);
    scanf("%d", &colunas);
    esquinas = linhas * colunas;
    
    //criação de um grafo em que o número de vértices = esquinas
    TipoGrafo gr = criarGrafo(esquinas);

    int arestas, chegada, saida, n_amigos;

    //descobre a quantidade de arestas
    arestas = linhas * (colunas - 1) + colunas * (linhas - 1);
    
    //coloca a quantidade de amigos que podemos cumprimentar ao passarmos por essas arestas
    for (int i = 0; i < arestas; i++) {
        scanf(" %d %d %d", &saida, &chegada, &n_amigos);
        criarAresta(&gr, saida, chegada, n_amigos);
    }

    //chama a função para determinar o número máximo que podemos realizar com essa configuração
    int max_cumprimentos = percurso_pd(&gr, linhas, colunas, 0);
    printf("%d\n", max_cumprimentos);

    //libera memória do grafo
    limparGrafo(&gr);

    return 0;
}
