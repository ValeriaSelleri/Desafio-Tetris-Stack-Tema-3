#include "stack.h"

void stack_init(Stack *s) {
    s->top = -1;
}

int stack_is_empty(const Stack *s) {
    return s->top == -1;
}

int stack_is_full(const Stack *s) {
    return s->top >= MAX_STACK - 1;
}

int stack_push(Stack *s, StackItem item) {
    if (stack_is_full(s)) return 0;
    s->items[++s->top] = item;
    return 1;
}

int stack_pop(Stack *s, StackItem *out) {
    if (stack_is_empty(s)) return 0;
    if (out) *out = s->items[s->top];
    s->top--;
    return 1;
}

int stack_peek(const Stack *s, StackItem *out) {
    if (stack_is_empty(s)) return 0;
    if (out) *out = s->items[s->top];
    return 1;
}

int stack_size(const Stack *s) {
    return s->top + 1;
}
