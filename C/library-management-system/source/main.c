#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"menu.h"
#include"database.h"
#include"utility.h"
#include"search.h"
#include "log.h"
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	int flag = 0;
/*--------------------LOG--------------------*/
#if LOG

	log_system_open();
#endif
/*++++++++++++++++++++LOG++++++++++++++++++++*/
	printf("正在进行初始化...\n");
	link_initialize();
	FILE* FileName = NULL;
	FileName = fopen(DATEBASE_FILENAME, "a+");
	flag = datebase_reload();
	if(flag == SUCCEED)
		printf("初始化完成！\n按回车返回主菜单");
	else
	{
		printf("初始化失败！");
		exit(0);
	}
	CLS;
	while(1)
	{
		menu();

	}
/*--------------------LOG--------------------*/
#if LOG

	log_system_close();

#endif
/*++++++++++++++++++++LOG++++++++++++++++++++*/
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////