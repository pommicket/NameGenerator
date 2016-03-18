typedef struct
{
    char* s;
    int i;
}
StringIntPair;

typedef struct
{
    int size;
    int index;
    StringIntPair* pairs;
}
StringIntMap;

StringIntPair createPair(char* s, int i)
{
    StringIntPair* sip = malloc(sizeof(StringIntPair));
    sip->s = s;
    sip->i = i;
    return *sip;
}

StringIntMap* newStringIntMap(int size)
{
    StringIntMap* sim = malloc(sizeof(StringIntMap));
    sim->size = size;
    sim->index = 0;
    sim->pairs = malloc(size*sizeof(StringIntPair));
    return sim;
}

void addStringIntMap(StringIntMap* sim, char* s, int i)
{
    sim->pairs[sim->index++] = createPair(s, i);
}

int valueAtMap(StringIntMap* sim, char* s)
{
    int i;
    for (i = 0; i < sim->index; i++)
        if (strEquals(sim->pairs[i].s, s))
            return sim->pairs[i].i;

    return 0;

}

typedef StringIntMap* TrigramList;
