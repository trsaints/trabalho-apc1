#include <stdio.h>
#include <stdlib.h>

struct jogo
{
  int _REPRINT,
      estado, // 0 é Jogador 0, 1 é Jogador X, 2 é novo_jogo.reprint
      _ACAO_ATUAL,
      partida_acabou,
      pode_mover,
      pecas_X,
      pecas_O;
};

int main()
{
  int entrada_correta = 0;
  char tabuleiro[8][8];
  // se tão na mesma linha os is são iguais, se tão na mesma coluna os jotas são iguais
  int linha_origem, coluna_origem;   // posição da peça no tabuleiro
  int linha_destino, coluna_destino; // para onde a peça quer ir

  for (linha_origem = 0; linha_origem < 8; linha_origem++)
    for (coluna_origem = 0; coluna_origem < 8; coluna_origem++)
    {
      if ((linha_origem + coluna_origem) % 2 == 0)
        tabuleiro[linha_origem][coluna_origem] = ' ';
      else
      {
        if (linha_origem < 3)
          tabuleiro[linha_origem][coluna_origem] = 'O';
        else if (linha_origem > 4)
          tabuleiro[linha_origem][coluna_origem] = 'X';
        else
          tabuleiro[linha_origem][coluna_origem] = ' ';
      }
    }

  struct jogo novo_jogo = {1, 2, 1, 0, 0, 12, 12};

  while (novo_jogo.partida_acabou == 0)
  {
    while (novo_jogo.estado == 2)
    {
      if (novo_jogo._REPRINT == 1)
      {
        entrada_correta = system("clear");

        for (linha_origem = 0; linha_origem < 8; linha_origem++)
        {
          for (coluna_origem = 0; coluna_origem < 8; coluna_origem++)
            printf(" %c", tabuleiro[linha_origem][coluna_origem]);

          printf(" %d\n", (linha_origem + 1));
        }

        printf(" 1 2 3 4 5 6 7 8\n");
        novo_jogo._REPRINT = 0;
      }

      novo_jogo.estado = novo_jogo._ACAO_ATUAL;
    }

    while (novo_jogo.estado == 1)
    {
      int pecas_esgotaram = novo_jogo.pecas_X == 0 || novo_jogo.pecas_O == 0;

      if (pecas_esgotaram)
      {
        novo_jogo.estado = 2;
        novo_jogo._REPRINT = 1;
        novo_jogo._ACAO_ATUAL = 3;
      }

      printf("X, escolha a peça que deseja mover (linha coluna): ");

      entrada_correta = scanf("%d %d", &linha_origem, &coluna_origem),
      linha_origem = linha_origem - 1,
      coluna_origem = coluna_origem - 1;

      while (getchar() != '\n')
        ;

      int nao_tem_x = tabuleiro[linha_origem][coluna_origem] != 'X';

      if (nao_tem_x)
      {
        printf("Nenhuma peça X encontrada. Precione ENTER para escolher novamente\n");
        getchar();

        linha_origem = 0,
        coluna_origem = 0,
        linha_destino = 0,
        coluna_destino = 0;
      }
      else
      {
        int tem_diagonal_livre = tabuleiro[linha_origem - 1][coluna_origem + 1] == ' ' || tabuleiro[linha_origem - 1][coluna_origem - 1] == ' ';
        int peca_colidiu_a_esquerda = tabuleiro[linha_origem - 1][coluna_origem + 1] == 'O' && tabuleiro[linha_origem - 2][coluna_origem + 2] == ' ';
        int peca_colidiu_a_direita = tabuleiro[linha_origem - 1][coluna_origem - 1] == 'O' && tabuleiro[linha_origem - 2][coluna_origem - 2] == ' ';

        if (tem_diagonal_livre)
          novo_jogo.pode_mover = 1;

        if (peca_colidiu_a_esquerda)
          novo_jogo.pode_mover = 1;

        if (peca_colidiu_a_direita)
          novo_jogo.pode_mover = 1;
      }

      if (novo_jogo.pode_mover == 1)
      {
        printf("X, escolha a posição para onde deseja mover a peça (linha "
               "coluna): ");

        entrada_correta = scanf("%i %i", &linha_destino, &coluna_destino),
        linha_destino = linha_destino - 1,
        coluna_destino = coluna_destino - 1;

        while (getchar() != '\n')
          ;

        int movimento_valido = linha_destino == linha_origem - 1;

        if (movimento_valido)
        {
          int pode_ir_para_diagonal = coluna_destino == coluna_origem + 1 || coluna_destino == coluna_origem - 1;
          int peca_colide_em_diagonal = tabuleiro[linha_destino][coluna_destino] == 'O';

          if (pode_ir_para_diagonal)
          {
            if (tabuleiro[linha_destino][coluna_destino] == ' ')
            {
              tabuleiro[linha_destino][coluna_destino] = 'X';
              tabuleiro[linha_origem][coluna_origem] = ' ';
              novo_jogo._ACAO_ATUAL = 0;
              novo_jogo.estado = 2;
            }
            else if (peca_colide_em_diagonal) // tabuleiro[h][k] != 'X'
            {
              if (coluna_destino < coluna_origem)
              {
                if (tabuleiro[linha_origem - 2][coluna_origem - 2] == ' ')
                {
                  tabuleiro[linha_destino][coluna_destino] = ' ';
                  tabuleiro[linha_origem][coluna_origem] = ' ';
                  tabuleiro[linha_origem - 2][coluna_origem - 2] = 'X';
                  novo_jogo.pecas_O = novo_jogo.pecas_O - 1;
                  novo_jogo._ACAO_ATUAL = 0;
                  novo_jogo.estado = 2;
                }
              }
              else if (coluna_destino > coluna_origem)
              { // isso é um fallback, deve da 1 sempre
                if (tabuleiro[linha_origem - 2][coluna_origem + 2] == ' ')
                {
                  tabuleiro[linha_destino][coluna_destino] = ' ';
                  tabuleiro[linha_origem][coluna_origem] = ' ';
                  tabuleiro[linha_origem - 2][coluna_origem + 2] = 'X';
                  novo_jogo.pecas_O = novo_jogo.pecas_O - 1;
                  novo_jogo._ACAO_ATUAL = 0;
                  novo_jogo.estado = 2;
                }
              }
            }
          }
        }
        if (novo_jogo.estado == 1)
        {
          printf("Nenhum movimento possível para a peça escolhida. Precione "
                 "ENTER para escolher novamente\n");
          getchar();
          linha_origem = 0;
          coluna_origem = 0;
          linha_destino = 0;
          coluna_destino = 0;
          novo_jogo._REPRINT = 1;
          novo_jogo.estado = 2;
          novo_jogo._ACAO_ATUAL = 1;
        }
      }
    }
    while (novo_jogo.estado == 0)
    {
      printf("Teste deu certo");

      getchar();
      while (getchar() != '\n')
        ;

      novo_jogo.estado = 3;
    }
  }

  return 0;
}