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

struct Jogo
{
    unsigned int _REPRINT,
        estado,
        _ACAO_ATUAL,
        acabou;

    int sentido;

    char tabuleiro[8][8];
};

struct Jogador
{
    char nome[12];
    char simbolo;
    int pecas;
};

typedef struct Turno
{
    struct Jogador jogador,
        oponente;
};

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Resolve problema de acentuação no windows
#endif

    int opcao_escolhida;
    do
    {
        system("clear");

        printf("Menu:\n");
        printf("1. Iniciar jogo\n");
        printf("2. Sair\n");
        printf("Selecione uma opção (somente números): ");
        scanf("%d", &opcao_escolhida);

        switch (opcao_escolhida)
        {
        case 1:
            break;
        case 2:
            printf("Saindo...\n");

            return 0;
        default:
            printf("Escolha inválida choice. Tente novamente.\n");
            break;
        }
    } while ((opcao_escolhida != 2) && (opcao_escolhida != 1));

    struct Jogo partida = {
        ._REPRINT = TRUE,
        .estado = REPRINT,
        ._ACAO_ATUAL = 1,
        .acabou = FALSE,
        .sentido = 0};

    struct Jogador jogador1 = {
        .nome = "Jogador 1",
        .simbolo = 'X',
        .pecas = 11};

    struct Jogador jogador2 = {
        .nome = "Jogador 2",
        .simbolo = 'O',
        .pecas = 11};

    char buffer_linha[256];

    int entrada_correta = 0;

    struct Posicao origem,
        destino;

    do
    {
        printf("Jogador 1, qual é seu nome? ");
        fgets(buffer_linha, sizeof(buffer_linha), stdin);

        entrada_correta = sscanf(buffer_linha, "%s", &jogador1.nome);
    } while (entrada_correta < 1 || entrada_correta > 12);

    do
    {
        printf("Jogador 2, qual é seu nome? ");
        fgets(buffer_linha, sizeof(buffer_linha), stdin);

        entrada_correta = sscanf(buffer_linha, "%s", &jogador2.nome);
    } while (entrada_correta < 1 || entrada_correta > 12);

    struct Turno turno_atual = {
        .jogador = jogador1,
        .oponente = jogador2,
    };

    for (int linha = 0; linha < 8; linha++)
        for (int coluna = 0; coluna < 8; coluna++)
        {
            int pos = linha + coluna;
            partida.tabuleiro[linha][coluna] =
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
                        int posicao_nao_jogavel = (pos % 2) == 0;

                        if (posicao_nao_jogavel)
                            printf(ANSI_BG_WHITE "%c " ANSI_COLOR_RESET, partida.tabuleiro[linha][coluna]);
                        else
                            printf(ANSI_BG_BLACK "%c " ANSI_COLOR_RESET, partida.tabuleiro[linha][coluna]);
                    }

                    printf(" %d\n", (linha + 1));
                }

                printf(" 1 2 3 4 5 6 7 8\n");
                partida._REPRINT = FALSE;
            }

            partida.estado = partida._ACAO_ATUAL;
            partida._REPRINT = TRUE;

            partida.acabou = (jogador1.pecas == 0) || (jogador2.pecas == 0);
        }

        while (partida.estado == TURNO)
        {
            struct Posicao posicao_inserida;

            partida.sentido = (turno_atual.jogador.simbolo == 'X') ? -1 : 1;

            do
            {
                printf("%s, qual peça deseja mover (linha coluna)? ", turno_atual.jogador.nome);
                fgets(buffer_linha, sizeof(buffer_linha), stdin);
                entrada_correta = sscanf(buffer_linha, "%d %d", &posicao_inserida.lin, &posicao_inserida.col);
            } while (entrada_correta < 2);

            posicao_inserida.lin--;
            posicao_inserida.col--;

            int fora_do_alcance = (posicao_inserida.lin < 0) ||
                                  (posicao_inserida.lin > 7) ||
                                  (posicao_inserida.col < 0) ||
                                  (posicao_inserida.col > 7);

            int destino_vazio = (partida.tabuleiro[posicao_inserida.lin][posicao_inserida.col] == ' ');
            int tem_oponente = (partida.tabuleiro[posicao_inserida.lin][posicao_inserida.col] == turno_atual.oponente.simbolo);

            if (fora_do_alcance || destino_vazio || tem_oponente)
            {
                printf("Nenhuma peça %c encontrada. Precione ENTER para escolher novamente\n", turno_atual.jogador.simbolo);
                while (getchar() != '\n')
                    ;

                origem = (struct Posicao){0, 0};
                posicao_inserida = (struct Posicao){0, 0};
                partida.estado = REPRINT;

                continue;
            }

            origem = posicao_inserida;

            do
            {
                printf("%s, para onde deseja mover a peça (linha coluna)? ",
                       turno_atual.jogador.nome);
                fgets(buffer_linha, sizeof(buffer_linha), stdin);
                entrada_correta = sscanf(buffer_linha, "%i %i", &posicao_inserida.lin, &posicao_inserida.col);
            } while (entrada_correta < 2);

            posicao_inserida.lin--;
            posicao_inserida.col--;

            int direcao = (posicao_inserida.col > origem.col) ? 1 : -1;
            struct Posicao pos_captura = {.lin = origem.lin + (2 * partida.sentido),
                                          .col = origem.col + (2 * direcao)};

            fora_do_alcance = (posicao_inserida.lin < 0) ||
                              (posicao_inserida.lin > 7) ||
                              (posicao_inserida.col < 0) ||
                              (posicao_inserida.col > 7);

            int captura_invalida = (pos_captura.lin < 0) ||
                                   (pos_captura.lin > 7) ||
                                   (pos_captura.col < 0) ||
                                   (pos_captura.col > 7);

            destino_vazio = (partida.tabuleiro[posicao_inserida.lin][posicao_inserida.col] == ' ');
            tem_oponente = partida.tabuleiro[posicao_inserida.lin][posicao_inserida.col] == turno_atual.oponente.simbolo;

            int sentido_correto = turno_atual.jogador.simbolo == 'X'
                                      ? (posicao_inserida.lin < origem.lin)
                                      : (posicao_inserida.lin > origem.lin);

            int captura_vazia = partida.tabuleiro[pos_captura.lin][pos_captura.col] == ' ';

            int move_e_captura = tem_oponente && captura_vazia && !captura_invalida,
                move_e_nao_captura = destino_vazio && !fora_do_alcance;

            int movimento_valido = (move_e_nao_captura || move_e_captura) && sentido_correto;

            if (!movimento_valido)
            {
                printf("Movimento inválido. Pressione ENTER para escolher novamente\n");
                getchar();
                origem = (struct Posicao){0, 0};
                posicao_inserida = (struct Posicao){0, 0};
                partida.estado = REPRINT;

                continue;
            }

            destino = posicao_inserida;
            partida.estado = JOGADOR;

            if (move_e_nao_captura)
            {
                partida.tabuleiro[destino.lin][destino.col] = turno_atual.jogador.simbolo;
                partida.tabuleiro[origem.lin][origem.col] = ' ';
            }
            else if (move_e_captura)
            {
                int sentido_captura = (turno_atual.jogador.simbolo == 'X') ? (origem.lin - 2) : (origem.lin + 2);

                partida.tabuleiro[destino.lin][destino.col] = ' ';
                partida.tabuleiro[origem.lin][origem.col] = ' ';
                partida.tabuleiro[pos_captura.lin][pos_captura.col] = turno_atual.jogador.simbolo;

                turno_atual.oponente.pecas--;
            }
            else
            {
                printf("Nenhum movimento possível para a peça escolhida. Pressione "
                       "ENTER para escolher novamente\n");
                getchar();
                origem = (struct Posicao){0, 0};
                posicao_inserida = (struct Posicao){0, 0};

                partida._REPRINT = TRUE;
                partida.estado = REPRINT;
                partida._ACAO_ATUAL = TURNO;

                continue;
            }
        }

        while (partida.estado == JOGADOR)
        {
            struct Jogador tmp = turno_atual.oponente;
            turno_atual.oponente = turno_atual.jogador;
            turno_atual.jogador = tmp;

            partida._REPRINT = TRUE;
            partida.estado = REPRINT;
            partida._ACAO_ATUAL = TURNO;
        }
    }

    printf("Fim de jogo\n");

    return 0;
}
