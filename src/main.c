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
    int number;
    
    printf("Number of names: ");
    scanf("%d", &number);
    
    gettimeofday(&t, NULL);
    srand(t.tv_sec * 1000000 + t.tv_usec);

    trigrams = loadTrigrams("trigrams.txt");
    
    for (i = 0; i < number; i++)
        printf("%s\n", createName(trigrams));

    return 0;
}
