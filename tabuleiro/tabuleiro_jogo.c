#include <stdio.h>
#include <stdlib.h>

struct jogo
{
  int reprint,
      vez, // 0 é Jogador 0, 1 é Jogador X, 2 é novo_jogo.reprint
      proxima_vez,
      ganhou,
      peca_tem_moves,
      pecas_X,
      pecas_O;
};

int main()
{
  int entrada_correta = 0;
  char tabuleiro[8][8]; // se tão na mesma linha os is são iguais, se tão na mesma coluna os jotas são iguais
  int i, j;             // posição da peça no tabuleiro
  int h, k;             // para onde a peça quer ir

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
    {
      if ((i + j) % 2 == 0)
        tabuleiro[i][j] = ' ';
      else
      {
        if (i < 3)
          tabuleiro[i][j] = 'O';
        else if (i > 4)
          tabuleiro[i][j] = 'X';
        else
          tabuleiro[i][j] = ' ';
      }
    }

  struct jogo novo_jogo = {1, 2, 1, 0, 0, 12, 12};

  while (novo_jogo.ganhou == 0)
  {
    while (novo_jogo.vez == 2)
    {
      if (novo_jogo.reprint == 1)
      {
        entrada_correta = system("clear");

        for (i = 0; i < 8; i++)
        {
          for (j = 0; j < 8; j++)
            printf(" %c", tabuleiro[i][j]);

          printf(" %d\n", (i + 1));
        }

        printf(" 1 2 3 4 5 6 7 8\n");
        novo_jogo.reprint = 0;
      }

      novo_jogo.vez = novo_jogo.proxima_vez;
    }

    while (novo_jogo.vez == 1)
    {
      if (novo_jogo.pecas_X == 0 || novo_jogo.pecas_O == 0)
      {
        novo_jogo.vez = 2;
        novo_jogo.reprint = 1;
        novo_jogo.proxima_vez = 3;
      }

      printf("X, escolha a peça que deseja mover (linha coluna): ");

      entrada_correta = scanf("%d %d", &i, &j),
      i = i - 1,
      j = j - 1;

      while (getchar() != '\n')
        ;

      if (tabuleiro[i][j] != 'X')
      {
        printf("Nenhuma peça X encontrada. Precione ENTER para escolher novamente\n");
        getchar();

        i = 0,
        j = 0,
        h = 0,
        k = 0;
      }
      else if (tabuleiro[i][j] == 'X')
      {
        if (tabuleiro[i - 1][j + 1] == ' ' || tabuleiro[i - 1][j - 1] == ' ')
          novo_jogo.peca_tem_moves = 1;
        if (tabuleiro[i - 1][j + 1] == 'O' && tabuleiro[i - 2][j + 2] == ' ')
          novo_jogo.peca_tem_moves = 1;
        if (tabuleiro[i - 1][j - 1] == 'O' && tabuleiro[i - 2][j - 2] == ' ')
          novo_jogo.peca_tem_moves = 1;
      }
      if (novo_jogo.peca_tem_moves == 1)
      {
        printf("X, escolha a posição para onde deseja mover a peça (linha "
               "coluna): ");

        entrada_correta = scanf("%i %i", &h, &k),
        h = h - 1,
        k = k - 1;

        while (getchar() != '\n')
          ;

        if (h == i - 1)
        {
          if (k == j + 1 || k == j - 1)
          {
            if (tabuleiro[h][k] == ' ')
            {
              tabuleiro[h][k] = 'X';
              tabuleiro[i][j] = ' ';
              novo_jogo.proxima_vez = 0;
              novo_jogo.vez = 2;
            }
            else if (tabuleiro[h][k] == 'O')
            {
              if (k < j)
              {
                if (tabuleiro[i - 2][j - 2] == ' ')
                {
                  tabuleiro[h][k] = ' ';
                  tabuleiro[i][j] = ' ';
                  tabuleiro[i - 2][j - 2] = 'X';
                  novo_jogo.pecas_O = novo_jogo.pecas_O - 1;
                  novo_jogo.proxima_vez = 0;
                  novo_jogo.vez = 2;
                }
              }
              else if (k > j)
              { // isso é um fallback, deve da 1 sempre
                if (tabuleiro[i - 2][j + 2] == ' ')
                {
                  tabuleiro[h][k] = ' ';
                  tabuleiro[i][j] = ' ';
                  tabuleiro[i - 2][j + 2] = 'X';
                  novo_jogo.pecas_O = novo_jogo.pecas_O - 1;
                  novo_jogo.proxima_vez = 0;
                  novo_jogo.vez = 2;
                }
              }
            }
          }
        }
        if (novo_jogo.vez == 1)
        {
          printf("Nenhum movimento possível para a peça escolhida. Precione "
                 "ENTER para escolher novamente\n");
          getchar();
          i = 0;
          j = 0;
          h = 0;
          k = 0;
          novo_jogo.reprint = 1;
          novo_jogo.vez = 2;
          novo_jogo.proxima_vez = 1;
        }
      }
    }
    while (novo_jogo.vez == 0)
    {
      printf("Teste deu certo");

      getchar();
      while (getchar() != '\n')
        ;

      novo_jogo.vez = 3;
    }
  }

  return 0;
}