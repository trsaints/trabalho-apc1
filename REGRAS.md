# Escolha da peça
* Os índices precisam ser válidos (0 <= i < total_de_colunas)
* Os índices não podem apontar para um espaço vazio ((0, 0) != ' ')
* Os índices não podem apontar para uma peça do oponente ((0, 0) != peca_do_oponente)

# Movimentação da peça
* Os índices precisam ser válidos (0 <= i < total_de_colunas)
* O índice precisa estar vazio ((0, 0) == ' ')
* O índice não pode apontar para outra peça do jogador ((0, 0) == ' ')
* O índice só pode apontar para uma peça do oponente se, e somente se, o espaço após o mesmo estiver livre e o espaço for válido. Ex.: Origem (1,4)
    - Caso 1:
        * Destino (2, 5) -> peca_do_oponente
        * (3, 6) está livre e existe ? captura : não mover a peça
    - Caso 2:
        * Destino (2, 3) -> peca_do_oponente
        * (3, 2) está livre e existe ? captura : não mover a peça
