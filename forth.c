#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 100
#define MAX_TOKENS 100
#define MAX_WORD_LENGTH 32

typedef struct Context {
    int stack[MAX_STACK_SIZE];
    int stack_top;
} Context;

Context* create_context() {
    Context *ctx = malloc(sizeof(Context));
    ctx->stack_top = 0;
    return ctx;
}

void push(Context *ctx, int value) {
    if (ctx->stack_top < MAX_STACK_SIZE) {
        ctx->stack[ctx->stack_top++] = value;
    } else {
        printf("Stack overflow\n");
    }
}

int pop(Context *ctx) {
    if (ctx->stack_top > 0) {
        return ctx->stack[--ctx->stack_top];
    } else {
        printf("Stack underflow\n");
        return 0; // Верните 0 или обработайте ошибку
    }
}

bool is_digit(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}

void execute_operation(const char *operation, Context *ctx) {
    int a, b;

    if (strcmp(operation, "+") == 0) {
        b = pop(ctx);
        a = pop(ctx);
        push(ctx, a + b);
    } else if (strcmp(operation, "-") == 0) {
        b = pop(ctx);
        a = pop(ctx);
        push(ctx, a - b);
    } else if (strcmp(operation, "*") == 0) {
        b = pop(ctx);
        a = pop(ctx);
        push(ctx, a * b);
    } else if (strcmp(operation, "/") == 0) {
        b = pop(ctx);
        a = pop(ctx);
        push(ctx, a / b);
    } else if (strcmp(operation, ".") == 0) {
        printf("%d\n", pop(ctx));
    }
}

void parse(const char *tokens[], int token_count, Context *ctx) {
    for (int i = 0; i < token_count; i++) {
        const char *token = tokens[i];

        if (is_digit(token)) {
            push(ctx, atoi(token));
        } else {
            execute_operation(token, ctx);
        }
    }
}

int main() {
    const char *tokens[] = {
        "5", "3", "+", "2", "*", "."
    };

    Context *ctx = create_context();
    parse(tokens, sizeof(tokens) / sizeof(tokens[0]), ctx);
    
    free(ctx);
    int testInteger;
    scanf("%d", &testInteger);  
    return 0;
}
