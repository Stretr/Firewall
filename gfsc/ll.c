#include "ll.h"

#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) calloc(1, sizeof(LinkedList));
    if (ll) {
        ll->length = 0;
        ll->head = node_create(NULL, NULL);
        ll->tail = node_create(NULL, NULL);
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
        ll->mtf = mtf;
    }
    return ll;
}

// Node deletion occurs at ll->head->next
void ll_delete(LinkedList **ll) {
    while ((*ll)->head->next != (*ll)->tail) {
        Node *curr = (*ll)->head->next;
        (*ll)->head->next = curr->next;
        (*ll)->head->next->prev = (*ll)->head;
        node_delete(&curr);
    }
    node_delete(&(*ll)->tail);
    node_delete(&(*ll)->head);
    free(*ll);
    *ll = NULL;
    return;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

// Move To Front only rearranges list order
// There is no memory reallocation at all
// For loop based off of design from lecture
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    for (Node *curr = ll->head->next; curr != ll->tail; curr = curr->next) {
        if (strcmp(curr->oldspeak, oldspeak) == 0) {
            if (ll->mtf == true) {
                curr->next->prev = curr->prev;
                curr->prev->next = curr->next;
                curr->next = ll->head->next;
                curr->prev = ll->head;
                curr->next->prev = curr;
                curr->prev->next = curr;
            }
            return curr;
        }
    }
    return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (ll_lookup(ll, oldspeak) == NULL) {
        Node *neck = node_create(oldspeak, newspeak);
        neck->prev = ll->head;
        neck->next = ll->head->next;
        neck->prev->next = neck;
        neck->next->prev = neck;
        ll->length += 1;
    }
    return;
}

// Newlines are printed first beacause
// of use in banhammer.c
void ll_print(LinkedList *ll) {
    for (Node *curr = ll->head->next; curr != ll->tail; curr = curr->next) {
        printf("\n");
        node_print(curr);
    }
    return;
}