#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <regex>
#include <stdexcept>
#include <initializer_list>
#include <windows.h>
#include <conio.h>
////////////////////////////////////////////////////////////////////////////////
using namespace std;
////////////////////////////////////////////////////////////////////////////////
string g_password;
int g_screenX = 35;
int g_screenY = 20;
// 性别枚举类型
enum Gender
{
    FEMALE = 0,
    MALE = 1,
    UNKNOWN = 2
};
// 正则类型匹配模式
regex STU_NUM_PATTERN(string("^[0-9]{8}$"));
regex GENDER_PATTERN(string("^[0-2]$"));
regex DOR_NUM_PATTERN(string("^[0-9]{3,4}$"));
regex BIRTHDAY_PATTERN(string("^[0-9]{4}\\.[0-9]{2}\\.[0-9]{2}$"));
regex PHONE_NUM_PATTERN(string("^[0-9]{11}$"));
////////////////////////////////////////////////////////////////////////////////
void SetCursorPosition(const int _X, const int _Y);
void SetColor(int _ColorID);
void SetBackColor(void);
void PrintStr(std::string _Str, const int _X, const int _Y, const int _ColorID);
void initialize(void);
void freshScreen();
bool login();
void pause();
void menu();
void addStu();
void searchEdit();
void printAll();
void loadData();
void saveData();
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
////////////////////////////////////////////////////////////////////////////////
int selector(std::initializer_list<Option> _Opt);
Option add_stu(string("Add New Student"), (g_screenX - 7) / 2 - 1, 6);
Option search_edit(string("Search and Edit"), (g_screenX - 7) / 2 - 1, 8);
Option print_all(string("Print All"), (g_screenX - 4) / 2 - 1, 10);
Option load_data(string("Load Data"), (g_screenX - 4) / 2 - 1, 12);
Option save_data(string("Save Data"), (g_screenX - 4) / 2 - 1, 14);
Option exit_sys(string("Exit"), (g_screenX - 2) / 2 - 1, 16);
Option edit(string("Edit"), g_screenX / 6, g_screenY - 2);
Option del(string("Delete"), g_screenX / 6 * 2, g_screenY - 2);
Option reSearch(string("ReSearch"), g_screenX / 6 * 3, g_screenY - 2);
Option cancel(string("Cancel"), g_screenX / 6 * 5, g_screenY - 2);
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
    friend istream& operator>>(istream& is, StuInfo& stu);
    friend ostream& operator<<(ostream& os, StuInfo& stu);

    inline bool empty() const { return _empty; }

private:
    string _name;
    string _stuID;
    Gender _gender;
    string _dorNum;
    string _birthday;
    string _phoneNum;
    string _hometown;

    StuInfo* _last;
    StuInfo* _next;

    bool _empty;
};
istream& operator>>(istream& is, StuInfo& stu)
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

ostream& operator<<(ostream& os, StuInfo& stu)
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
////////////////////////////////////////////////////////////////////////////////
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
    StuInfo* _head;
    StuInfo* _tail;
};
inline StuInfo* Data::back() const
{
    return _tail;
}
inline StuInfo* Data::front() const
{
    return _head;
}
inline int Data::size() const
{
    return _length;
}
inline void Data::increase(int _X)
{
    _length += _X;
}
void Data::showAll() const
{
    StuInfo* p = _head;
    if (_length)
        while (p != nullptr && !p->empty())
        {
            cout << *p << endl;
            p = p->_next;
        }
    else
        cout << "There are nothing!" << endl;
}
void Data::add()
{
    _tail->_next = new StuInfo;
    _tail->_next->_last = _tail;
    _tail = _tail->_next;
}
StuInfo* Data::search(string& _KeyWord)
{
    StuInfo* p = _head;
    StuInfo* found = nullptr;
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
void Data::remove(StuInfo*& _Remove)
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
void Data::change(StuInfo*& _Change)
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
bool Data::load()
{
    std::ifstream ifs_data;
    StuInfo* p = _head;
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
bool Data::save()
{
    std::ofstream ofs_data;
    StuInfo* p = _head;
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
////////////////////////////////////////////////////////////////////////////////
Data* database = new Data;
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
////////////////////////////////////////////////////////////////////////////////
void SetCursorPosition(const int _X, const int _Y)
{ // consoleAPI 设置光标位置
    COORD position;
    position.X = _X * 2;
    position.Y = _Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
////////////////////////////////////////
void SetColor(int _ColorID)
{ // consoleAPI 设置字体颜色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _ColorID);
}
////////////////////////////////////////
void SetBackColor(void)
{ // consoleAPI 设置字体背景色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_BLUE |
        BACKGROUND_BLUE |
        BACKGROUND_GREEN |
        BACKGROUND_RED);
}
////////////////////////////////////////////////////////////////////////////////
void initialize(void)
{
    // 更改console标题
    system("title Student Info Management System");
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
        g_screenX = 35;
        g_screenY = 20;
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

    string block("**");
    string board;
    for (int i = 0; i < login_x; ++i)
        board += block;

    cout << board << endl;
    for (int i = 0; i < 3; ++i)
        cout << block + string(login_x * 2 - 4, ' ') + block << endl;
    cout << board;

    SetCursorPosition(6, 2);
    cout << "password:";

    string input_passwd;
    char key;
    int i = 0;
    while ((key = getch()) != '\r')
    {
        if (key == 8) // BACKSPACE
        {
            cout << "\b \b";
            --i;
        }
        else
        {
            input_passwd += string(1, key);
            cout << '*';
            ++i;
        }
    }
    input_passwd.erase(i);

    if (input_passwd == g_password)
        return true;
    else
        return false;

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
void pause()
{
    cout << "Type any key to continue." << endl;
    getchar();
}
////////////////////////////////////////////////////////////////////////////////
void menu()
{
    string block("**");
    string board;
    for (int i = 0; i < g_screenX; ++i)
        board += block;
_start:
    freshScreen();
    cout << board << endl;
    for (int i = 0; i < 3; ++i)
        cout << block + string(g_screenX * 2 - 4, ' ') + block << endl;
    cout << board << endl;
    cout << "Current items:" << database->size();

    SetCursorPosition((g_screenX - 19) / 2, 2);
    cout << "Students Information Management System";

    switch (selector({ add_stu, search_edit, print_all, load_data, save_data, exit_sys }))
    { // 菜单选择器
    case 0:
        addStu();
        break;
    case 1:
        searchEdit();
        break;
    case 2:
        printAll();
        break;
    case 3:
        loadData();
        break;
    case 4:
        saveData();
        break;
    case 5:
    default:
        exit(0);
    }
    goto _start;
}
////////////////////////////////////////////////////////////////////////////////
void addStu()
{
    freshScreen();
    cout << "Please input student information as the format below." << endl;
    cout << "Name StudentID Gender DormNum Birthday(YYYY.MM.DD) PhoneNum Hometown" << endl;
    if (!database->back()->empty())
        database->add();
    cin >> *database->back();
    database->increase(1);
    cout << "Added successfully." << endl;
    cout << "New item:" << endl
        << *database->back() << endl;
    cout << "Type any key to continue." << endl;
    getchar();
    getchar();
}
////////////////////////////////////////////////////////////////////////////////
void searchEdit()
{
    
_start:
    try
    {
        freshScreen();
        cout << "Please input the keyword" << endl;
        string keyword;
        cin >> keyword;
        getchar();
        StuInfo* found = database->search(keyword);
        if (found == nullptr)
            throw runtime_error("Item Not Found");
        switch (selector({ edit, del, reSearch, cancel }))
        {
        case 0:
            freshScreen();
            database->change(found);
            pause();
            break;
        case 1:
            freshScreen();
            database->remove(found);
            cout << "Removed Successfully." << endl;
            pause();
            break;
        case 2:
            goto _start;
        case 3:
        default:
            return;
        }
    }
    catch (runtime_error err)
    {
        std::cerr << "Error: " << err.what() << endl;
        cout << "Please Try Again." << endl;
        getchar();
    }
    
}
////////////////////////////////////////////////////////////////////////////////
void printAll()
{
    freshScreen();
    database->showAll();
    pause();
}
////////////////////////////////////////////////////////////////////////////////
void loadData()
{
    freshScreen();
    try
    {
        cout << "Loading..." << endl;
        if (database->load())
            cout << "Done" << endl;
        else
            throw runtime_error("File Not Found");
    }
    catch (runtime_error err)
    {
        std::cerr << "Error: " << err.what() << endl;
        cout << "Please try again." << endl;
    }
    pause();
}
////////////////////////////////////////////////////////////////////////////////
void saveData()
{
    freshScreen();
    try
    {
        cout << "Saving..." << endl;
        if (database->save())
            cout << "Saved" << endl;
        else
            throw runtime_error("Permission Denied");
    }
    catch (runtime_error err)
    {
        std::cerr << "Error: " << err.what() << endl;
        cout << "Please try again." << endl;
    }
    pause();
}