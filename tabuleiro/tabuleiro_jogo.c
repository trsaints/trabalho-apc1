#include <stdio.h>
#include <stdlib.h>

int main() {
  char tabuleiro[8][8]; // se tão na mesma linha os is são iguais, se tão na mesma coluna os jotas são iguais
  int i/* mesma linha*/, j/*mesma coluna*/; // posição da peça no tabuleiro
  int h, k; // para onde a peça quer ir
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
  int reprint = 1; //reprintar o tabuleiro
  while (reprint == 1) {
    deu_certo = system("clear");
    for (i = 0; i < 8; i++) {
      for (j = 0; j < 8; j++) {
        printf(" %c", tabuleiro[i][j]);
      }
      printf(" %d\n", (i + 1));
    }
    printf(" 1 2 3 4 5 6 7 8\n");
    reprint = 0;
  }
  int vez = 0; // 0 é Jogador 0, 1 é Jogador X, no 2 alguem venceu
  int peca_tem_moves = 0;
  while (vez == 1) {
    printf("X, escolha a peça que deseja mover (linha coluna): ");
    deu_certo = scanf("%d %d", &i, &j);
    i = i-1;
    j = j-1;
    while (getchar() != '\n');
    if (tabuleiro[i][j] != 'X') {
      printf("Nenhuma peça X encontrada. Precione ENTER para escolher novamente\n");
      getchar();
      i = 0;
      j = 0;
      h = 0;
      k = 0;
    } else if (j == 0 || j == 7) {
      if (j == 0) {
        if (tabuleiro[i - 2][j] == ' ') {
          peca_tem_moves = 1;
        }
      } else {
        if (tabuleiro[i - 2][j - 2] == ' ') {
          peca_tem_moves = 1;
        }
      }
    } else {
      if (tabuleiro[i - 2][j - 2] == ' ' || tabuleiro[i - 2][j] == ' ') {
        peca_tem_moves = 1;
      } else if (tabuleiro[i - 2][j - 2] == 'O' || tabuleiro[i - 2][j] == 'O') {
        if (tabuleiro[i - 3][j - 3] == ' ' || tabuleiro[i - 3][j + 1] == ' ') {
          peca_tem_moves = 1;
        }
      }
    }
    if (peca_tem_moves == 1) {
      printf("X, escolha a posição para onde deseja mover a peça (linha coluna): ");
      deu_certo = scanf("%i %i", &h, &k);
      h = h - 1;
      k = k - 1;
      while (getchar() != '\n');
      if (tabuleiro[h - 1][k - 1] == ' ') {
        if (h - 1 == i - 2) {
          if (k - 1 == j || k - 1 == j - 2) {
            tabuleiro[i - 1][j - 1] = ' ';
            tabuleiro[h - 1][k - 1] = 'X';
            vez = 0;
          }
        }
      } else if (tabuleiro[h-1][k-1] == 'O') {
        if (tabuleiro[i-3][j-3] == ' ') {
          tabuleiro[h-1][k-1] = ' ';
          tabuleiro[i-1][j-1] = ' ';
          tabuleiro[i-3][j-3] = 'X';
        } else if (tabuleiro[i-3][j] == ' ') {
          tabuleiro[h-1][k-1] = ' ';
          tabuleiro[i-1][j-1] = ' ';
          tabuleiro[i-3][j] = 'X';
        }
      }
    }
    if (vez == 1) {
      printf("Nenhum movimento possível para a peça escolhida. Precione ENTER para escolher novamente \n");
      getchar();
      i = 0;
      j = 0;
      h = 0;
      k = 0;
    }
  }
  while (vez == 0) {}
  while (vez == 2){
    
  }
  return 0;
  }
