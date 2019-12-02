#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "database.h"
#include "utility.h"
#include "search.h"
#include "log.h"
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
char* get_time(void)
{
	time_t* ptm = ( time_t*) malloc(sizeof(long long));
	if(ptm == NULL)
		return NULL;
	time(ptm);
	struct tm* tmpt = localtime(ptm);
	free(ptm);
	ptm = NULL;
	return asctime(tmpt);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void log_datebase_add(const bookinf* p)
{
	FILE* FileName = fopen(LOG_FILENAME, "a");
	fprintf(FileName, "------------------------LOG------------------------\n");
	fprintf(FileName, "\n");
	if(get_time() == NULL)
		fprintf(FileName, "TIME ERROR\n");
	else
		fprintf(FileName, "%s", get_time());
	fprintf(FileName, "INFO: DATEBASE ADD\n");
	fprintf(FileName, "BOOK INFORMATION:\n");
	fprintf(FileName, "name:%s\n", p->name);
	fprintf(FileName, "auther:%s\n", p->auther);
	fprintf(FileName, "publisher:%s\n", p->publisher);
	fprintf(FileName, "page:%d\n", p->page);
	fprintf(FileName, "time_in:%d.%d.%d\n", p->time_in.year, p->time_in.month, p->time_in.day);
	fprintf(FileName, "time_pub:%d.%d.%d\n", p->time_pub.year, p->time_pub.month, p->time_pub.day);
	fprintf(FileName, "\n");
	fprintf(FileName, "------------------------END------------------------\n");
	fprintf(FileName, "\n");
	fclose(FileName);
	FileName = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void log_datebase_del(const bookinf* p)
{
	FILE* FileName = fopen(LOG_FILENAME, "a");
	fprintf(FileName, "------------------------LOG------------------------\n");
	fprintf(FileName, "\n");
	if(get_time() == NULL)
		fprintf(FileName, "TIME ERROR\n");
	else
		fprintf(FileName, "%s", get_time());
	fprintf(FileName, "INFO: DATEBASE DEL\n");
	fprintf(FileName, "BOOK INFORMATION:\n");
	fprintf(FileName, "name:%s\n", p->name);
	fprintf(FileName, "auther:%s\n", p->auther);
	fprintf(FileName, "publisher:%s\n", p->publisher);
	fprintf(FileName, "page:%d\n", p->page);
	fprintf(FileName, "time_in:%d.%d.%d\n", p->time_in.year, p->time_in.month, p->time_in.day);
	fprintf(FileName, "time_pub:%d.%d.%d\n", p->time_pub.year, p->time_pub.month, p->time_pub.day);
	fprintf(FileName, "\n");
	fprintf(FileName, "------------------------END------------------------\n");
	fprintf(FileName, "\n");
	fclose(FileName);
	FileName = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void log_datebase_save(void)
{
	FILE* FileName = fopen(LOG_FILENAME, "a");
	fprintf(FileName, "------------------------LOG------------------------\n");
	fprintf(FileName, "\n");
	if(get_time() == NULL)
		fprintf(FileName, "TIME ERROR\n");
	else
		fprintf(FileName, "%s", get_time());
	fprintf(FileName, "INFO: DATEBASE SAVE\n");
	fprintf(FileName, "\n");
	fprintf(FileName, "------------------------END------------------------\n");
	fprintf(FileName, "\n");
	fclose(FileName);
	FileName = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void log_datebase_load(void)
{
	FILE* FileName = fopen(LOG_FILENAME, "a");
	fprintf(FileName, "------------------------LOG------------------------\n");
	fprintf(FileName, "\n");
	if(get_time() == NULL)
		fprintf(FileName, "TIME ERROR\n");
	else
		fprintf(FileName, "%s", get_time());
	fprintf(FileName, "INFO: DATEBASE LOAD\n");
	fprintf(FileName, "\n");
	fprintf(FileName, "------------------------END------------------------\n");
	fprintf(FileName, "\n");
	fclose(FileName);
	FileName = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void log_system_open(void)
{
	FILE* FileName = fopen(LOG_FILENAME, "a");
	fprintf(FileName, "------------------------LOG------------------------\n");
	fprintf(FileName, "\n");
	if(get_time() == NULL)
		fprintf(FileName, "TIME ERROR\n");
	else
		fprintf(FileName, "%s", get_time());
	fprintf(FileName, "INFO: SYSTEM OPENED\n");
	fprintf(FileName, "\n");
	fprintf(FileName, "------------------------END------------------------\n");
	fprintf(FileName, "\n");
	fclose(FileName);
	FileName = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void log_system_close(void)
{
	FILE* FileName = fopen(LOG_FILENAME, "a");
	fprintf(FileName, "------------------------LOG------------------------\n");
	fprintf(FileName, "\n");
	if(get_time() == NULL)
		fprintf(FileName, "TIME ERROR\n");
	else
		fprintf(FileName, "%s", get_time());
	fprintf(FileName, "INFO: SYSTEM CLOSED\n");
	fprintf(FileName, "\n");
	fprintf(FileName, "------------------------END------------------------\n");
	fprintf(FileName, "\n");
	fclose(FileName);
	FileName = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void log_update()
{
	CLS;
	PRINT_LINE;
	printf("**                   Version 2.0版本更新介绍                      **\n");
	PRINT_LINE;
	NEWLINE;
	printf("2019/8/17.数据库容量扩大至100本\n");
	printf("2019/8/17.书籍名称、作者名称和出版社名称现在可以使用中文和空格了\n");
	printf("2019/8/17.新增了使用序号查询书籍和删除书籍功能\n");
	printf("2019/9/2.修复了一些BUG\n");
	NEWLINE;
	printf("按回车返回主菜单");
	getchar();
}
/////////////////////////////////////////////////////////////////////////////////////////////////