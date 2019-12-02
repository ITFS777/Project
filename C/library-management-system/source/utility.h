#pragma once
int get_menu_choice(void);
int get_search_choice(void);
int get_add_choice(void);
int get_del_choice(void);
void choice_judge(const int flag);
void search_judge(const int flag);
void print_progress(const int i);
#define DEBUG 1
#define PRINT_LINE printf("********************************************************************\n")
#define NEWLINE printf("\n")
#define PRINT_CHOICE printf("«Î ‰»Î≤Àµ•–Ú∫≈:")
#define TRUE 1
#define FALSE 0
#define SUCCEED 1
#define CLS system("CLS")
#define LINE --------------------------------------------------------------------------------------------
