#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
//  printf("Iniciando jogo.\n");
//  printf("Suas peças: O/@\n Peças do seu oponente: X/#");
  float tabuleiro[8][8];
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      tabuleiro[i][j] = i;
    }
  }
  //printf("\x1b[41m  \x1b[0m\n");
  int deu_certo = system("clear");
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
       if (j % 2 == 0) {
        if ((int)tabuleiro[i][j] % 2 == 0) {
          //tabuleiro[i][j] = 1;
          printf("\x1b[41m  \x1b[0m");
         } else {
          //tabuleiro[i][j] = 0;
          printf("\x1b[101m  \x1b[0m");
         }
       } else {
         if ((int)tabuleiro[i][j] % 2 == 0) {
           //tabuleiro[i][j] = 0;
           printf("\x1b[101m  \x1b[0m");
         } else {
           //tabuleiro[i][j] = 1;
           printf("\x1b[41m  \x1b[0m");
         }
       }
    }
    printf("\n");
  }/*
  for (int i = 0; i < 8; ++i) {
     for (int j = 0; j < 8; ++j){
       printf("%d ", (int)tabuleiro[i][j]);
     }
    printf("\n");
  }*/
  return 0;
}