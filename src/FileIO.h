int numLines(char* fname)
{
    FILE* fp = fopen(fname, "r");
    char str[64];
    int n = 0;
    while (fgets(str, 64, fp) != NULL)
        n++;
    fclose(fp);
    return n;

}

