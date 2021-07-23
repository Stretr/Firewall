#include "node.h"

#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Design referenced from Piazza
#define strdup(s) strcpy(malloc(strlen(s) + 1), s)

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    if (n) {
        n->next = NULL;
        n->prev = NULL;
        if (!(oldspeak == NULL)) {
            n->oldspeak = strdup(oldspeak);
        }
        if (!(newspeak == NULL)) {
            n->newspeak = strdup(newspeak);
        }
    }
    return n;
}

void node_delete(Node **n) {
    if ((*n)->newspeak != NULL) {
        free((*n)->newspeak);
        (*n)->newspeak = NULL;
    }
    if ((*n)->oldspeak != NULL) {
        free((*n)->oldspeak);
        (*n)->oldspeak = NULL;
    }
    free(*n);
    *n = NULL;
    return;
}

// Newline avoided in print function
// due to use in banhammer.c
void node_print(Node *n) {
    printf("%s", n->oldspeak);
    if (!(n->newspeak == NULL)) {
        printf(" -> %s", n->newspeak);
    }
    return;
}