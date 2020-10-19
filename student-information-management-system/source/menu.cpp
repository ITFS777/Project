#include <iostream>
#include <cstdio>
#include <string>
#include <stdexcept>
#include "stuinfo.h"
#include "utility.h"
#include "option.h"
#include "data.h"
#include "menu.h"
////////////////////////////////////////////////////////////////////////////////
extern Data *database;
using std::cin;
using std::cout;
using std::endl;
using std::runtime_error;
using std::string;
////////////////////////////////////////////////////////////////////////////////
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
void pause()
{
    cout << "Type any key to continue." << endl;
    getchar();
}
////////////////////////////////////////////////////////////////////////////////
void menu()
{
    string block("■");
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

    switch (selector({add_stu, search_edit, print_all, load_data, save_data, exit_sys}))
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
    if(database->size()==0)
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
    freshScreen();
_start:
    try
    {
        string keyword;
        cout << "Please input the keyword" << endl;
        cin >> keyword;
        getchar();
        StuInfo *found = database->search(keyword);
        if (found == nullptr)
            throw runtime_error("Item Not Found");
        switch (selector({edit, del, reSearch, cancel}))
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