#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "NameGenerator.h"

int main(int argc, char** argv)
{
    struct timeval t;

    gettimeofday(&t, NULL);
    srand(t.tv_sec * 1000000 + t.tv_usec);

    printf("Loading... ");
    initialize_namegenerator();
    printf("done.\n");
    printf("How many names would you like to generate? ");

    int i, N;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
        printf("%s\n", generate_name_with_length(5, 64));

    return 0;
}
