#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TAM 200

int converterExpressao(char*);
int estaVazia();
int estaCheia();
char peek();
char pop();
void push(char);
int checarOperando(char);
int checarPrecedencia(char);

char pilha[TAM];
int topo = -1;

int main(){
    puts("CONVERSOR DE EXPRESSAO INFIXA PARA POSFIXA");
    char expression[TAM];
    puts("Digite sua expressão:");
    fgets(expression, 20, stdin);
    converterExpressao(expression); 
    return 0; 
}

int converterExpressao(char* expr) { 
    int i, j;

    for (i = 0, j = -1; expr[i]; ++i) { 
        if (checarOperando(expr[i])){
            expr[++j] = expr[i];
        } else if (expr[i] == '(') {
            push(expr[i]);
        } else if (expr[i]==')') {
            if(expr[i]==')'){  
                while (!estaVazia() && peek() != '(') {
                    expr[++j] = pop();
                }     
                pop();
            }
        } else { 
            while (!estaVazia() && checarPrecedencia(expr[i]) <= checarPrecedencia(peek())) {
                expr[++j] = pop(); 
            }
            push(expr[i]); 
        } 
    } 
    while (!estaVazia()) {
        expr[++j] = pop();
    } 
    expr[++j] = '\0'; 
    printf( "%s", expr); 
} 

int estaVazia(){
    return topo == -1;
}
int estaCheia(){
    return topo == TAM - 1;
}

char peek(){
    return pilha[topo];
}

char pop(){
    if(estaVazia()){
        return INT_MIN;
    }
    char x = pilha[topo];
    topo--;
    return(x);
}

void push(char oper){
    if(estaCheia()){
        printf("Pilha cheia.");
    } else {
        topo++;
        pilha[topo] = oper;
    }
}

int checarOperando(char x) {
    return (x >= '0' && x <= '9');
} 

int checarPrecedencia(char x) {
    switch (x) { 
    case '+': 
    case '-': 
        return 1; 
    case '*': 
    case '/': 
        return 2; 

    case '^': 
        return 3; 
    } 
    return -1; 
} 
