#ifndef STUINFO_H
#define STUINFO_H

#include <iostream>
#include <string>
#include <regex>
#include <stdexcept>
////////////////////////////////////////////////////////////////////////////////
using namespace std;
////////////////////////////////////////////////////////////////////////////////
extern regex STU_NUM_PATTERN;
extern regex GENDER_PATTERN;
extern regex DOR_NUM_PATTERN;
extern regex BIRTHDAY_PATTERN;
extern regex PHONE_NUM_PATTERN;
// 性别枚举
enum Gender
{
    FEMALE = 0,
    MALE = 1,
    UNKNOWN = 2
};
////////////////////////////////////////////////////////////////////////////////
class StuInfo
{
public:
    StuInfo()
    {
        _gender = UNKNOWN;
        _last = nullptr;
        _next = nullptr;
        _empty = true;
    }
    friend class Data;
    friend istream &operator>>(istream &is, StuInfo &stu);
    friend ostream &operator<<(ostream &os, StuInfo &stu);

    inline bool empty() const { return _empty; }

private:
    string _name;
    string _stuID;
    Gender _gender;
    string _dorNum;
    string _birthday;
    string _phoneNum;
    string _hometown;

    StuInfo *_last;
    StuInfo *_next;

    bool _empty;
};

istream &operator>>(istream &is, StuInfo &stu)
{

    string tmp_item;
_start:

    try
    {
        // 输入学生姓名
        is >> tmp_item;
        stu._name = tmp_item;

        // 输入学生学号
        is >> tmp_item;
        // 输入格式检测
        if (regex_match(tmp_item, STU_NUM_PATTERN))
            stu._stuID = tmp_item;
        else // 格式错误 抛出异常
            throw runtime_error("Student Number Mismatch.");

        // 输入学生性别
        is >> tmp_item;
        if (regex_match(tmp_item, GENDER_PATTERN))
            stu._gender = Gender(stoi(tmp_item));
        /* switch (stoi(tmp_item))
            {
            case 0:
                stu._gender = FEMALE;
                break;
            case 1:
                stu._gender = MALE;
                break;
            default:
                stu._gender = UNKNOWN;
                break;
            } */
        else
            throw runtime_error("Student Gender Mismatch.");

        // 输入寝室号
        is >> tmp_item;
        if (regex_match(tmp_item, DOR_NUM_PATTERN))
            stu._dorNum = tmp_item;
        else
            throw runtime_error("Dormitory Number Mismatch.");

        // 输入生日
        is >> tmp_item;
        if (regex_match(tmp_item, BIRTHDAY_PATTERN))
            stu._birthday = tmp_item;
        else
            throw runtime_error("Birthday Mismatch.");

        // 输入手机号
        is >> tmp_item;
        if (regex_match(tmp_item, PHONE_NUM_PATTERN))
            stu._phoneNum = tmp_item;
        else
            throw runtime_error("Phone Number Mismatch.");

        // 输入籍贯
        is >> tmp_item;
        stu._hometown = tmp_item;
        stu._empty = false;
    }
    catch (runtime_error err)
    {
        cerr << "ERROR: " << err.what() << endl
             << "Please try again." << endl;
        goto _start;
    }
    return is;
}

ostream &operator<<(ostream &os, StuInfo &stu)
{
    os << stu._name << ' '
       << stu._stuID << ' '
       << stu._gender << ' '
       << stu._dorNum << ' '
       << stu._birthday << ' '
       << stu._phoneNum << ' '
       << stu._hometown;
    return os;
}

#endif