#include  <stdio.h>
#include  <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#define MAX_NAME_LENGTH 64 // Maximum possible length of a name

#include "NameGenerator.h"

/*
trigrams[char_index('f')][char_index('o')][char_index('o')] = frequency of "foo" trigram.
*/
int trigrams[27][27][27];

int char_index(char c)
{
    // Returns 0 for space, 1 for a, 2 for b, etc.
    assert(c == ' ' || (c >= 'a' && c <= 'z'));
    if (c == ' ')
        return 0;
    return c - 'a' + 1;
}

char index_char(int i)
{
    // Returns ' ' for 0, 'a' for 1, 'b' for 2, etc.
    assert(i >= 0 && i < 27);
    if (i == 0)
        return ' ';
    return i - 1 + 'a';
}

void initialize_namegenerator()
{
    // Load trigrams
    FILE* fp = fopen("trigrams.txt", "r");
    if (!fp)
    {
        fprintf(stderr, "Error: trigrams.txt not found.\n");
    }

    // Extract frequencies into trigrams array.
    char* buffer = malloc(16);
    char c1,c2,c3;
    int frequency;
    while (fgets(buffer, 16, fp))
    {
        c1 = buffer[0];
        c2 = buffer[1];
        c3 = buffer[2];
        sscanf(buffer+4, "%d", &frequency);
        trigrams[char_index(c1)][char_index(c2)][char_index(c3)] = frequency;
    }
}

double rand01()
{
    return (double)rand()/RAND_MAX;
}

int randrange(int a, int b)
{
    return a + (b-a) * rand01();
}

char* start_name()
{
    // Returns string containing 2 characters.
    // These two characters come from a trigram of the form ' ab'.
    int i, j, total = 0;
    // Get total frequency
    for (i = 0; i < 27; i++)
    {
        for (j = 0; j < 27; j++)
        {
            total += trigrams[0 /* space */][i][j];
        }
    }

    int selected = randrange(0, total);
    total = 0; // Now, this variable will start counting up frequencies, and once it passes selected, it will have arrived at the correct trigram.
    int brk = 0;
    for (i = 0; i < 27; i++)
    {
        for (j = 0; j < 27; j++)
        {
            total += trigrams[0][i][j];
            if (total > selected)
            {
                brk = 1;
                break;
            }
        }
        if (brk) break;
    }
    // Create name from first two characters.
    char* name = malloc(64);
    name[0] = index_char(i);
    name[1] = index_char(j);
    name[2] = 0;
    return name;
}

int add_char(char* name)
{
    // Add another character to the name.
    // Returns 0 if the name is done, 1 if it is not, -1 if the maximum length has been passed.
    int L = strlen(name);
    if (L >= MAX_NAME_LENGTH) return -1;
    assert(L >= 2);
    char c1 = name[L-2], c2 = name[L-1];
    int ci1 = char_index(c1), ci2 = char_index(c2);

    // Find total frequency.
    int i, total = 0;
    for (i = 0; i < 27; i++)
    {
        total += trigrams[ci1][ci2][i];
    }

    int selected = randrange(0, total);
    total = 0; // Now, this variable will start counting up frequencies, and once it passes selected, it will have arrived at the correct trigram.
    for (i = 0; i < 27; i++)
    {
        total += trigrams[ci1][ci2][i];
        if (total > selected)
            break;
    }

    if (i == 0) // Space
    {
        return 0;
    }
    name[L] = index_char(i);
    name[L+1] = 0;
    return 1;
}

char* generate_name()
{
    char* name = start_name();
    int ret;
    while ((ret = add_char(name)) == 1);
    if (ret == -1) return generate_name();
    name[0] = toupper(name[0]);
    return name;
}

char* generate_name_with_length(int min_length, int max_length)
{
    // Generates a name with length in the interval [min_length, max_length]
    char* name = generate_name();
    if (strlen(name) < min_length || strlen(name) > max_length)
        return generate_name_with_length(min_length, max_length);

    return name;
}
