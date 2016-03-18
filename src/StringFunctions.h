
int strEquals(char* a, char* b)
{
    if (strlen(a) != strlen(b))
        return 0;
    int i;
    for (i = 0; i < strlen(a); i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

char* substring(char* x, int start, int end)
{
    char* newX = malloc(end-start+1);
    int i;
    for (i = start; i < end; i++)
        newX[i-start] = x[i];
    newX[end-start] = 0; //Null-terminate
    return newX;
}
