//////////////////////////////////////////////////////////////////////////
char *get_symbol(const char *exp, int length)
{
    int i = 0, count = 0;
    char *str = (char *)calloc(length, sizeof(char));
    strncpy(str, exp, length);
    char symbol_list[128] = {0};
    for (i = 0, count = 0; i < length; i++)
    {
        if (is_symbol(str[i]))
        {
            symbol_list[count] = str[i];
            count++;
        }
    }
    char *symbol = (char *)calloc(count + 1, sizeof(char));
    for (i = 0; i < count; i++)
        symbol[i] = symbol_list[i];
    symbol[count] = '\0';
    return symbol;
}
//////////////////////////////////////////////////////////////////////////