#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define FALSE 0
#define TRUE 1

#define ARRAY_SIZE(X) (sizeof(X) / sizeof(*X))

enum EstadoJogo
{
  ESTADO_JOGADOR,
  TURNO,
  ESTADO_REPRINT
};

struct Posicao
{
  int lin;
  int col;
};

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
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8); // Resolve problema de acentuação no windows
#endif
  char buffer_linha[256];

  int entrada_correta = 0;
  char tabuleiro[8][8];
  // se tão na mesma linha os is são iguais, se tão na mesma coluna os jotas são iguais

  struct Posicao origem;  // posição da peça no tabuleiro
  struct Posicao destino; // para onde a peça quer ir

  char simbolo_turno = 'X';
  char simbolo_oponente = 'O';

  // char tmp = simbolo_oponente;
  // simbolo_oponente = simbolo_turno;
  // simbolo_turno = tmp;

  for (int linha = 0; linha < 8; linha++)
    for (int coluna = 0; coluna < 8; coluna++)
    {
      int pos = linha + coluna;
      tabuleiro[linha][coluna] =
          ((pos % 2) == 0) ? ' ' : (linha < 3) ? 'O'
                               : (linha > 4)   ? 'X'
                                             /* else */
                                             : ' ';
    }

  struct jogo partida = {
      ._REPRINT = TRUE,
      .estado = ESTADO_REPRINT,
      ._ACAO_ATUAL = 1,
      .partida_acabou = 0,
      .pode_mover = FALSE,
      .pecas_X = 12,
      .pecas_O = 12};

  while (partida.partida_acabou == FALSE)
  {
    while (partida.estado == ESTADO_REPRINT)
    {
      if (partida._REPRINT)
      {
        entrada_correta = system("clear");

        for (int linha = 0; linha < 8; linha++)
        {
          for (int coluna = 0; coluna < 8; coluna++)
            printf(" %c", tabuleiro[linha][coluna]);

          printf(" %d\n", (linha + 1));
        }

        printf(" 1 2 3 4 5 6 7 8\n");
        partida._REPRINT = FALSE;
      }

      partida.estado = partida._ACAO_ATUAL;
    }

    while (partida.estado == TURNO)
    {
      int pecas_esgotaram = (partida.pecas_X == 0) || (partida.pecas_O == 0);

      if (pecas_esgotaram)
      {
        partida.estado = ESTADO_REPRINT;
        partida._REPRINT = TRUE;
        partida._ACAO_ATUAL = 3;
      }

      do
      {
        printf("%c, escolha a peça que deseja mover (linha coluna): ", simbolo_turno);
        fgets(buffer_linha, sizeof(buffer_linha), stdin);
        entrada_correta = sscanf(buffer_linha, "%d %d", &origem.lin, &origem.col);
      } while (entrada_correta < 2);

      origem.lin--;
      origem.col--;

      int peca_nao_existe = (tabuleiro[origem.lin][origem.col] != simbolo_turno);

      if (peca_nao_existe)
      {
        printf("Nenhuma peça %c encontrada. Precione ENTER para escolher novamente\n", simbolo_turno);
        while (getchar() != '\n')
          ;
        origem = (struct Posicao){0, 0};
        destino = (struct Posicao){0, 0};
      }
      else
      {
        int tem_diagonal_livre = FALSE,
            peca_colidiu_a_esquerda = FALSE,
            peca_colidiu_a_direita = FALSE;

        switch (simbolo_turno)
        {
        case 'O': // tabuleiro[origem.lin + (1*var)] var = 1 em X, var = -1 em O
          tem_diagonal_livre = (tabuleiro[origem.lin - 1][origem.col + 1] == ' ') || (tabuleiro[origem.lin - 1][origem.col - 1] == ' ');
          peca_colidiu_a_esquerda = (tabuleiro[origem.lin - 1][origem.col + 1] == simbolo_oponente) && (tabuleiro[origem.lin - 2][origem.col + 2] == ' ');
          peca_colidiu_a_direita = (tabuleiro[origem.lin - 1][origem.col - 1] == simbolo_oponente) && (tabuleiro[origem.lin - 2][origem.col - 2] == ' ');

          break;

        case 'X':
          tem_diagonal_livre = (tabuleiro[origem.lin + 1][origem.col + 1] == ' ') || (tabuleiro[origem.lin + 1][origem.col - 1] == ' ');
          peca_colidiu_a_esquerda = (tabuleiro[origem.lin + 1][origem.col + 1] == simbolo_oponente) && (tabuleiro[origem.lin + 2][origem.col + 2] == ' ');
          peca_colidiu_a_direita = (tabuleiro[origem.lin + 1][origem.col - 1] == simbolo_oponente) && (tabuleiro[origem.lin + 2][origem.col - 2] == ' ');

          break;
        }

        partida.pode_mover = tem_diagonal_livre || peca_colidiu_a_esquerda || peca_colidiu_a_direita;
      }
      if (partida.pode_mover == FALSE)
        continue;

      do
      {
        printf("%c, escolha a posição para onde deseja mover a peça (linha "
               "coluna): ",
               simbolo_turno);
        fgets(buffer_linha, sizeof(buffer_linha), stdin);
        entrada_correta = sscanf(buffer_linha, "%i %i", &destino.lin, &destino.col);
      } while (entrada_correta < 2);

      destino.lin--;
      destino.col--;

      int movimento_valido = (destino.lin == (origem.lin - 1));

      if (movimento_valido)
      {
        int pode_ir_para_diagonal = (destino.col == origem.col + 1) || (destino.col == origem.col - 1);

        if (pode_ir_para_diagonal)
        {
          int peca_colide_em_diagonal = (tabuleiro[destino.lin][destino.col] == simbolo_oponente);

          if (tabuleiro[destino.lin][destino.col] == ' ')
          {
            tabuleiro[destino.lin][destino.col] = simbolo_turno;
            tabuleiro[origem.lin][origem.col] = ' ';
            partida._ACAO_ATUAL = 0;
            partida.estado = 2;
          }
          else if (peca_colide_em_diagonal)
          {
            int direcao = (destino.col < origem.col)   ? -1
                          : (destino.col > origem.col) ? 1
                                                       /* else */
                                                       : 0;
            int pode_capturar = 0;

            switch (simbolo_turno)
            {
            case 'X':
              pode_capturar = (direcao != 0) && (tabuleiro[origem.lin - 2][origem.col + 2 * direcao] == ' ');

              if (pode_capturar)
              {
                tabuleiro[destino.lin][destino.col] = ' ';
                tabuleiro[origem.lin][origem.col] = ' ';
                tabuleiro[origem.lin - 2][origem.col + 2 * direcao] = simbolo_turno;
                partida.pecas_O = partida.pecas_O - 1;
                partida._ACAO_ATUAL = 0;
                partida.estado = 2;
              }

              break;

            case 'O':
              pode_capturar = (direcao != 0) && (tabuleiro[origem.lin + 2][origem.col + 2 * direcao] == ' ');

              if (pode_capturar)
              {
                tabuleiro[destino.lin][destino.col] = ' ';
                tabuleiro[origem.lin][origem.col] = ' ';
                tabuleiro[origem.lin + 2][origem.col + 2 * direcao] = simbolo_turno;
                partida.pecas_X = partida.pecas_X - 1;
                partida._ACAO_ATUAL = 1;
                partida.estado = 2; // depois disso, o codigo continua? ou ele passa pro outro while?
              }

              break;
            }
          }
        }
      }

      if (partida.estado == TURNO)
      {
        printf("Nenhum movimento possível para a peça escolhida. Pressione "
               "ENTER para escolher novamente\n");
        getchar();
        origem = (struct Posicao){0, 0};
        destino = (struct Posicao){0, 0};
        partida._REPRINT = TRUE;
        partida.estado = ESTADO_REPRINT;
        partida._ACAO_ATUAL = 1;

        continue;
      }

      char tmp = simbolo_oponente;
      simbolo_oponente = simbolo_turno;
      simbolo_turno = tmp;
    }

    while (partida.estado == ESTADO_JOGADOR)
    {
      // TODO
      partida._REPRINT = TRUE;
      partida.estado = ESTADO_REPRINT;
      partida._ACAO_ATUAL = 1;
    }
  }

  return 0;
}