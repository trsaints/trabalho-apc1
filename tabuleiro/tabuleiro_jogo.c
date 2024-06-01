#include <stdio.h>
#include <stdlib.h>

int main() {
  char tabuleiro[8][8];
  int i, j;
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      if ((i + j) % 2 == 0) {
        tabuleiro[i][j] = ' ';
      } else {
        if (i < 3) {
          tabuleiro[i][j] = 'O';
        } else if (i > 4) {
          tabuleiro[i][j] = 'X';
        } else {
          tabuleiro[i][j] = ' ';
        }
      }
    }
  }

  int deu_certo = system("clear");
  int reprint = 1;
  while (reprint == 1) {
    for (i = 0; i < 8; i++) {
      for (j = 0; j < 8; j++) {
        printf(" %c", tabuleiro[i][j]);
      }
      printf(" %d\n", (i + 1));
    }
    printf(" 1 2 3 4 5 6 7 8\n");
  }
  int vez = 0; // 0 é Jogador 0, 1 é Jogador X
  int peca_tem_moves = 0;
  while (vez == 1) {
    printf("X, escolha a peça que deseja mover (linha coluna): ");
    deu_certo = scanf("%d %d", &i, &j);
    while (getchar() != '\n')
      ;
    if (tabuleiro[i - 1][j - 1] != 'X') {
      printf("Nenhuma peça X encontrada.\n");
    } else if (j == 0 || j == 7) {
      if (j == 0) {
        if (tabuleiro[i - 1][j + 1] == ' ') {
          peca_tem_moves = 1;
        } else if (tabuleiro[i - 1][j + 1] == '0') {
          if (tabuleiro[i - 2][j + 2] == ' ' || tabuleiro[i-2][j-2] == ' '){
            peca_tem_moves = 1;
          }
        }
      }
      if (peca_tem_moves == 1) {
        printf("X, escolha a posição para onde deseja mover a peça (linha coluna): ");
        deu_certo = scanf("%d %d", &i, &j);
        while (getchar() != '\n')
          ;
      }
    }
  }
  return 0;
}
