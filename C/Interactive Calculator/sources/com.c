double com(double **value_list, int value_count, char *symbol_list, int symbol_count)
{
    int i = 0, j = 0;
    double result = 0;
    result = *value_list[0];
    for (i = 1, j = 0; (i < value_count) && (j < symbol_count); i++, j++)
    {
        switch (symbol_list[j])
        {
        case '+':
            result += *value_list[i];
            break;
        case '-':
            result -= *value_list[i];
            break;
        case '*':
            result *= *value_list[i];
            break;
        case '/':
            if (value_list[i] == 0)
                return 0.0;
            result /= *value_list[i];
            break;
        case '^':
            if ((result < 0) && (value_list[i] < 0))
                return 0.0;
            result = pow(result, *value_list[i]);
            break;
        }
    }
    return result;
}