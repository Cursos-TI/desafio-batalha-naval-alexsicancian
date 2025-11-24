#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Verifica se é possível posicionar um navio horizontalmente
int podePosicionarHorizontal(int tabuleiro[][TAMANHO_TABULEIRO],
                             int linha, int colunaInicial) {
    if (linha < 0 || linha >= TAMANHO_TABULEIRO) return 0;
    if (colunaInicial < 0 || colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][colunaInicial + i] != AGUA) return 0;
    }
    return 1;
}

// Verifica se é possível posicionar um navio verticalmente
int podePosicionarVertical(int tabuleiro[][TAMANHO_TABULEIRO],
                           int linhaInicial, int coluna) {
    if (coluna < 0 || coluna >= TAMANHO_TABULEIRO) return 0;
    if (linhaInicial < 0 || linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linhaInicial + i][coluna] != AGUA) return 0;
    }
    return 1;
}

// Verifica se é possível posicionar um navio na diagonal principal (\)
int podePosicionarDiagonalPrincipal(int tabuleiro[][TAMANHO_TABULEIRO],
                                    int linhaInicial, int colunaInicial) {
    if (linhaInicial < 0 || linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    if (colunaInicial < 0 || colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linhaInicial + i][colunaInicial + i] != AGUA) return 0;
    }
    return 1;
}

// Verifica se é possível posicionar um navio na diagonal secundária (/)
int podePosicionarDiagonalSecundaria(int tabuleiro[][TAMANHO_TABULEIRO],
                                     int linhaInicial, int colunaInicial) {
    if (linhaInicial < 0 || linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    if (colunaInicial < 0 || colunaInicial >= TAMANHO_TABULEIRO) return 0;
    if (colunaInicial - (TAMANHO_NAVIO - 1) < 0) return 0; // não pode "passar" da coluna 0

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linhaInicial + i][colunaInicial - i] != AGUA) return 0;
    }
    return 1;
}

// Exibe o tabuleiro na tela
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

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Navios (tamanho 3, representados por 3)
    int navio1[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO}; // horizontal
    int navio2[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO}; // vertical
    int navio3[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO}; // diagonal \
    int navio4[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO}; // diagonal /

    // Inicializa tabuleiro com água
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Coordenadas escolhidas diretamente no código
    // Navio 1: horizontal
    int linhaNavio1 = 1;
    int colunaNavio1 = 1; // ocupa (1,1) (1,2) (1,3)

    // Navio 2: vertical
    int linhaNavio2 = 2;
    int colunaNavio2 = 7; // ocupa (2,7) (3,7) (4,7)

    // Navio 3: diagonal principal (\)
    int linhaNavio3 = 6;
    int colunaNavio3 = 0; // ocupa (6,0) (7,1) (8,2)

    // Navio 4: diagonal secundária (/)
    int linhaNavio4 = 0;
    int colunaNavio4 = 8; // ocupa (0,8) (1,7) (2,6)

    // Posiciona navio 1 (horizontal)
    if (!podePosicionarHorizontal(tabuleiro, linhaNavio1, colunaNavio1)) {
        printf("Erro ao posicionar navio 1 (horizontal).\n");
        return 1;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaNavio1][colunaNavio1 + i] = navio1[i];
    }

    // Posiciona navio 2 (vertical)
    if (!podePosicionarVertical(tabuleiro, linhaNavio2, colunaNavio2)) {
        printf("Erro ao posicionar navio 2 (vertical).\n");
        return 1;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaNavio2 + i][colunaNavio2] = navio2[i];
    }

    // Posiciona navio 3 (diagonal principal \)
    if (!podePosicionarDiagonalPrincipal(tabuleiro, linhaNavio3, colunaNavio3)) {
        printf("Erro ao posicionar navio 3 (diagonal principal).\n");
        return 1;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaNavio3 + i][colunaNavio3 + i] = navio3[i];
    }

    // Posiciona navio 4 (diagonal secundaria /)
    if (!podePosicionarDiagonalSecundaria(tabuleiro, linhaNavio4, colunaNavio4)) {
        printf("Erro ao posicionar navio 4 (diagonal secundaria).\n");
        return 1;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaNavio4 + i][colunaNavio4 - i] = navio4[i];
    }

    // Exibe o tabuleiro final
    printf("Tabuleiro de Batalha Naval (0 = agua, 3 = navio):\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
