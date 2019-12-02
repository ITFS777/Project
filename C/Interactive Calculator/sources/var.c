//////////////////////////////////////////////////////////////////////////
double *hash(const char *name, const double *base, int size, const char *hash_seed)
{
    int i = 0;
    long long int tmp = 0, p3 = 0;
    char p1 = 0, p2 = 0;
    for (i = 0; i < strlen(name); i++)
    {
        p1 = (name[i] & 0xA5) | (hash_seed[i % strlen(hash_seed)] & 0x5A);
        p2 = (name[i] & 0x5A) | (hash_seed[i % strlen(hash_seed)] & 0xA5);
        tmp += ((p1 & 0xF0) | (p2 & 0x0F)) + ((p1 & 0x0F) | (p2 & 0xF0));
        p3 += hash_seed[i % strlen(hash_seed)];
    }
    return (base + (tmp*p3 % size));
}
//////////////////////////////////////////////////////////////////////////
int *get_var(const char *exp, int length, const double *base, int size)
{
    int i = 0, j = 0, count = 0;
    int *output = (int *)calloc(2, sizeof(int));
    char *str = (char *)calloc(length, sizeof(char));
    strncpy(str, exp, length);
    double *var_list[128] = {0};
    char tmp[128] = {0};
    for (i = 0, count = 0; i < length; i++)
    {
        if (is_letter(str[i]))
        {
            memset(tmp, 0, 128 * sizeof(char));
            j = 0;
            while (is_letter(str[i]) || is_num(str[i]))
            {
                tmp[j] = str[i];
                j++;
                i++;
            }
            var_list[count] = hash(tmp, base, size);
            count++;
        }
    }
    double **var = (double **)calloc(count, sizeof(double *));
    for (i = 0; i < count; i++)
        var[i] = var_list[i];
    output[0] = (int)var;
    output[1] = count;
    return output;
}
//////////////////////////////////////////////////////////////////////////