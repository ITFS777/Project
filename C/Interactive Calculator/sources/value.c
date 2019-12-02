//////////////////////////////////////////////////////////////////////////
int *get_value(const char *exp, int length)
{
    int i = 0, j = 0, count = 0;
    int *output = (int *)calloc(2, sizeof(int));
    char *str = (char *)calloc(length, sizeof(char));
    strncpy(str, exp, length);
    double value_list[128] = {0.0};
    char tmp[128] = {0};
    for (i = 0, count = 0; i < length; i++)
    {
        if (is_num(str[i]))
        {
            memset(tmp, 0, 128 * sizeof(char));
            j = 0;
            do
            {
                tmp[j] = str[i];
                j++;
                i++;
            } while (is_num(str[i]));
            value_list[count] = atof(tmp);
            count++;
        }
    }
    double *value = (double *)calloc(count, sizeof(double));
    for (i = 0; i < count; i++)
        value[i] = value_list[i];

    output[0] = (int)value;
    output[1] = count;
    return output;
}
//////////////////////////////////////////////////////////////////////////