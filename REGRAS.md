## Escolha da peça
* Os índices precisam ser válidos (0 <= i < total_de_colunas)
* Os índices não podem apontar para um espaço vazio ((0, 0) != ' ')
* Os índices não podem apontar para uma peça do oponente ((0, 0) != peca_do_oponente)

## Movimentação da peça
* Os índices precisam ser válidos (0 <= i < total_de_colunas)
* O índice precisa estar vazio ((0, 0) == ' ')
* O índice só pode apontar para uma peça do oponente se, e somente se, o espaço após o mesmo estiver livre e o espaço for válido. Ex.: Origem (1,4)
    - Caso 1:
        * Destino (2, 5) -> peca_do_oponente
        * (3, 6) está livre e existe ? captura : não mover a peça
    - Caso 2:
        * Destino (2, 3) -> peca_do_oponente
        * (3, 2) está livre e existe ? captura : não mover a peça

## Sentido da captura

### Captura em O

Origem(6, 5)
* Caso 1:
    - Destino(5, 6) -> peca_O
    - Captura válida -> Destino(4, 7)

* Caso 2:
    - Destino(5, 4) -> peca_0
    - Captura válida -> Destino(4, 3)

### Captura em X

Origem(3, 4)
* Caso 1:
    - Destino(4, 3) -> peca_X
    - Captura válida -> Destino(5, 2)
* Caso 2:
    - Destino(4, 5)
    - Captura válida -> Destino(5, 6)
