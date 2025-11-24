#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAM_HABILIDADE 5

#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// ---------- Funções utilitárias do tabuleiro ----------

// Inicializa o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Exibe o tabuleiro com índices de linha/coluna
// 0 = água, 3 = navio, 5 = área de habilidade
void exibirTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// ---------- Criação dinâmica das matrizes de habilidade ----------

// Preenche uma matriz 5x5 em forma de cone apontando para baixo.
// Origem do cone = topo, posição (0,2) na matriz de habilidade.
void criarHabilidadeCone(int cone[][TAM_HABILIDADE]) {
    int centro = 2;      // coluna do "meio" (0..4)
    int raioMax = 2;     // altura útil do cone (3 linhas)

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Começa tudo como 0 (não afetado)
            cone[i][j] = 0;

            // As linhas de 0 até raioMax formam o cone
            if (i <= raioMax) {
                // Para cada linha i, o cone "abre" do centro-i até centro+i
                if (j >= centro - i && j <= centro + i) {
                    cone[i][j] = 1;
                }
            }
        }
    }
}

// Preenche uma matriz 5x5 em forma de cruz, origem no centro (2,2).
void criarHabilidadeCruz(int cruz[][TAM_HABILIDADE]) {
    int centro = 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // 1 na linha central ou na coluna central, 0 nos demais
            if (i == centro || j == centro) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }
}

// Preenche uma matriz 5x5 em forma de octaedro (losango), origem no centro (2,2).
void criarHabilidadeOctaedro(int octa[][TAM_HABILIDADE]) {
    int centro = 2;
    int raio = 2; // controla o "tamanho" do losango

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int dist = (i - centro);
            if (dist < 0) dist = -dist;
            int dist2 = (j - centro);
            if (dist2 < 0) dist2 = -dist2;

            // Distância de Manhattan ao centro menor ou igual ao raio
            if (dist + dist2 <= raio) {
                octa[i][j] = 1;
            } else {
                octa[i][j] = 0;
            }
        }
    }
}

// ---------- Aplicando a habilidade no tabuleiro ----------
//
// origemTabLinha / origemTabColuna: ponto de origem da habilidade no tabuleiro
// origemHabLinha / origemHabColuna: posição da origem dentro da matriz de habilidade
// Ex.: cone -> origem no topo (0,2)
//      cruz / octa -> origem no centro (2,2)
void aplicarHabilidadeNoTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO],
                                  int habilidade[][TAM_HABILIDADE],
                                  int origemTabLinha,
                                  int origemTabColuna,
                                  int origemHabLinha,
                                  int origemHabColuna) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                // Calcula a posição correspondente no tabuleiro
                int linhaTab = origemTabLinha + (i - origemHabLinha);
                int colunaTab = origemTabColuna + (j - origemHabColuna);

                // Garante que está dentro dos limites 10x10
                if (linhaTab >= 0 && linhaTab < TAMANHO_TABULEIRO &&
                    colunaTab >= 0 && colunaTab < TAMANHO_TABULEIRO) {

                    // Marca área de habilidade somente em água,
                    // para não "apagar" navios (3).
                    if (tabuleiro[linhaTab][colunaTab] == AGUA) {
                        tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Matrizes 5x5 para as habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octa[TAM_HABILIDADE][TAM_HABILIDADE];

    // 1) Inicializa tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // 2) Posiciona alguns navios (3 casas cada) só para visualização
    //    (coordenadas escolhidas manualmente, sem sobreposição)
    // Navio horizontal: linha 1, colunas 1 a 3
    tabuleiro[1][1] = NAVIO;
    tabuleiro[1][2] = NAVIO;
    tabuleiro[1][3] = NAVIO;

    // Navio vertical: coluna 7, linhas 2 a 4
    tabuleiro[2][7] = NAVIO;
    tabuleiro[3][7] = NAVIO;
    tabuleiro[4][7] = NAVIO;

    // Navio diagonal (\)
    tabuleiro[6][0] = NAVIO;
    tabuleiro[7][1] = NAVIO;
    tabuleiro[8][2] = NAVIO;

    // Navio diagonal (/)
    tabuleiro[0][8] = NAVIO;
    tabuleiro[1][7] = NAVIO;
    tabuleiro[2][6] = NAVIO;

    // 3) Cria as matrizes de habilidade usando loops + condicionais
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octa);

    // 4) Define pontos de origem das habilidades no tabuleiro
    //    (escolhidos para não baterem nos navios, só em água)
    //
    // Cone: origem no topo da forma (0,2) da matriz -> vamos colocar em (4,4) no tabuleiro
    int origemConeTabLinha = 4;
    int origemConeTabColuna = 4;
    int origemConeHabLinha = 0;
    int origemConeHabColuna = 2;

    // Cruz: origem no centro (2,2) -> colocar em (5,5) no tabuleiro
    int origemCruzTabLinha = 5;
    int origemCruzTabColuna = 5;
    int origemCruzHabLinha = 2;
    int origemCruzHabColuna = 2;

    // Octaedro: origem no centro (2,2) -> colocar em (7,7) no tabuleiro
    int origemOctaTabLinha = 7;
    int origemOctaTabColuna = 7;
    int origemOctaHabLinha = 2;
    int origemOctaHabColuna = 2;

    // 5) Aplica as habilidades no tabuleiro
    aplicarHabilidadeNoTabuleiro(tabuleiro, cone,
                                 origemConeTabLinha, origemConeTabColuna,
                                 origemConeHabLinha, origemConeHabColuna);

    aplicarHabilidadeNoTabuleiro(tabuleiro, cruz,
                                 origemCruzTabLinha, origemCruzTabColuna,
                                 origemCruzHabLinha, origemCruzHabColuna);

    aplicarHabilidadeNoTabuleiro(tabuleiro, octa,
                                 origemOctaTabLinha, origemOctaTabColuna,
                                 origemOctaHabLinha, origemOctaHabColuna);

    // 6) Exibe o tabuleiro final
    printf("Tabuleiro (0 = agua, 3 = navio, 5 = area de habilidade):\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
