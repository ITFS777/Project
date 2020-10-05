#include "utility.h"
#include "data.h"
#include "menu.h"
////////////////////////////////////////////////////////////////////////////////
Data *database = new Data;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    initialize();
    int i = 0;
    while (!login())
        if (++i >= 3) // 密码错误3次自动关闭
            return -1;
    database->load();
    menu();
    return 0;
}