#ifndef STACK_H
#define STACK_H

#define MAX_STACK 100

typedef struct {
    int piece_id;   // id da peça (1 = I, 2 = O, etc.)
    int row;        // linha onde a peça foi colocada (top-left)
    int col;        // coluna onde a peça foi colocada (top-left)
} StackItem;

typedef struct {
    StackItem items[MAX_STACK];
    int top; // índice do topo (-1 = vazio)
} Stack;

void stack_init(Stack *s);
int stack_is_empty(const Stack *s);
int stack_is_full(const Stack *s);
int stack_push(Stack *s, StackItem item);
int stack_pop(Stack *s, StackItem *out);
int stack_peek(const Stack *s, StackItem *out);
int stack_size(const Stack *s);

#endif
