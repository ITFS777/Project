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
    if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '^') || (ch == '%') || (ch == '='))
        return true;
    else
        return false;
}
//////////////////////////////////////////////////////////////////////////