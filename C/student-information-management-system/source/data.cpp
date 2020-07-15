#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <regex>
#include "data.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::regex_match;
using std::string;
// 正则类型匹配模式
regex STU_NUM_PATTERN(string("^[0-9]{8}$"));
regex GENDER_PATTERN(string("^[0-2]$"));
regex DOR_NUM_PATTERN(string("^[0-9]{3,4}$"));
regex BIRTHDAY_PATTERN(string("^[0-9]{4}\\.[0-9]{2}\\.[0-9]{2}$"));
regex PHONE_NUM_PATTERN(string("^[0-9]{11}$"));
////////////////////////////////////////////////////////////////////////////////
inline StuInfo *Data::back() const
{
    return _tail;
}
////////////////////////////////////////////////////////////////////////////////
inline StuInfo *Data::front() const
{
    return _head;
}
////////////////////////////////////////////////////////////////////////////////
inline int Data::size() const
{
    return _length;
}
////////////////////////////////////////////////////////////////////////////////
inline void Data::increase(int _X)
{
    _length += _X;
}
////////////////////////////////////////////////////////////////////////////////
void Data::showAll() const
{
    StuInfo *p = _head;
    if (_length)
        while (p != nullptr && !p->empty())
        {
            cout << *p << endl;
            p = p->_next;
        }
    else
        cout << "There are nothing!" << endl;
}
////////////////////////////////////////////////////////////////////////////////
void Data::add()
{
    _tail->_next = new StuInfo;
    _tail->_next->_last = _tail;
    _tail = _tail->_next;
}
////////////////////////////////////////////////////////////////////////////////
StuInfo *Data::search(string &_KeyWord)
{
    StuInfo *p = _head;
    StuInfo *found = nullptr;
    while (p != nullptr)
    {
        if (p->_name == _KeyWord || p->_stuID == _KeyWord || p->_dorNum == _KeyWord || p->_hometown == _KeyWord)
        {
            cout << *p << endl;
            found = p;
        }
        p = p->_next;
        continue;
    }
    return found;
}
////////////////////////////////////////////////////////////////////////////////
void Data::remove(StuInfo *&_Remove)
{
    if (_Remove == _head && _Remove == _tail)
    {
        _head = new StuInfo;
        _tail = _head;
    }
    else if (_Remove == _head)
    {
        _head = _Remove->_next;
        _head->_last = nullptr;
    }
    else if (_Remove == _tail)
    {
        _tail = _Remove->_last;
        _tail->_next = nullptr;
    }
    else
    {
        _Remove->_last->_next = _Remove->_next;
        _Remove->_next->_last = _Remove->_last;
    }
    delete _Remove;
    --_length;
}
////////////////////////////////////////////////////////////////////////////////
void Data::change(StuInfo *&_Change)
{
    cout << "Current value:" << endl;
    cout << *_Change << endl;
    cout << "Please input new value." << endl;
    cin >> *_Change;
    cout << "Changed Successfully." << endl;
    cout << "New value:" << endl
         << *_Change << endl;
    cout << "Type any key to continue." << endl;
    getchar();
    getchar();
}
////////////////////////////////////////////////////////////////////////////////
bool Data::load()
{
    std::ifstream ifs_data;
    StuInfo *p = _head;
    bool flag = true;
    ifs_data.open("data.txt", ios::in);
    if (ifs_data)
    {
        _length = 0;
        int len;
        ifs_data >> len;
        for (int i = 0; i < len; ++i)
        {
            if (p == nullptr)
            {
                add();
                p = _tail;
            }
            ifs_data >> *p;
            p->_empty = false;
            p = p->_next;
            ++_length;
        }
    }
    else
        flag = false;
    ifs_data.close();
    return flag;
}
////////////////////////////////////////////////////////////////////////////////
bool Data::save()
{
    std::ofstream ofs_data;
    StuInfo *p = _head;
    bool flag = true;
    ofs_data.open("data.txt", ios::out);
    if (ofs_data)
    {
        ofs_data << _length << endl;
        for (int i = 0; i < _length; ++i)
        {
            ofs_data << *p << endl;
            p = p->_next;
        }
    }
    else
        flag = false;
    ofs_data.close();
    return flag;
}