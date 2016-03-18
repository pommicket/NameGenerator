#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "StringFunctions.h"
#include "FileIO.h"
#include "Random.h"
#include "StringIntMap.h"
#include "NameGenerator.h"



TrigramList trigrams;

int main(int argc, char** argv)
{
    struct timeval t;
    int i;
    
    gettimeofday(&t, NULL);
    srand(t.tv_sec * 1000000 + t.tv_usec);

    if (argc < 2)
    {
        fprintf(stderr, "Error: Usage: %s [number of names]\n", argv[0]);
	return 1;
    }
    trigrams = loadTrigrams("trigrams.txt");
    
    for (i = 0; i < atoi(argv[1]); i++)
        printf("%s\n", createName(trigrams));

    return 0;
}
