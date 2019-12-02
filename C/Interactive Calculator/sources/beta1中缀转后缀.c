#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define NOTEST
#define VAR_COUNT 1000
double *var = NULL;
//////////////////////////////////////////////////////////////////////////
char next(void);
char *get_symbol(const char *exp, int length);
bool is_letter(char ch);
bool is_num(char ch);
bool is_symbol(char ch);
int *get_value(const char *exp, int length);
double *hash(const char *name, const double *base, int size);
int *get_var(const char *exp, int length, const double *base, int size);
//////////////////////////////////////////////////////////////////////////
#ifdef NOTEST
int main(int argc, char *argv[])
{
    int i = 0, length = 0;
    char ch = 0;
    char *str = (char *)calloc(1, sizeof(char));
    int *value = NULL;
    int *var_list = NULL;
    char *symbol = NULL;
    var = (double *)calloc(VAR_COUNT, sizeof(double));

    for (i = 0; (ch = getchar()) != '\n'; /*void*/)
    {
        str[i] = ch;
        i++;
        str = realloc(str, (i + 1) * sizeof(char));
        if (str == NULL)
            return 0;
        str[i] = '\0';
    }
    length = i;

    value = get_value(str, length);//输出数值表
    for (i = 0; i < value[1]; i++)
        printf("%lf ", ((double *)value[0])[i]);
    printf("\n");

    symbol = get_symbol(str, length);//输出符号表
    puts(symbol);

    var_list = get_var(str, length, var, VAR_COUNT);//输出变量表
    for (i = 0; i < var_list[1]; i++)
        printf("%p\n", ((double **)var_list[0])[i]);
    return 0;
}
#endif
//////////////////////////////////////////////////////////////////////////
#ifdef TEST
int main(int argc, char *argv[])
{

    return 0;
}
#endif
//////////////////////////////////////////////////////////////////////////
char next(void)
{
    char ch = 0;
    while ((ch = getchar()) == ' ')
        ;
    ungetc(ch, stdin);
    return ch;
}
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
bool is_letter(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_'))
        return true;
    else
        return false;
}
//////////////////////////////////////////////////////////////////////////
bool is_num(char ch)
{
    if ((ch >= '0' && ch <= '9') || (ch == '.'))
        return true;
    else
        return false;
}
//////////////////////////////////////////////////////////////////////////
bool is_symbol(char ch)
{
    if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '^'))
        return true;
    else
        return false;
}
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
double *hash(const char *name, const double *base, int size)
{
    int i = 0;
    long long int tmp = 0;
    char p1 = 0, p2 = 0, p3 = 0, p4 = 0;
    for (i = 0; i < strlen(name); i++)
    {
        p1 = name[i] & 0xAA;
        p2 = name[i] & 0x55;
        p3 = name[i] & 0xF0;
        p4 = name[i] & 0x0F;
        tmp += (p1 * p2) + (p3 * p4);
    }
    return (base + ((tmp * 23333) % size));
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