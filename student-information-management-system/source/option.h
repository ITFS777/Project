#ifndef OPTION_H
#define OPTION_H

#include <string>
////////////////////////////////////////////////////////////////////////////////
class Option
{
public:
    Option() = default;
    Option(std::string str, int x, int y) : _content(str), _x(x), _y(y) {}
    Option choose(void) const;
    Option unchoose(void) const;
    Option clear(void) const;

private:
    int _x, _y;
    std::string _content;
    static constexpr int CHOSEN_CONTENT_COLOR_ID = 0;
    static constexpr int CHOSEN_BACK_COLOR_ID = 7;
    static constexpr int UNCHOSEN_CONTENT_COLOR_ID = 7;
    static constexpr int UNCHOSEN_BACK_COLOR_ID = 0;
};

#endif