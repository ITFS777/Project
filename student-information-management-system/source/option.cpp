#include <iostream>
#include <string>
#include "option.h"
#include "utility.h"
////////////////////////////////////////////////////////////////////////////////
Option Option::choose(void) const
{ // 高亮选中项
    SetCursorPosition(_x, _y);
    SetBackColor();
    std::cout << _content;
    return *this;
}
Option Option::unchoose(void) const
{ // 取消高亮
    SetCursorPosition(_x, _y);
    SetColor(UNCHOSEN_CONTENT_COLOR_ID);
    std::cout << _content;
    return *this;
}
Option Option::clear(void) const
{ // 清除选项
    SetCursorPosition(_x, _y);
    SetColor(UNCHOSEN_CONTENT_COLOR_ID);
    std::cout << std::string(_content.size(), ' ');
    return *this;
}