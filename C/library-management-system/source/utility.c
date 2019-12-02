#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"menu.h"
#include"search.h"
#include"database.h"
#include"utility.h"
#include "log.h"
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
int get_menu_choice(void)
{
	extern g_choice;
	int flag = 1;
	flag = scanf("%u", &g_choice);
	getchar();
	if(flag == EOF)
		return FALSE;
	if(g_choice == 0 || g_choice == 1 || g_choice == 2 || g_choice == 3 || g_choice == 4 || g_choice == 5 || g_choice == 6)
	{
		switch(g_choice)
		{
			case 0:
				printf("正在保存数据库...\n");
				datebase_save();
				printf("保存完成！\n");
				printf("系统已关闭\n");
/*--------------------LOG--------------------*/
#if LOG

				log_system_close();

#endif
/*++++++++++++++++++++LOG++++++++++++++++++++*/
				exit(0);			/*返回main函数并结束程序*/
			case 1:
				menu_search();		/*进入查找界面*/
				break;
			case 2:
				menu_add();			/*进入添加书籍界面*/
				break;
			case 3:
				menu_del();			/* 进入删除书籍界面*/
				break;
			case 4:
				menu_save();		/*进入保存书籍数据界面*/
				break;
			case 5:
				menu_reload();		/*进入重载数据库界面*/
				break;
			case 6:
				log_update();
		}
		return SUCCEED;

	}
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int get_search_choice(void)
{
	extern g_choice;
	int flag = 1;
	flag = scanf("%hu", &g_choice);
	getchar();
	if(flag == EOF)
		return FALSE;
	if(g_choice == 0 || g_choice == 1 || g_choice == 2 || g_choice == 3 || g_choice == 4 || g_choice == 5 || g_choice == 6 || g_choice == 7)
	{
		switch(g_choice)
		{
			case 0:
				return SUCCEED;
			case 1:
				search_judge(search_name());
				break;
			case 2:
				search_judge(search_auther());
				break;
			case 3:
				search_judge(search_publisher());
				break;
			case 4:
				search_judge(search_in_time());
				break;
			case 5:
				search_judge(search_pub_time());
				break;
			case 6:
				search_judge(search_serial());
				break;
			case 7:
				print_allbook();
		}
		return SUCCEED;
	}
	else
		return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int get_add_choice(void)
{
	extern g_choice;
	int flag = 1;
	flag = scanf("%hu", &g_choice);
	getchar();
	if(flag == EOF)
		return FALSE;
	if(g_choice == 0 || g_choice == 1)
	{
		switch(g_choice)
		{
			case 0:
				return SUCCEED;
			case 1:
				book_add();
		}
		return SUCCEED;
	}
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int get_del_choice(void)
{
	extern g_choice;
	int flag = 1;
	flag = scanf("%hu", &g_choice);
	getchar();
	if(flag == EOF)
		return FALSE;
	if(g_choice == 0 || g_choice == 1 || g_choice == 2)
	{
		switch(g_choice)
		{
			case 0:
				return SUCCEED;
			case 1:
				search_judge(book_del());
				break;
			case 2:
				search_judge(book_del_serial());
		}
		return SUCCEED;
	}
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void choice_judge(const int flag)
{
	if(flag == FALSE)
	{
		printf("操作失败！请检查菜单序号是否正确\n按回车返回主菜单\n");
		getchar();
		system("CLS");
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void search_judge(const int flag)
{
	if(flag == SUCCEED)
	{
		printf("按回车返回主菜单\n");
		getchar();
		return;
	}
	else
	{
		printf("未找到指定书籍！请检查书籍信息是否正确\n按回车返回主菜单\n");
		getchar();
		system("CLS");
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void print_progress(const int i)
{
	printf("\r%d%%", i);
}
/////////////////////////////////////////////////////////////////////////////////////////////////