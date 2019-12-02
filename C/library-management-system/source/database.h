#pragma once
#include<stdbool.h>
void link_initialize(void);
void print_BookInf(const struct bookinf* p);
void book_add(void);
int book_del(void);
int book_del_serial(void);
void datebase_add(const	struct bookinf* p);
int datebase_reload(void);
int datebase_save(void);
void print_allbook(void);
#define LEN_NAME 128
#define LEN_AUTHER 128
#define LEN_PUBLISHER 128
#define DATEBASE_SIZE 100
#define DATEBASE_FILENAME "datebase.txt"
typedef struct timeinf
{
	unsigned year;
	unsigned short month;
	unsigned short day;
}timeinf;
/////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct bookinf
{
	char name[LEN_NAME];
	char auther[LEN_AUTHER];
	char publisher[LEN_PUBLISHER];
	unsigned int serial;
	int page;
	timeinf time_pub;
	timeinf time_in;
	struct bookinf* next;
	bool occupy;
}bookinf;