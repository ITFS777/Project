#include<stdio.h>
#include<string.h>
#include<windows.h>

#include"utility.h"
#include"database.h"
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
int search_name(void)	/*按书籍名称查询*/
{
	extern bookinf book[];
	CLS;
	char search_name[LEN_NAME] = { '\0' };
	bookinf* p = NULL;
	int i = 0;
	printf("请输入书籍名称:");
	gets(search_name);
	p = book;
	for(i = 0; i < DATEBASE_SIZE; i++)
	{
		if(strncmp(p->name, search_name, sizeof(search_name)) == 0)
		{
			printf("已找到该书籍，下面是书籍信息");
			NEWLINE;
			PRINT_LINE;
			print_BookInf(p);
			PRINT_LINE;
			return SUCCEED;
		}
		else
			p = p->next;
	}
	return FALSE;				/*未查询到该书籍*/
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int search_auther(void)		/*按作者查询*/
{
	CLS;
	extern bookinf book[];
	char search_auther[LEN_NAME] = { '\0' };
	bookinf* p = NULL;
	int i = 0;
	printf("请输入作者名称:");
	gets(search_auther);
	p = book;
	for(i = 0; i < DATEBASE_SIZE; i++)
	{
		if(strncmp(p->auther, search_auther, sizeof(search_auther)) == 0)
		{
			printf("已找到该书籍，下面是书籍信息");
			NEWLINE;
			PRINT_LINE;
			print_BookInf(p);
			PRINT_LINE;
			return SUCCEED;
		}
		else
			p = p->next;
	}
	return FALSE;				/*未查询到该书籍*/
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int search_publisher(void)		/*按出版商查询*/
{
	CLS;
	extern bookinf book[];
	char search_publisher[LEN_NAME] = { '\0' };
	bookinf* p = NULL;
	int i = 0;
	printf("请输入书籍名称:");
	gets(search_publisher);
	p = book;
	for(i = 0; i < DATEBASE_SIZE; i++)
	{
		if(strncmp(p->publisher, search_publisher, sizeof(search_publisher)) == 0)
		{
			printf("已找到该书籍，下面是书籍信息");
			NEWLINE;
			PRINT_LINE;
			print_BookInf(p);
			PRINT_LINE;
			return SUCCEED;
		}
		else
			p = p->next;
	}
	return FALSE;				/*未查询到该书籍*/
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int search_pub_time(void)		/*按出版日期查询*/
{
	CLS;
	extern bookinf book[];
	unsigned year = 0;
	unsigned short month = 0;
	unsigned short day = 0;
	bookinf* p = NULL;
	int i = 0;
	printf("请输入出版日期:(格式：YYYY.MM.DD)\n");
	if(scanf("%u.%hu.%hu", &year, &month, &day) == EOF)
		return FALSE;
	getchar();
	p = book;
	for(i = 0; i < DATEBASE_SIZE; i++)
	{
		if(p->time_pub.year == year && p->time_pub.month == month && p->time_pub.day == day)
		{
			printf("已找到该书籍，下面是书籍信息");
			NEWLINE;
			PRINT_LINE;
			print_BookInf(p);
			PRINT_LINE;
			return SUCCEED;
		}
		else
			p = p->next;
	}
	return FALSE;				/*未查询到该书籍*/
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int search_in_time(void)		/*按入库日期查询*/
{
	CLS;
	extern bookinf book[];
	unsigned year = 0;
	unsigned short month = 0;
	unsigned short day = 0;
	bookinf* p = NULL;
	int i = 0;
	printf("请输入入库日期:(格式：YYYY.MM.DD)\n");
	if(scanf("%u.%hu.%hu", &year, &month, &day) == EOF)
		return FALSE;
	getchar();
	p = book;
	for(i = 0; i < DATEBASE_SIZE; i++)
	{
		if(p->time_in.year == year && p->time_in.month == month && p->time_in.day == day)
		{
			printf("已找到该书籍，下面是书籍信息");
			NEWLINE;
			PRINT_LINE;
			print_BookInf(p);
			PRINT_LINE;
			return SUCCEED;
		}
		else
			p = p->next;
	}
	return FALSE;				/*未查询到该书籍*/
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void search_serial(void)
{
	extern bookinf book[];
	CLS;
	unsigned search_serial = 0;
	bookinf* p = NULL;
	int i = 0;
	char flag = 'N';
	printf("请输入书籍序号:");
	if(scanf("%u", &search_serial) == EOF)
		return FALSE;
	getchar();
	p = book;
	for(i = 0; i < DATEBASE_SIZE; i++)
	{
		if(p->serial == search_serial)
		{
			printf("已找到该书籍，下面是书籍信息");
			NEWLINE;
			PRINT_LINE;
			print_BookInf(p);
			PRINT_LINE;
			return SUCCEED;
		}
		else
			p = p->next;
	}
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
bookinf* search_empty(void)					/*寻找空链表并返回链表指针*/
{
	extern bookinf book[];
	int i = 0;
	while(book[i].occupy != 0 && i < DATEBASE_SIZE)
		i++;
	if(i == DATEBASE_SIZE)
	{
		printf("数据库已满！\n按回车返回主菜单\n");
		getchar();
		return NULL;
	}
	else
		return &book[i];
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////