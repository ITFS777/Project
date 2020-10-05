#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <windows.h>
#define NOTEST
#define MAX_VALUE_COUNT 1000
#define MAX_VAR_NAME_LENGTH 128
#define MAX_DIG_LENGTH 128
#define MAX_SYMBOL_COUNT 128
#define HASH_SEED "Aryan.ITFS@Gmail.com"
//////////////////////////////////////////////////////////////////////////
bool is_letter(char ch);
bool is_num(char ch);
bool is_symbol(char ch);
double *hash(const char *name, const double *base, int size, const char *hash_seed);
double com(double **value_list, int value_count, char *symbol_list, int symbol_count);
//////////////////////////////////////////////////////////////////////////
#ifdef NOTEST
int main(int argc, char *argv[])
{
    /*-----------------------------------声明变量-----------------------------------*/
    int i = 0, j = 0, length = 0;
    char ch = 0;
    //表达式值相关声明
    int value_count = 0;
    int digit_count = 0;
    double result = 0.0;
    double *var = NULL;
    double digit_list[MAX_VALUE_COUNT] = {0};
    double *value_list[MAX_VALUE_COUNT] = {0};
    char digit_string[MAX_DIG_LENGTH] = {0};
    char var_name[MAX_VAR_NAME_LENGTH] = {0};
    //表达式符号相关声明
    int symbol_count = 0;
    char symbol_list[MAX_SYMBOL_COUNT] = {0};
    //定义变量哈希表
    var = (double *)calloc(MAX_VALUE_COUNT, sizeof(double));
    while (1)
    {
        /*----------------------------------初始化变量----------------------------------*/
        i = 0;
        j = 0;
        length = 0;
        ch = 0;
        value_count = 0;
        digit_count = 0;
        symbol_count = 0;
        result = 0;
        memset(digit_list, 0, MAX_VALUE_COUNT * sizeof(double));
        memset(value_list, 0, MAX_VALUE_COUNT * sizeof(double *));
        memset(digit_string, 0, MAX_DIG_LENGTH * sizeof(char));
        memset(var_name, 0, MAX_VAR_NAME_LENGTH * sizeof(char));
        memset(symbol_list, 0, MAX_SYMBOL_COUNT * sizeof(char));
        /*----------------------------------读取表达式----------------------------------*/
        char *exp = (char *)calloc(1, sizeof(char));
        for (i = 0; (ch = getchar()) != '\n'; /*void*/)
        {
            exp[i] = ch;
            ++i;
            exp = realloc(exp, (i + 1) * sizeof(char));
            if (exp == NULL)
                return 0;
            exp[i] = '\0';
        }
        length = i; //记录长度
        if(!strncmp(exp,"clear",5))
        {
            system("cls");
            continue;
        }
        /*----------------------------------处理表达式----------------------------------*/
        for (i = 0, value_count = 0, symbol_count = 0, digit_count = 0; i < length; ++i)
        {
            if (is_letter(exp[i])) //检测到变量
            {
                memset(var_name, 0, MAX_VAR_NAME_LENGTH * sizeof(char)); //初始化
                j = 0;
                while (is_letter(exp[i]) || is_num(exp[i]))
                {
                    var_name[j] = exp[i];
                    ++j;
                    ++i;
                }
                value_list[value_count] = hash(var_name, var, MAX_SYMBOL_COUNT, HASH_SEED); //将变量名映射到哈希地址
                ++value_count;
                --i;
            }
            else if (is_symbol(exp[i])) //检测到符号
            {
                symbol_list[symbol_count] = exp[i];
                ++symbol_count;
            }
            else if (is_num(exp[i])) //检测到数值
            {
                memset(digit_string, 0, MAX_DIG_LENGTH * sizeof(char)); //初始化
                j = 0;
                while (is_num(exp[i])) //将数值保存为字符串
                {
                    digit_string[j] = exp[i];
                    ++j;
                    ++i;
                }
                digit_list[digit_count] = atof(digit_string);       //转化为字符
                value_list[value_count] = &digit_list[digit_count]; //储存在值序列中
                ++digit_count;
                ++value_count;
                --i;
            }
        }
        free(exp);\
        /*----------------------------------计算表达式----------------------------------*/
        if (value_count == 0 && symbol_count == 0)
        {
            puts("Input error");
            continue;
        }
        if (symbol_list[0] == '=') //赋值表达式
        {
            *value_list[0] = com(value_list + 1, value_count - 1, symbol_list + 1, symbol_count - 1);
            *hash("_", var, MAX_VALUE_COUNT, HASH_SEED) = *value_list[0];
        }
        else //运算表达式
        {
            result = com(value_list, value_count, symbol_list, symbol_count);
            *hash("_", var, MAX_VALUE_COUNT, HASH_SEED) = result;
            printf("%lf\n", result); //输出运算结果
        }
        /*-----------------------------------计算结束----------------------------------*/
    }
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
    if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '^') || (ch == '=') || (ch == '(') || (ch == ')'))
        return true;
    else
        return false;
}
//////////////////////////////////////////////////////////////////////////
double *hash(const char *name, const double *base, int size, const char *hash_seed)
{
    long long int tmp = 0, p3 = 0;
    char p1 = 0, p2 = 0;
    for (int i = 0; i < strlen(name); ++i)
    {
        p1 = (name[i] & 0xA5) | (hash_seed[i % strlen(hash_seed)] & 0x5A);
        p2 = (name[i] & 0x5A) | (hash_seed[i % strlen(hash_seed)] & 0xA5);
        tmp += ((p1 & 0xF0) | (p2 & 0x0F)) + ((p1 & 0x0F) | (p2 & 0xF0));
        p3 += hash_seed[i % strlen(hash_seed)];
    }
    return (base + (tmp * p3 % size));
}
//////////////////////////////////////////////////////////////////////////
double com(double **value_list, int value_count, char *symbol_list, int symbol_count)
{
    if (symbol_list[0] == '(')
        return com(value_list, value_count, symbol_list + 1, symbol_count - 1);
    int i = 0, j = 0;
    double result = 0;
    result = *value_list[0];
    for (i = 1, j = 0; (i < value_count) && (j < symbol_count); ++i, ++j)
    {
        switch (symbol_list[j])
        {
        case '+':
            if (symbol_list[j + 1] == '(')
            {
                result += com(value_list + i, value_count - i, symbol_list + j + 2, symbol_count - j - 2);
                for (/*void*/; symbol_list[j] == ')'; ++j)
                {
                    if (symbol_list[j] == '(')
                        continue;
                    else
                        ++i;
                }
                ++i;
                j -= 2;
            }
            else
                result += *value_list[i];

            break;
        case '-':
            if (symbol_list[j + 1] == '(')
            {
                result -= com(value_list + i, value_count - i, symbol_list + j + 2, symbol_count - j - 2);
                for (/*void*/; symbol_list[j] == ')'; ++j)
                {
                    if (symbol_list[j] == '(')
                        continue;
                    else
                        ++i;
                }
                ++i;
                j -= 2;
            }
            else
                result -= *value_list[i];
            break;
        case '*':
            if (symbol_list[j + 1] == '(')
            {
                result *= com(value_list + i, value_count - i, symbol_list + j + 2, symbol_count - j - 2);
                for (/*void*/; symbol_list[j] == ')'; ++j)
                {
                    if (symbol_list[j] == '(')
                        continue;
                    else
                        ++i;
                }
                ++i;
                j -= 2;
            }
            else
                result *= *value_list[i];
            break;
        case '/':
            if (symbol_list[j + 1] == '(')
            {
                result /= com(value_list + i, value_count - i, symbol_list + j + 2, symbol_count - j - 2);
                for (/*void*/; symbol_list[j] == ')'; ++j)
                {
                    if (symbol_list[j] == '(')
                        continue;
                    else
                        ++i;
                }
                ++i;
                j -= 2;
            }
            else
            {
                if (value_list[i] == 0)
                    return 0.0;
                else
                    result /= *value_list[i];
            }
            break;
        case '^':
            if (symbol_list[j + 1] == '(')
            {
                result = pow(result, com(value_list + i, value_count - i, symbol_list + j + 2, symbol_count - j - 2));
                for (/*void*/; symbol_list[j] == ')'; ++j)
                {
                    if (symbol_list[j] == '(')
                        continue;
                    else
                        ++i;
                }
                ++i;
                j -= 2;
            }
            else
            {
                if ((result < 0) && (value_list[i] < 0))
                    return 0.0;
                else
                    result = pow(result, *value_list[i]);
            }
            break;
        case ')':
            return result;
        }
    }
    return result;
}
//////////////////////////////////////////////////////////////////////////