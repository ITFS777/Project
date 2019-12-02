#include<stdio.h>
#include<windows.h>
#include"utility.h"
#include "database.h"
/////////////////////////////////////////////////////////////////////////////////////////////////
unsigned short g_choice = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////
void menu(void)
{
	CLS;
	PRINT_LINE;
	printf("**            图    书    管    理    系    统    v2.0            **\n");
	PRINT_LINE;
	NEWLINE;
	printf("                        <0>关闭系统\n");
	printf("                        <1>查找书籍\n");
	printf("                        <2>增加书籍\n");
	printf("                        <3>删除书籍\n");
	printf("                        <4>保存数据\n");
	printf("                        <5>载入数据库\n");
	printf("                        <6>查看更新日志\n");
	NEWLINE;
	PRINT_LINE;
	PRINT_CHOICE;
	choice_judge(get_menu_choice());
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void menu_search(void)
{
	CLS;
	PRINT_LINE;
	printf("**                  查    找    书    籍                          **\n");
	PRINT_LINE;
	NEWLINE;
	printf("                      <0>返回上一级\n");
	printf("                      <1>按书籍名称查询\n");
	printf("                      <2>按作者名称查询\n");
	printf("                      <3>按出版商查询\n");
	printf("                      <4>按入库日期查询\n");
	printf("                      <5>按出版日期查询\n");
	printf("                      <6>按书籍序号查询\n");
	printf("                      <7>查看全部书籍\n");
	NEWLINE;
	PRINT_LINE;
	PRINT_CHOICE;
	choice_judge(get_search_choice());
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void menu_add(void)
{
	CLS;
	PRINT_LINE;
	printf("**                  添    加    书    籍                          **\n");
	PRINT_LINE;
	NEWLINE;
	printf("                      <0>返回上一级\n");
	printf("                      <1>录入书籍信息\n");
	NEWLINE;
	PRINT_LINE;
	PRINT_CHOICE;
	choice_judge(get_add_choice());
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void menu_del(void)
{
	CLS;
	PRINT_LINE;
	printf("**                  删    除    书    籍                          **\n");
	PRINT_LINE;
	NEWLINE;
	printf("                      <0>返回上一级\n");
	printf("                      <1>按书籍名称删除\n");
	printf("                      <2>按书籍序号删除\n");
	NEWLINE;
	PRINT_LINE;
	PRINT_CHOICE;
	choice_judge(get_del_choice());
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void menu_save(void)
{
	CLS;
	int flag = 0;
	printf("正在保存书籍数据...\n");
	FILE* FileName = fopen(DATEBASE_FILENAME, "w");
	flag = datebase_save(FileName);
	if(flag == SUCCEED)
		printf("保存成功！\n按回车返回主菜单");
	else
		printf("保存失败！\n按回车返回主菜单");
	getchar();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void menu_reload(void)
{
	CLS;
	int flag = 0;
	printf("正在加载数据库...\n");
	FILE* FileName = fopen(DATEBASE_FILENAME, "r");
	flag = datebase_reload(FileName);
	if(flag == SUCCEED)
		printf("加载成功！\n按回车返回主菜单");
	else
		printf("加载失败！\n按回车返回主菜单");
	getchar();
}
/////////////////////////////////////////////////////////////////////////////////////////////////