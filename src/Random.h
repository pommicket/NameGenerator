double rand01()
{
    return (double)rand() / RAND_MAX;
}

int randrange(int a, int b)
{
    return (int)((b-a)*rand01() + a);
}
