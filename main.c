// Rumpfskript zu Übungsblatt 4, Aufgabe 2
// Anlegen, Traversieren und Auswerten eines Ausdrucksbaums
// Autor: H. Schramm

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char type;                      /* Operatorzeichen oder '0' fuer Zahlenknoten */
    double number;                  /* Zahl fuer Zahlenknoten oder 0.0 */
    struct node *pleft, *pright;    /* Zeiger auf linken und rechten Teilbaum */
} TNode;

TNode *compose_tree(char type, double value, TNode *pleft, TNode *pright);

void ausgabePreorder(TNode *node);

void ausgabePostorder(TNode *node);

void ausgabeInorder(TNode *node);

void ausgabeLevelorder(TNode *node);

float auswerten(TNode *node);

float calculate(double value1, char operator, double value2);


int main() {
    TNode *proot, *left, *right;

    left = compose_tree('0', 3.0, NULL, NULL);
    right = compose_tree('0', 2.0, NULL, NULL);
    proot = compose_tree('*', 0.0, left, right);
    left = compose_tree('0', 8.0, NULL, NULL);
    right = compose_tree('0', 4.0, NULL, NULL);
    right = compose_tree('/', 0.0, left, right);
    proot = compose_tree('+', 0.0, proot, right);

    ausgabePreorder(proot);
    printf("\n");
    ausgabeInorder(proot);
    printf("\n");
    ausgabePostorder(proot);
    printf("\n");
    printf("Auswertung des Baumes ergibt: %.2f\n", auswerten(proot));

    return 0;
}


TNode *compose_tree(char type, double value, TNode *pleft, TNode *pright) {
    TNode *proot;                               /* Zeiger auf neues Element */
    TNode *new = (TNode *) malloc(sizeof(TNode));
    if (new == NULL) return NULL;
    new->type = type;
    new->number = value;
    new->pleft = pleft;
    new->pright = pright;
    proot = new;
    return proot;
}


void ausgabePreorder(TNode *node) {
    if (node != NULL) {
        if (node->type != '0') {
            printf("%c ", node->type);
        } else {
            printf("%.2lf ", node->number);
        }
        ausgabePreorder(node->pleft);
        ausgabePreorder(node->pright);
    }
    return;
}

void ausgabeInorder(TNode *node) {
    if (node != NULL) {
        if (node->type != '0') {
            ausgabeInorder(node->pleft);
            printf("%c ", node->type);
            ausgabeInorder(node->pright);
        } else {
            printf("%.2lf ", node->number);
        }
    }
    return;
}

void ausgabePostorder(TNode *node) {
    if (node != NULL) {
        if (node->type != '0') {
            ausgabePostorder(node->pleft);
            ausgabePostorder(node->pright);
            printf("%c ", node->type);
        } else {
            printf("%.2lf ", node->number);
        }
    }
    return;
}

float auswerten(TNode *node) {
    if (node != NULL) {

        if (node->type != '0') {
            return calculate(auswerten(node->pleft), node->type, auswerten(node->pright));
        } else {
            return node->number;
        }


    } else {
        printf("Invalid tree");
        exit(0);
    }
}

float calculate(double value1, char operator, double value2) {


    switch (operator) {
        case '+':
            return value1 + value2;

        case '-':
            return value1 - value2;

        case '*':
            return value1 * value2;

        case '/':
            return value1 / value2;
        default:
            return 0.0;
    }
}

void ausgabeLevelorder(TNode *node) {
    if (node != NULL) {
        if(node != '0') {
            printf("%c ", node->type);
        }
    }
}

