typedef struct CharPair
{
    char c1;
    char c2;
} CharPair;

StringIntMap* loadTrigrams(char* filename)
{
    FILE* fp = fopen(filename, "r");
    char ln[32];
    char* line;
    StringIntMap* trigrams = newStringIntMap(numLines(filename));
    while (fgets(ln,32,fp) != NULL)
    {
        line = strtok(ln, "\n");
        addStringIntMap(trigrams, substring(line, 0, 3), atoi(substring(line, 4, strlen(line))));
    }
    return trigrams;
}

char nextChar(StringIntMap* trigrams, char* name, int index)
{
    int chosenTrigram;
    int count, sum;
    count = 0;
    sum = 0;
    int i;
    for (i = 0; i < trigrams->index; i++)
        if (trigrams->pairs[i].s[0] == name[index-2] && trigrams->pairs[i].s[1] == name[index-1])
            sum += trigrams->pairs[i].i;

    chosenTrigram = randrange(0, sum);

    for (i = 0; i < trigrams->index; i++)
    {
        if (trigrams->pairs[i].s[0] == name[index-2] && trigrams->pairs[i].s[1] == name[index-1])
        {
            count += trigrams->pairs[i].i;
            if (chosenTrigram < count)
                return trigrams->pairs[i].s[2];

        }
    }

    return 'X';
}

CharPair first2chars(StringIntMap* trigrams)
{
    CharPair cp;
    int chosenTrigram;
    int count, sum;
    count = 0;
    sum = 0;
    int i;
    for (i = 0; i < trigrams->index; i++)
        if (trigrams->pairs[i].s[0] == ' ')
            sum += trigrams->pairs[i].i;

    chosenTrigram = randrange(0, sum);

    for (i = 0; i < trigrams->index; i++)
    {
        if (trigrams->pairs[i].s[0] == ' ')
        {
            count += trigrams->pairs[i].i;
            if (chosenTrigram < count)
            {
                cp.c1 = trigrams->pairs[i].s[1];
                cp.c2 = trigrams->pairs[i].s[2];
                return cp;
            }
        }
    }
    return cp;
}

char* createName(StringIntMap* trigrams)
{
    char c;
    char* name = malloc(256);
    int index = 1;
    do
    {
        CharPair cp = first2chars(trigrams);
        name[0] = cp.c1;
        name[1] = cp.c2;
    }
    while (name[0] == ' ' || name[1] == ' ');
    while ((c=nextChar(trigrams, name, ++index)) != ' ')
    {
        if (c == ' ')
            continue;
        if (index >= 254)
            break;
        name[index] = c;
    }
    name[0] = toupper(name[0]);
    name[index] = 0;
    return name;
}
char* createNameWithLength(StringIntMap* trigrams, int minLength)
{
    char* name;
    while (strlen(name = createName(trigrams)) < minLength);
    return name;
}
