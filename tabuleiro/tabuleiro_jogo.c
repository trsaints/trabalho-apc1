#include <stdio.h>
#include <stdlib.h>

int main() {
  char tabuleiro[8][8]; // se tão na mesma linha os is são iguais, se tão na mesma coluna os jotas são iguais
  int i, j;// posição da peça no tabuleiro
  int h, k;// para onde a peça quer ir
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
  int deu_certo;
  int reprint = 1;
  int vez = 2; // 0 é Jogador 0, 1 é Jogador X, 2 é reprint
  int proxima_vez = 1;
  int ganhou = 0;
  int peca_tem_moves = 0;
  int pecas_X = 12;
  int pecas_O = 12;
  while (ganhou == 0) {
    
    while (vez == 2) {
      if (reprint == 1) {
        deu_certo = system("clear");
        for (i = 0; i < 8; i++) {
          for (j = 0; j < 8; j++) {
            printf(" %c", tabuleiro[i][j]);
          }
          printf(" %d\n", (i + 1));
        }
        printf(" 1 2 3 4 5 6 7 8\n");
        reprint = 0;
        vez = proxima_vez;
      }
    }
    
    while (vez == 1) {
      if (pecas_X == 0 || pecas_O == 0) {
        vez = 2;
        reprint = 1;
        proxima_vez = 3;
      }
      printf("X, escolha a peça que deseja mover (linha coluna): ");
      deu_certo = scanf("%d %d", &i, &j);
      i = i - 1;
      j = j - 1;
      while (getchar() != '\n');
      if (tabuleiro[i][j] != 'X') {
        printf("Nenhuma peça X encontrada. Precione ENTER para escolher novamente\n");
        getchar();
        i = 0;
        j = 0;
        h = 0;
        k = 0;
      } else if (tabuleiro[i][j] == 'X') {
        if (tabuleiro[i - 1][j + 1] == ' ' || tabuleiro[i - 1][j - 1] == ' ') {
          peca_tem_moves = 1;
        }
        if (tabuleiro[i - 1][j + 1] == 'O' && tabuleiro[i - 2][j + 2] == ' ') {
          peca_tem_moves = 1;
        }
        if (tabuleiro[i - 1][j - 1] == 'O' && tabuleiro[i - 2][j - 2] == ' ') {
          peca_tem_moves = 1;
        }
      }
      if (peca_tem_moves == 1) {
        printf("X, escolha a posição para onde deseja mover a peça (linha "
               "coluna): ");
        deu_certo = scanf("%i %i", &h, &k);
        h = h - 1;
        k = k - 1;
        while (getchar() != '\n');
        if (h == i - 1) {
          if (k == j + 1 || k == j - 1) {
            if (tabuleiro[h][k] == ' ') {
              tabuleiro[h][k] = 'X';
              tabuleiro[i][j] = ' ';
              proxima_vez = 0;
              vez = 2;
            } else if (tabuleiro[h][k] == 'O') {
              if (k < j) {
                if (tabuleiro[i - 2][j - 2] == ' ') {
                  tabuleiro[h][k] = ' ';
                  tabuleiro[i][j] = ' ';
                  tabuleiro[i - 2][j - 2] = 'X';
                  pecas_O = pecas_O - 1;
                  proxima_vez = 0;
                  vez = 2;
                }
              } else if (k > j) { // isso é um fallback, deve da 1 sempre
                if (tabuleiro[i - 2][j + 2] == ' ') {
                  tabuleiro[h][k] = ' ';
                  tabuleiro[i][j] = ' ';
                  tabuleiro[i - 2][j + 2] = 'X';
                  pecas_O = pecas_O - 1;
                  proxima_vez = 0;
                  vez = 2;
                }
              }
            }
          }
        }
        if (vez == 1) {
          printf("Nenhum movimento possível para a peça escolhida. Precione "
                 "ENTER para escolher novamente\n");
          getchar();
          i = 0;
          j = 0;
          h = 0;
          k = 0;
          reprint = 1;
          vez = 2;
          proxima_vez = 1;
        }
      }
    }
    while (vez == 0) {
      printf("Teste deu certo");
      getchar();
      while (getchar() != '\n');
      vez = 3;
    }
  }
  return 0;
}