#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <initializer_list>
#include <windows.h>
#include "option.h"
////////////////////////////////////////////////////////////////////////////////
extern std::string g_password;
extern int g_screenX, g_screenY;
////////////////////////////////////////////////////////////////////////////////
void SetCursorPosition(const int _X, const int _Y);
void SetColor(int _ColorID);
void SetBackColor(void);
void PrintStr(std::string _Str, const int _X, const int _Y, const int _ColorID);
int selector(std::initializer_list<Option> _Opt);
void initialize(void);
void freshScreen();
bool login();


#endif