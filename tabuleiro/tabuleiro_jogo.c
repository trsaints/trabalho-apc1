#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define FALSE 0
#define TRUE 1

#define ANSI_BG_WHITE "\x1b[47m"
#define ANSI_BG_BLACK "\x1b[40m"
#define ANSI_COLOR_RESET "\x1b[0m"

enum EstadoJogo
{
    JOGADOR,
    TURNO,
    REPRINT
};

struct Posicao
{
    int lin;
    int col;
};

struct jogo
{
    unsigned int _REPRINT,
        estado,
        _ACAO_ATUAL,
        acabou,
        pecas_X,
        pecas_O;

    int sentido;
};

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Resolve problema de acentuação no windows
#endif

    struct jogo partida = {
        ._REPRINT = TRUE,
        .estado = REPRINT,
        ._ACAO_ATUAL = 1,
        .acabou = FALSE,
        .pecas_X = 11,
        .pecas_O = 1,
        .sentido = 0};

    char buffer_linha[256],
        tabuleiro[8][8];

    int entrada_correta = 0;
    int posicao_esta_vazia = FALSE;

    struct Posicao origem,
        destino;

    char simbolo_turno = 'X',
         simbolo_oponente = 'O';

    for (int linha = 0; linha < 8; linha++)
        for (int coluna = 0; coluna < 8; coluna++)
        {
            int pos = linha + coluna;
            tabuleiro[linha][coluna] =
                ((pos % 2) == 0) ? ' '
                : (linha < 3)    ? 'O'
                : (linha > 4)    ? 'X'
                                 : ' ';
        }

    while (partida.acabou == FALSE)
    {
        while (partida.estado == REPRINT)
        {
            if (partida._REPRINT)
            {
                entrada_correta = system("clear");

                for (int linha = 0; linha < 8; linha++)
                {
                    for (int coluna = 0; coluna < 8; coluna++)
                    {
                        int pos = linha + coluna;
                        posicao_esta_vazia = (pos % 2) == 0;

                        if (posicao_esta_vazia)
                            printf(ANSI_BG_WHITE "%c " ANSI_COLOR_RESET, tabuleiro[linha][coluna]);
                        else
                            printf(ANSI_BG_BLACK "%c " ANSI_COLOR_RESET, tabuleiro[linha][coluna]);
                    }

                    printf(" %d\n", (linha + 1));
                }

                printf(" 1 2 3 4 5 6 7 8\n");
                partida._REPRINT = FALSE;
            }

            partida.estado = partida._ACAO_ATUAL;
            partida._REPRINT = TRUE;
        }

        while (partida.estado == TURNO)
        {
            int pecas_esgotaram = FALSE;
            partida.sentido = (simbolo_turno == 'X') ? -1 : 1;

            do
            {
                printf("%c, escolha a peça que deseja mover (linha coluna): ", simbolo_turno);
                fgets(buffer_linha, sizeof(buffer_linha), stdin);
                entrada_correta = sscanf(buffer_linha, "%d %d", &origem.lin, &origem.col);
            } while (entrada_correta < 2);

            origem.lin--;
            origem.col--;

            posicao_esta_vazia = (tabuleiro[origem.lin][origem.col] == ' ');

            if (posicao_esta_vazia)
            {
                printf("Nenhuma peça %c encontrada. Precione ENTER para escolher novamente\n", simbolo_turno);
                while (getchar() != '\n')
                    ;

                origem = (struct Posicao){0, 0};
                destino = (struct Posicao){0, 0};
                partida.estado = REPRINT;

                continue;
            }

            do
            {
                printf("%c, escolha a posição para onde deseja mover a peça (linha coluna): ",
                       simbolo_turno);
                fgets(buffer_linha, sizeof(buffer_linha), stdin);
                entrada_correta = sscanf(buffer_linha, "%i %i", &destino.lin, &destino.col);
            } while (entrada_correta < 2);

            destino.lin--;
            destino.col--;

            int movimento_valido = destino.lin == (origem.lin + (partida.sentido)),
                pode_ir_para_diagonal = movimento_valido && (destino.col == origem.col + 1) ||
                                        (destino.col == origem.col - 1),
                peca_colide = pode_ir_para_diagonal &&
                              (tabuleiro[destino.lin][destino.col] == simbolo_oponente),
                peca_nao_colide = pode_ir_para_diagonal &&
                                  (tabuleiro[destino.lin][destino.col] == ' ');

            partida._ACAO_ATUAL = (peca_colide || peca_nao_colide) ? JOGADOR : TURNO;
            partida.estado = REPRINT;

            if (peca_nao_colide)
            {
                tabuleiro[destino.lin][destino.col] = simbolo_turno;
                tabuleiro[origem.lin][origem.col] = ' ';
            }
            else if (peca_colide)
            {
                int sentido_captura = (simbolo_turno == 'X') ? (origem.lin - 2) : (origem.lin + 2);

                int pode_capturar = (partida.sentido != 0) && (tabuleiro[sentido_captura][origem.col + 2 * partida.sentido] == ' ');

                if (pode_capturar)
                {
                    tabuleiro[destino.lin][destino.col] = ' ';
                    tabuleiro[origem.lin][origem.col] = ' ';
                    tabuleiro[sentido_captura][origem.col + 2 * partida.sentido] = simbolo_turno;
                }

                if (pode_capturar && (simbolo_turno == 'X'))
                    partida.pecas_O--;
                else if (pode_capturar && (simbolo_turno == 'O'))
                    partida.pecas_X--;

                pecas_esgotaram = (partida.pecas_X == 0) || (partida.pecas_O == 0);

                partida.acabou = pecas_esgotaram ? TRUE : FALSE;
            }
            else
            {
                printf("Nenhum movimento possível para a peça escolhida. Pressione "
                       "ENTER para escolher novamente\n");
                getchar();
                origem = (struct Posicao){0, 0};
                destino = (struct Posicao){0, 0};

                partida._REPRINT = TRUE;
                partida._ACAO_ATUAL = TURNO;

                continue;
            }
        }

        while (partida.estado == JOGADOR)
        {
            char tmp = simbolo_oponente;
            simbolo_oponente = simbolo_turno;
            simbolo_turno = tmp;

            partida._REPRINT = TRUE;
            partida.estado = REPRINT;
            partida._ACAO_ATUAL = TURNO;
        }
    }

    printf("Fim de jogo\n");

    return 0;
}
