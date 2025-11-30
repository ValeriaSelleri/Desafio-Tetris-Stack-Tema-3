#include <stdio.h>
#include <string.h>
#include "tetris.h"

static int board[BOARD_ROWS][BOARD_COLS];
static Stack stack;
static int pieces_defined = 0;

/*
  Implementamos duas peças (4x4 matrices simplificadas):
  piece 1: I (vertical 4)
  piece 2: O (2x2)
  As peças aqui são representadas por arrays de 4x4 para facilitar o posicionamento.
*/

static const int PIECE_SIZE = 4;
static int pieces[3][4][4]; // index 1..2 used

void init_example_pieces(void) {
    if (pieces_defined) return;
    memset(pieces, 0, sizeof(pieces));
    // Piece 1: I (vertical)
    pieces[1][0][1] = 1;
    pieces[1][1][1] = 1;
    pieces[1][2][1] = 1;
    pieces[1][3][1] = 1;
    // Piece 2: O (2x2)
    pieces[2][1][1] = 1;
    pieces[2][1][2] = 1;
    pieces[2][2][1] = 1;
    pieces[2][2][2] = 1;

    pieces_defined = 1;
}

void board_init(void) {
    memset(board, 0, sizeof(board));
    stack_init(&stack);
    init_example_pieces();
}

void board_print(void) {
    printf("\nTabuleiro (linha 0 = topo):\n");
    for (int r = 0; r < BOARD_ROWS; r++) {
        printf("|");
        for (int c = 0; c < BOARD_COLS; c++) {
            printf("%c", board[r][c] ? '#' : ' ');
        }
        printf("|\n");
    }
}

static int can_place_at(int top_row, int left_col, int piece_id) {
    if (piece_id < 1 || piece_id > 2) return 0;
    for (int r = 0; r < PIECE_SIZE; r++) {
        for (int c = 0; c < PIECE_SIZE; c++) {
            if (pieces[piece_id][r][c]) {
                int br = top_row + r;
                int bc = left_col + c;
                if (br < 0 || br >= BOARD_ROWS || bc < 0 || bc >= BOARD_COLS) return 0;
                if (board[br][bc]) return 0;
            }
        }
    }
    return 1;
}

static void apply_piece_at(int top_row, int left_col, int piece_id, int fill) {
    for (int r = 0; r < PIECE_SIZE; r++) {
        for (int c = 0; c < PIECE_SIZE; c++) {
            if (pieces[piece_id][r][c]) {
                board[top_row + r][left_col + c] = fill ? piece_id : 0;
            }
        }
    }
}

// drop: tenta encaixar a peça na coluna indicada (left col)
// strategy: testar linhas do topo até o máximo possível para "caer" até a posição mais baixa possível.
int place_piece(int piece_id, int col) {
    init_example_pieces();
    if (piece_id < 1 || piece_id > 2) return 0;
    if (col < 0 || col >= BOARD_COLS) return 0;

    // procurar a maior linha top_row onde a peça ainda cabe (simulate falling)
    int best_row = -1;
    for (int top = 0; top <= BOARD_ROWS - PIECE_SIZE; top++) {
        if (!can_place_at(top, col, piece_id)) {
            // se aqui não cabe, peça colidiu; a posição válida é top-1
            break;
        }
        best_row = top;
    }
    if (best_row == -1) return 0; // não cabe nem no topo

    // verificar se na posição mais baixa cabe (queremos a posição mais baixa disponível)
    // começamos do topo e andamos até o último válido, que será best_row.
    // aplicamos no best_row
    apply_piece_at(best_row, col, piece_id, 1);

    // salvar na stack
    StackItem item;
    item.piece_id = piece_id;
    item.row = best_row;
    item.col = col;
    if (!stack_push(&stack, item)) {
        // sem espaço na stack: desfaz e retorna erro
        apply_piece_at(best_row, col, piece_id, 0);
        return 0;
    }
    return 1;
}

int remove_last_piece(void) {
    StackItem it;
    if (!stack_pop(&stack, &it)) return 0;
    apply_piece_at(it.row, it.col, it.piece_id, 0);
    return 1;
}

void list_stack(void) {
    printf("\nPilha (topo à direita): size=%d\n", stack_size(&stack));
    if (stack_is_empty(&stack)) {
        printf(" <vazia>\n");
        return;
    }
    for (int i = 0; i <= stack.top; i++) {
        StackItem it = stack.items[i];
        printf(" [%d] peça %d em row=%d col=%d\n", i, it.piece_id, it.row, it.col);
    }
}
