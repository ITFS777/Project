#ifndef DATA_H
#define DATA_H

#include <string>
#include "stuinfo.h"

class Data
{
public:
    friend class StuInfo;

    Data()
    {
        _length = 0;
        _head = new StuInfo;
        _tail = _head;
    }
    ~Data()
    {
        while (_tail->_last != nullptr)
        {
            _tail = _tail->_last;
            delete _tail->_next;
        }
        delete _tail;
    }

    inline StuInfo* back() const;
    inline StuInfo* front() const;
    inline int size() const;
    inline void increase(int _X);
    void showAll() const;
    void add();
    StuInfo* search(std::string& _KeyWord);
    void remove(StuInfo*& _Remove);
    void change(StuInfo*& _Change);
    bool load();
    bool save();

private:
    int _length;
    StuInfo *_head;
    StuInfo *_tail;
};

#endif