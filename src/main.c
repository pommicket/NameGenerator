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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "namegenerator/namegenerator.h"

int main(int argc, char** argv) {
    srand(time(NULL));
    namegenerator_load("trigrams.txt");
    long N;
    if (argc <= 1) {
        printf("How many names would you like to generate? ");
        fflush(stdout);
        char s[256];
        scanf("%s", s);
        if (!sscanf(s, "%ld", &N)) { /* Was having problems with non-numerical inputs with just scanf. */
            return EXIT_FAILURE;
        }
    } else {
        N = atol(argv[1]);
    }
    long i;
    for (i = 0; i < N; i++) {
        printf("%s\n", namegenerator_generate_name_with_length(5, 16));
    }
    return EXIT_SUCCESS;
}
