#include "bf.h"
#include "bv.h"
#include "hash.h"
#include "parser.h"

#include <getopt.h>
#include <math.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "h:f:m"
#define WORD    "([A-Za-z0-9_'-]*)"

int main(int argc, char **argv) {
    uint32_t hsize = 10000;
    uint32_t fsize = pow(2, 20);
    uint32_t opt;
    bool mtf = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': hsize = atoi(optarg); break;
        case 'f': fsize = atoi(optarg); break;
        case 'm': mtf = true; break;
        }
    }
    // Ensures sizes are valid, then initialises variables
    if (hsize < 1 || fsize < 1) {
        printf("Malformed input.\n");
        return 0;
    }
    BloomFilter *bf = bf_create(fsize);
    HashTable *ht = ht_create(hsize, mtf);
    char oldspeak[1024];
    char newspeak[1024];
    // Initializes the filter and table
    FILE *bsfile = fopen("badspeak.txt", "r");
    while (fscanf(bsfile, "%s\n", oldspeak) != EOF) {
        bf_insert(bf, oldspeak);
        ht_insert(ht, oldspeak, NULL);
    }
    fclose(bsfile);
    FILE *nsfile = fopen("newspeak.txt", "r");
    while (fscanf(nsfile, "%s %s\n", oldspeak, newspeak) != EOF) {
        bf_insert(bf, oldspeak);
        ht_insert(ht, oldspeak, newspeak);
    }
    fclose(nsfile);
    // After successfull initializations
    // regex is booted and ready for input
    // Based off of design from Lab Document
    regex_t rt;
    char *word = NULL;
    LinkedList *speak[2] = { ll_create(mtf), ll_create(mtf) };
    if (regcomp(&rt, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }
    while ((word = next_word(stdin, &rt)) != NULL) {
        if (bf_probe(bf, word) == true) {
            // Loc separates badspeak from oldspeak
            if (!(ht_lookup(ht, word) == NULL)) {
                uint32_t loc = 0;
                if (!(ht_lookup(ht, word)->newspeak == NULL)) {
                    loc += 1;
                }
                ll_insert(speak[loc], word, ht_lookup(ht, word)->newspeak);
            }
        }
    }
    // Prints worse outcome first if
    // any fatal error is found
    if (ll_length(speak[0]) > 0) {
        printf("Dear Comrade,\n\n");
        printf("You have chosen to use degenerate words that may cause hurt\n");
        printf("feelings or cause your comrades to think unpleasant thoughts.\n");
        printf("This is doubleplus bad. To correct your wrongthink and\n");
        printf("preserve community consensus we will be sending you to joycamp\n");
        printf("administered by Medellin’s Miniluv. Beware of the hippos.\n");
        printf("\nYour errors:\n");
        ll_print(speak[0]);
        // Will additionally print conversions
        // for replaced oldspeak if applicable
        if (ll_length(speak[1]) > 0) {
            printf("\n\nThink of these words on your vacation!\n");
            ll_print(speak[1]);
        }
    } else if (ll_length(speak[1]) > 0) {
        // Else is used to avoid interference
        printf("Dear Comrade,\n\n");
        printf("Submitting your text helps to preserve feelings and prevent\n");
        printf("badthink. Some of the words that you used are not goodspeak.\n");
        printf("The list shows how to turn the oldspeak words into newspeak.\n");
        ll_print(speak[1]);
    }
    clear_words();
    regfree(&rt);
    ll_delete(&speak[1]);
    ll_delete(&speak[0]);
    ht_delete(&ht);
    bf_delete(&bf);
    printf("\n");
    return 0;
}