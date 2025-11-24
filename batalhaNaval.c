#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Função para verificar se é possível posicionar um navio na horizontal
int podePosicionarHorizontal(int tabuleiro[][TAMANHO_TABULEIRO],
                             int linha, int colunaInicial) {
    // Verifica se o navio "cabe" no tabuleiro
    if (linha < 0 || linha >= TAMANHO_TABULEIRO) return 0;
    if (colunaInicial < 0 || colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;

    // Verifica se já existe algo nas posições onde o navio ficará
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][colunaInicial + i] != AGUA) {
            return 0; // Já tem navio aqui, sobreposição
        }
    }

    return 1;
}

// Função para verificar se é possível posicionar um navio na vertical
int podePosicionarVertical(int tabuleiro[][TAMANHO_TABULEIRO],
                           int linhaInicial, int coluna) {
    // Verifica se o navio "cabe" no tabuleiro
    if (coluna < 0 || coluna >= TAMANHO_TABULEIRO) return 0;
    if (linhaInicial < 0 || linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;

    // Verifica se já existe algo nas posições onde o navio ficará
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linhaInicial + i][coluna] != AGUA) {
            return 0; // Já tem navio aqui, sobreposição
        }
    }

    return 1;
}

// Função para exibir o tabuleiro na tela
void exibirTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j); // Índice das colunas
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Índice das linhas
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Matriz que representa o tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Vetores que representam os navios (3 posições cada)
    int navioHorizontal[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAMANHO_NAVIO]   = {NAVIO, NAVIO, NAVIO};

    // 1) Inicializa o tabuleiro com água (0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // 2) Define as coordenadas iniciais dos navios (apenas no código)
    // Navio horizontal começando na linha 2, coluna 1
    int linhaNavioH = 2;
    int colunaNavioH = 1;

    // Navio vertical começando na linha 5, coluna 7
    int linhaNavioV = 5;
    int colunaNavioV = 7;

    // 3) Validação e posicionamento do navio horizontal
    if (!podePosicionarHorizontal(tabuleiro, linhaNavioH, colunaNavioH)) {
        printf("Erro ao posicionar navio horizontal: coordenadas invalidas ou sobreposicao.\n");
        return 1;
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaNavioH][colunaNavioH + i] = navioHorizontal[i];
    }

    // 4) Validação e posicionamento do navio vertical
    if (!podePosicionarVertical(tabuleiro, linhaNavioV, colunaNavioV)) {
        printf("Erro ao posicionar navio vertical: coordenadas invalidas ou sobreposicao.\n");
        return 1;
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaNavioV + i][colunaNavioV] = navioVertical[i];
    }

    // 5) Exibe o tabuleiro final
    printf("Tabuleiro de Batalha Naval (0 = agua, 3 = navio):\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
