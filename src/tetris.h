#ifndef TETRIS_H
#define TETRIS_H

#include "stack.h"

#define BOARD_ROWS 20
#define BOARD_COLS 10

void board_init(void);
void board_print(void);
int place_piece(int piece_id, int col); // tenta colocar peça na coluna; retorna 1 sucesso, 0 falha
int remove_last_piece(void); // desempilha e remove do board, retorna 1 sucesso, 0 falha
void list_stack(void);
void init_example_pieces(void);

#endif
