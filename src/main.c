#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"

static void print_menu(void) {
    printf("\n=== Tetris Stack - Menu ===\n");
    printf("1 - empilhar peça (push)\n");
    printf("2 - desempilhar última peça (pop)\n");
    printf("3 - mostrar tabuleiro\n");
    printf("4 - listar pilha\n");
    printf("0 - sair\n");
    printf("Escolha: ");
}

int main(void) {
    board_init();
    int opt = -1;
    while (1) {
        print_menu();
        if (scanf("%d", &opt) != 1) {
            // limpar entrada
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        if (opt == 0) break;
        if (opt == 1) {
            int pid, col;
            printf("Qual peça? (1=I, 2=O): ");
            if (scanf("%d", &pid) != 1) continue;
            printf("Coluna (0-%d) (col é a posição esquerda da matriz 4x4): ", BOARD_COLS - 1);
            if (scanf("%d", &col) != 1) continue;
            if (place_piece(pid, col)) {
                printf("Peça empilhada com sucesso.\n");
            } else {
                printf("Falha ao empilhar peça (colisão ou espaço insuficiente).\n");
            }
        } else if (opt == 2) {
            if (remove_last_piece()) {
                printf("Última peça removida.\n");
            } else {
                printf("Pilha vazia.\n");
            }
        } else if (opt == 3) {
            board_print();
        } else if (opt == 4) {
            list_stack();
        } else {
            printf("Opção inválida.\n");
        }
    }
    printf("Saindo...\n");
    return 0;
}
