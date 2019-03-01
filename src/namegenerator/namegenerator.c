/*
Copyright (C) 2019 Leonardo Tenenbaum

This file is part of NameGenerator.

NameGenerator is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

NameGenerator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with NameGenerator.  If not, see <https://www.gnu.org/licenses/>.

*/
#include "namegenerator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <limits.h>

#if INT_MAX >= 2147483647L /* Is an int big enough to store trigram frequencies? */
typedef int frequency_t;
#define FREQUENCY_MAX INT_MAX
#else
typedef long frequency_t;
#define FREQUENCY_MAX LONG_MAX
#endif

#if FREQUENCY_MAX != 2147483647L
#error "Can't find a 32-bit integer type."
#endif

static frequency_t trigram_frequencies[27][27][27];
static frequency_t frequency_totals[27][27]; /* [i][j] = sum(trigram_frequencies[i][j][k]) */
static frequency_t frequency_total_start; /* = sum(trigram_frequencies[SPACE_INDEX][SPACE_INDEX][i]) */

static const size_t SPACE_INDEX = 26;

static frequency_t rand_frequency() {
#if RAND_MAX == 2147483647L
    return rand();
#else
#if RAND_MAX == 32767L
    return rand() + (rand() << 15) + ((rand() & 1) << 30);
#else 
#error Unable to determine RAND_MAX.
#endif
#endif
}

static frequency_t rand_frequency_up_to(frequency_t f) { /* This random function definitely isn't perfect */
    return f * (double)rand_frequency()/FREQUENCY_MAX;
}

static size_t char_to_index(char c) { /* Converts a character to an index of trigram_frequencies */
    assert(c == ' ' || (c >= 'a' && c <= 'z'));
    return c == ' ' ? SPACE_INDEX : (c - 'a');
}

static char index_to_char(size_t i) { /* Converts an index of trigram_frequencies to a charactre */
    assert(i >= 0 && i < 27);
    return i == SPACE_INDEX ? ' ' : (i + 'a');
}

void namegenerator_load(const char* trigrams_filename) {
    FILE* fp = fopen(trigrams_filename, "r");
    char buffer[16];
    while (fgets(buffer, 16, fp)) {
        size_t i1 = char_to_index(buffer[0]);
        size_t i2 = char_to_index(buffer[1]);
        size_t i3 = char_to_index(buffer[2]);
        frequency_t freq = atoi(buffer + 4);
        trigram_frequencies[i1][i2][i3] = freq;
        if (i1 == SPACE_INDEX) {
            frequency_total_start += freq;
        }
        frequency_totals[i1][i2] += freq;
    }
    fclose(fp);
}

static void generate_first_two(char* name) {
    frequency_t chosen = rand_frequency_up_to(frequency_total_start);
    size_t i, j;
    for (i = 0; i < 27; i++) {
        for (j = 0; j < 27; j++) {
            chosen -= trigram_frequencies[SPACE_INDEX][i][j];
            if (chosen < 0) {
                name[0] = index_to_char(i);
                name[1] = index_to_char(j);
                return;
            }
        }
    }
    assert(!"Something went wrong..."); 
}

static char generate_next(char second_last, char last) {
    size_t i1 = char_to_index(second_last);
    size_t i2 = char_to_index(last);
    frequency_t chosen = rand_frequency_up_to(frequency_totals[i1][i2]);
    size_t i;
    for (i = 0; i < 27; i++) {
        chosen -= trigram_frequencies[i1][i2][i];
        if (chosen <= 0) {
            return index_to_char(i);
        }
    }
    assert(!"Something went wrong...");
    return 0;
}

char* namegenerator_generate_name(void) {
    char* name = malloc(64);
    generate_first_two(name);
    size_t i = 2;
    while (1) {
        char next = generate_next(name[i-1], name[i-2]);
        if (next == ' ') break;
        name[i] = next;
        i++;
        if (i >= 63) {
            /* Try generating name again */
            free(name);
            return namegenerator_generate_name();
        }
    }
    name[i] = 0; /* Null terminate */
    name[0] = toupper(name[0]); /* Capitalize */
    return name;
}

char* namegenerator_generate_name_with_length(int min_len, int max_len) {
    char* name = NULL;
    size_t len;
    do {
        if (name) free(name);
        name = namegenerator_generate_name();
        len = strlen(name);
    } while (len < min_len || len >= max_len);
    return name;
}