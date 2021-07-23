#include "bv.h"

#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

uint32_t bytes(uint32_t bits) {
    if ((bits % 8) == 0) {
        return bits / 8;
    }
    return bits / 8 + 1;
}

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) calloc(1, sizeof(BitVector));
    if (!bv) {
        return 0;
    }
    bv->vector = (uint8_t *) calloc(bytes(length), sizeof(uint8_t));
    bv->length = length;
    return bv;
}

void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    (*bv)->vector = NULL;
    free(*bv);
    *bv = NULL;
    return;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

void bv_set_bit(BitVector *bv, uint32_t i) {
    bv->vector[i / 8] |= 1 << (i % 8);
    return;
}

void bv_clr_bit(BitVector *bv, uint32_t i) {
    bv->vector[i / 8] &= ~(1 << (i % 8));
    return;
}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    return (bv->vector[i / 8] >> (i % 8)) & 1;
}

void bv_print(BitVector *bv) {
    for (int i = 0; i < bv->length; i++) {
        if (bv_get_bit(bv, i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
    return;
}