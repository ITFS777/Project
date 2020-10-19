#include <iostream>
#include <fstream>
#include <string>
#include <initializer_list>
#include <windows.h>
#include <conio.h>
#include "utility.h"
#include "option.h"
////////////////////////////////////////////////////////////////////////////////
using std::cout;
using std::endl;
using std::ios;
using std::string;
string g_password;
int g_screenX = 35;
int g_screenY = 20;
////////////////////////////////////////////////////////////////////////////////
void SetCursorPosition(const int _X, const int _Y)
{ // consoleAPI 设置光标位置
    COORD position;
    position.X = _X * 2;
    position.Y = _Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
////////////////////////////////////////////////////////////////////////////////
void SetColor(int _ColorID)
{ // consoleAPI 设置字体颜色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _ColorID);
}
////////////////////////////////////////////////////////////////////////////////
void SetBackColor(void)
{ // consoleAPI 设置字体背景色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_BLUE |
                                BACKGROUND_BLUE |
                                BACKGROUND_GREEN |
                                BACKGROUND_RED);
}
////////////////////////////////////////////////////////////////////////////////
void PrintStr(string _Str, const int _X, const int _Y, const int _ColorID)
{ // 在指定位置打印字符串
    if (!_ColorID)
        SetBackColor();
    SetCursorPosition(_X, _Y);
    SetColor(_ColorID);
    cout << _Str;
}
////////////////////////////////////////////////////////////////////////////////
int selector(std::initializer_list<Option> _Opt)
{                                // 选项选择器
    int choice_cnt = _Opt.size(); // 选项数量
    auto last = _Opt.begin(), next = _Opt.begin();
    auto back = _Opt.begin();
    for (int i = 1; i < choice_cnt; ++i)
        ++back;
    char ch = 0;       // 键盘映射
    bool flag = false; // 是否选择该选项

    for (auto i = _Opt.begin(); i != _Opt.end(); ++i)
        i->unchoose();

    do
    {
        switch (ch)
        {
        case 72: // UP
        case 75: //RIGHT
            (last != _Opt.begin()) ? next = last - 1 : next = back;
            break;
        case 80: // DOWN
        case 77: // LEFT
            (last != _Opt.begin() + choice_cnt - 1) ? next = last + 1 : next = _Opt.begin();
            break;
        case 13: // ENTER
            flag = true;
            break;
        default:
            break;
        }
        if (flag) // 选中则跳出循环
            break;
        last->unchoose();
        next->choose();
        last = next;
    } while (ch = _getch());

    for (auto i = _Opt.begin(); i != _Opt.end(); ++i)
        i->clear();

    return last - _Opt.begin(); // 返回选择项的序号
}
////////////////////////////////////////////////////////////////////////////////
void initialize(void)
{
    // 更改console标题
    system("title Student Info Management System");
    // 更改console代码页为UTF-8(65001)
    system("chcp 65001");
    std::ifstream ifs_config;
    ifs_config.open("config.cfg", ios::in);
    if (ifs_config)
    { // 文件存在且打开成功
        ifs_config >> g_password >> g_screenX >> g_screenY;
        ifs_config.close();
    }
    else
    { // 文件不存在或打开失败
        std::ofstream ofs_config;
        ofs_config.open("config.cfg", ios::out);
        g_password = string("admin");
        ofs_config << g_password << endl
                   << g_screenX << ' ' << g_screenY;
        ofs_config.close();
    }
}
////////////////////////////////////////////////////////////////////////////////
void freshScreen()
{
    char cmd[30];
    sprintf(cmd, "mode con cols=%d lines=%d", 2 * g_screenX, g_screenY);
    system(cmd);
    system("cls");
}
////////////////////////////////////////////////////////////////////////////////
bool login()
{
    int login_x, login_y;
    login_x = 30;
    login_y = 5;
    char cmd[30];
    sprintf(cmd, "mode con cols=%d lines=%d", 2 * login_x, login_y);
    system(cmd);

    string block("■");
    string board;
    for (int i = 0; i < login_x; ++i)
        board += block;

    cout << board << endl;
    for (int i = 0; i < 3; ++i)
        cout << block + string(login_x * 2-4, ' ') + block << endl;
    cout << board;

    SetCursorPosition(6, 2);
    cout << "password:";
    
    string input_passwd;
    char key;
    int i = 0;
    while((key = getch())!='\r')
    {
        if(key == 8) // BACKSPACE
        {
            cout <<"\b \b";
            --i;
        }
        else
        {
            input_passwd += string(1,key);
            cout << '*';
            ++i;
        }
    }
    input_passwd.erase(i);

    if(input_passwd == g_password)
        return true;
    else
        return false;

}