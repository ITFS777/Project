#include<stdio.h>
#include<string.h>
#include<windows.h>
#include"utility.h"
#include"database.h"
#include "log.h"
#include "search.h"
/////////////////////////////////////////////////////////////////////////////////////////////////
bookinf book[DATEBASE_SIZE];
/////////////////////////////////////////////////////////////////////////////////////////////////
void link_initialize(void)
{
	extern bookinf book[];
	int i = 0;
	memset(book[DATEBASE_SIZE - 1].name, '\0', LEN_NAME);
	memset(book[DATEBASE_SIZE - 1].auther, '\0', LEN_AUTHER);
	memset(book[DATEBASE_SIZE - 1].publisher, '\0', LEN_PUBLISHER);
	book[DATEBASE_SIZE - 1].page = 0;
	book[DATEBASE_SIZE - 1].next = NULL;
	book[DATEBASE_SIZE - 1].serial = DATEBASE_SIZE;
	book[DATEBASE_SIZE - 1].occupy = 0;
	book[DATEBASE_SIZE - 1].time_in.year = 0;
	book[DATEBASE_SIZE - 1].time_in.month = 0;
	book[DATEBASE_SIZE - 1].time_in.day = 0;
	book[DATEBASE_SIZE - 1].time_pub.year = 0;
	book[DATEBASE_SIZE - 1].time_pub.month = 0;
	book[DATEBASE_SIZE - 1].time_pub.day = 0;
	for(i = 0; i < DATEBASE_SIZE - 1; i++)
	{
		memset(book[i].name, '\0', LEN_NAME);
		memset(book[i].auther, '\0', LEN_AUTHER);
		memset(book[i].publisher, '\0', LEN_PUBLISHER);
		book[i].page = 0;
		book[i].serial = (i + 1);
		book[i].occupy = 0;
		book[i].time_in.year = 0;
		book[i].time_in.month = 0;
		book[i].time_in.day = 0;
		book[i].time_pub.year = 0;
		book[i].time_pub.month = 0;
		book[i].time_pub.day = 0;
		book[i].next = &book[i + 1];
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void print_BookInf(const struct bookinf* p)
{
	printf("书籍名称:《%s》\n", p->name);
	printf("作者名称: %s\n", p->auther);
	printf("出版社:   %s\n", p->publisher);
	printf("图书编号: %d\n", p->serial);
	printf("页数:     共%d页\n", p->page);
	printf("出版日期: %d年%d月%d日\n", p->time_pub.year, p->time_pub.month, p->time_pub.day);
	printf("入库日期: %d年%d月%d日\n", p->time_in.year, p->time_in.month, p->time_in.day);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void book_add(void)
{
	CLS;
	bookinf* p = NULL;
	int i = 0;
	unsigned year = 0;
	unsigned short month = 0;
	unsigned short day = 0;
	if((p = search_empty()) == NULL)
		return;
	printf("请完善书籍信息，名称中间不得出现空格！\n");
	PRINT_LINE;
	printf("请输入书籍名称:");
	gets(p->name);
	printf("请输入作者名称:");
	gets(p->auther);
	printf("请输入出版社名称:");
	gets(p->publisher);
	printf("请输入页码:");
	scanf("%d", &(p->page));
	printf("请输入入库日期，格式为 YYYY.MM.DD\n");
	scanf("%u.%hu.%hu", &year, &month, &day);
	p->time_in.year = year;
	p->time_in.month = month;
	p->time_in.day = day;
	printf("请输入出版日期，格式为 YYYY.MM.DD\n");
	scanf("%u.%hu.%hu", &year, &month, &day);
	p->time_pub.year = year;
	p->time_pub.month = month;
	p->time_pub.day = day;
	p->occupy = 1;
	datebase_add(p);
	PRINT_LINE;
	printf("添加成功！\n按回车返回主菜单");
	getchar();
	getchar();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int book_del(void)
{
	extern bookinf book[];
	CLS;
	char search_name[LEN_NAME] = { '\0' };
	bookinf* p = NULL;
	int i = 0;
	char flag = 'N';
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
			printf("确认删除该书籍吗？(Y\\N)\n");
			flag = getchar();
			if(flag == 'Y')
			{
				printf("正在删除该书籍...\n");

/*--------------------LOG--------------------*/
#if LOG

				log_datebase_del(p);

#endif
/*++++++++++++++++++++LOG++++++++++++++++++++*/

				memset(p->name, '\0', LEN_NAME);

/*--------------------DEBUG--------------------*/
#if DEBUG

				print_progress(20);

#endif
/*--------------------DEBUG--------------------*/

				memset(p->auther, '\0', LEN_AUTHER);

/*++++++++++++++++++++DEBUG++++++++++++++++++++*/
#if DEBUG

				print_progress(40);

#endif
/*--------------------DEBUG--------------------*/

				memset(p->publisher, '\0', LEN_PUBLISHER);

/*++++++++++++++++++++DEBUG++++++++++++++++++++*/
#if DEBUG

				print_progress(60);

#endif
/*++++++++++++++++++++DEBUG++++++++++++++++++++*/

				p->page = 0;

/*--------------------DEBUG--------------------*/
#if DEBUG

				print_progress(80);

#endif
/*++++++++++++++++++++DEBUG++++++++++++++++++++*/

				p->time_in.year = 0;
				p->time_in.month = 0;
				p->time_in.day = 0;
				p->time_pub.year = 0;
				p->time_pub.month = 0;
				p->time_pub.day = 0;
				p->occupy = 0;

/*--------------------DEBUG--------------------*/
#if DEBUG

				print_progress(100);
				printf("\n");

#endif
/*++++++++++++++++++++DEBUG++++++++++++++++++++*/

				printf("书籍已删除！\n");
				flag = datebase_save();
				printf("正在更新数据库...\n");
				if(flag == ERROR)
				{
					printf("更新失败！\n按回车返回主菜单");
					getchar();
					return SUCCEED;
				}
				printf("更新完成！按回车返回主菜单\n");
				getchar();
				return SUCCEED;
			}
			else
				getchar();
			return SUCCEED;
		}
		else
			p = p->next;
	}
	return FALSE;				/*未查询到该书籍*/
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int book_del_serial(void)
{
	extern bookinf book[];
	CLS;
	unsigned search_serial = 0;
	bookinf* p = book;
	int i = 0;
	char flag = 'N';
	printf("请输入书籍序号:");
	if(scanf("%u", &search_serial) == EOF)
		return FALSE;
	getchar();
	for(i = 0; i < DATEBASE_SIZE; i++)
	{
		if(p->serial == search_serial)
		{
			printf("已找到该书籍，下面是书籍信息");
			NEWLINE;
			PRINT_LINE;
			print_BookInf(p);
			PRINT_LINE;
			printf("确认删除该书籍吗？(Y\\N)\n");
			flag = getchar();
			if(flag == 'Y')
			{
				printf("正在删除该书籍...\n");

/*--------------------LOG--------------------*/
#if LOG

				log_datebase_del(p);

#endif
/*++++++++++++++++++++LOG++++++++++++++++++++*/

				memset(p->name, '\0', LEN_NAME);

/*--------------------DEBUG--------------------*/
#if DEBUG

				print_progress(20);

#endif
/*--------------------DEBUG--------------------*/

				memset(p->auther, '\0', LEN_AUTHER);

/*++++++++++++++++++++DEBUG++++++++++++++++++++*/
#if DEBUG

				print_progress(40);

#endif
/*--------------------DEBUG--------------------*/

				memset(p->publisher, '\0', LEN_PUBLISHER);

/*++++++++++++++++++++DEBUG++++++++++++++++++++*/
#if DEBUG

				print_progress(60);

#endif
/*++++++++++++++++++++DEBUG++++++++++++++++++++*/

				p->page = 0;

/*--------------------DEBUG--------------------*/
#if DEBUG

				print_progress(80);

#endif
/*++++++++++++++++++++DEBUG++++++++++++++++++++*/

				p->time_in.year = 0;
				p->time_in.month = 0;
				p->time_in.day = 0;
				p->time_pub.year = 0;
				p->time_pub.month = 0;
				p->time_pub.day = 0;
				p->occupy = 0;

/*--------------------DEBUG--------------------*/
#if DEBUG

				print_progress(100);
				printf("\n");

#endif
/*++++++++++++++++++++DEBUG++++++++++++++++++++*/

				printf("书籍已删除！\n");
				printf("正在更新数据库...\n");
				flag = datebase_save();
				if(flag == ERROR)
				{
					printf("更新失败！\n按回车返回主菜单");
					getchar();
					return SUCCEED;
				}
				printf("更新完成！按回车返回主菜单\n");
				getchar();
				return SUCCEED;
			}
			else
				getchar();
			return SUCCEED;
		}
		else
			p = p->next;
	}
	return FALSE;				/*未查询到该书籍*/
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void datebase_add(const bookinf* p)
{
	FILE* datebase = NULL;
	datebase = fopen(DATEBASE_FILENAME, "a");
	int i = 0;
	char name[LEN_NAME] = { '\0' };
	char auther[LEN_AUTHER] = { '\0' };
	char publisher[LEN_PUBLISHER] = { '\0' };
	strncpy(name, p->name, LEN_NAME);
	strncpy(auther, p->auther, LEN_AUTHER);
	strncpy(publisher, p->publisher, LEN_PUBLISHER);
	for(i = 0; i < LEN_NAME; i++)
	{
		if(name[i] == ' ')
			name[i] = '-';
	}
	for(i = 0; i < LEN_AUTHER; i++)
	{
		if(auther[i] == ' ')
			auther[i] = '-';
	}
	for(i = 0; i < LEN_PUBLISHER; i++)
	{
		if(publisher[i] == ' ')
			publisher[i] = '-';
	}
	fprintf(datebase, "name:%s\n", name);
	fprintf(datebase, "auther:%s\n", auther);
	fprintf(datebase, "publisher:%s\n", publisher);
	fprintf(datebase, "page:%d\n", p->page);
	fprintf(datebase, "time_in:%u.%hu.%hu\n", p->time_in.year, p->time_in.month, p->time_in.day);
	fprintf(datebase, "time_pub:%u.%hu.%hu\n", p->time_pub.year, p->time_pub.month, p->time_pub.day);
	fclose(datebase);
	datebase = NULL;

/*--------------------LOG--------------------*/
#if LOG

	log_datebase_add(p);

#endif 
/*++++++++++++++++++++LOG++++++++++++++++++++*/

}
/////////////////////////////////////////////////////////////////////////////////////////////////
int datebase_reload(void)
{
	extern bookinf book[];
	int flag = 1;
	int i = 0;
	bookinf* p = book;
	FILE* FileName = fopen(DATEBASE_FILENAME, "r");
	char name[LEN_NAME] = { '\0' };
	char auther[LEN_AUTHER] = { '\0' };
	char publisher[LEN_PUBLISHER] = { '\0' };
	while(flag != 0)
	{
		flag = fscanf(FileName, "name:%s\n", &name);
		if(flag == EOF)
			break;
		fscanf(FileName, "auther:%s\n", &auther);
		fscanf(FileName, "publisher:%s\n", &publisher);
		fscanf(FileName, "page:%d\n", &(p->page));
		fscanf(FileName, "time_in:%u.%hu.%hu\n", &(p->time_in.year), &(p->time_in.month), &(p->time_in.day));
		fscanf(FileName, "time_pub:%u.%hu.%hu\n", &(p->time_pub.year), &(p->time_pub.month), &(p->time_pub.day));
		p->occupy = 1;
		for(i = 0; i < LEN_NAME; i++)
		{
			if(name[i] == '-')
				name[i] = ' ';
		}
		for(i = 0; i < LEN_AUTHER; i++)
		{
			if(auther[i] == '-')
				auther[i] = ' ';
		}
		for(i = 0; i < LEN_PUBLISHER; i++)
		{
			if(publisher[i] == '-')
				publisher[i] = ' ';
		}
		strncpy(p->name, name, LEN_NAME);
		strncpy(p->auther, auther, LEN_AUTHER);
		strncpy(p->publisher, publisher, LEN_PUBLISHER);
		if(p->serial != DATEBASE_SIZE)
			p = p->next;
		else
			break;
	}
	fclose(FileName);
	FileName = NULL;
	p = NULL;

/*--------------------LOG--------------------*/
#if LOG

	log_datebase_load();

#endif
/*++++++++++++++++++++LOG++++++++++++++++++++*/

	return SUCCEED;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int datebase_save(void)
{
	extern bookinf book[];
	bookinf* p = book;
	FILE* FileName = fopen(DATEBASE_FILENAME, "w");

_save:
	if(p->occupy == 1)
	{
		int i = 0;
		int flag = 1;
		char name[LEN_NAME] = { '\0' };
		char auther[LEN_AUTHER] = { '\0' };
		char publisher[LEN_PUBLISHER] = { '\0' };
		strncpy(name, p->name, LEN_NAME);
		strncpy(auther, p->auther, LEN_AUTHER);
		strncpy(publisher, p->publisher, LEN_PUBLISHER);
		for(i = 0; i < LEN_NAME; i++)
		{
			if(name[i] == ' ')
				name[i] = '-';
		}
		for(i = 0; i < LEN_AUTHER; i++)
		{
			if(auther[i] == ' ')
				auther[i] = '-';
		}
		for(i = 0; i < LEN_PUBLISHER; i++)
		{
			if(publisher[i] == ' ')
				publisher[i] = '-';
		}
		flag = fprintf(FileName, "name:%s\n", name);
		if(flag == EOF)
			goto _error;
		fprintf(FileName, "auther:%s\n", auther);
		fprintf(FileName, "publisher:%s\n", publisher);
		fprintf(FileName, "page:%d\n", p->page);
		fprintf(FileName, "time_in:%d.%d.%d\n", p->time_in.year, p->time_in.month, p->time_in.day);
		fprintf(FileName, "time_pub:%d.%d.%d\n", p->time_pub.year, p->time_pub.month, p->time_pub.day);
	}
	if(p->serial < DATEBASE_SIZE)
	{
		p = p->next;
		goto _save;
	}

	fclose(FileName);
	p = NULL;
	FileName = NULL;

/*--------------------LOG--------------------*/
#if LOG

	log_datebase_save();

#endif
/*++++++++++++++++++++LOG++++++++++++++++++++*/

	return SUCCEED;
_error:
	return ERROR;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void print_allbook(void)
{
	extern bookinf book[];
	CLS;
	bookinf* p = book;
	PRINT_LINE;
	for(; p->serial < DATEBASE_SIZE; p = p->next)
		if(p->occupy == 1)
			printf("<%d>《%s》\t作者:%s\t出版社:%s\t页数:%d\t入库时间:%u.%hu.%hu\n", p->serial, p->name, p->auther, p->publisher, p->page, p->time_in.year, p->time_in.month, p->time_in.day);
	PRINT_LINE;
	printf("按回车返回主菜单\n");
	getchar();
}
/////////////////////////////////////////////////////////////////////////////////////////////////