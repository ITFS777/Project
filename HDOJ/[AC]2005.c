#include <stdio.h>
int main(void)
{

	int year_p[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int year_r[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	long long int year = 0;
	short int month = 0, day = 0, i = 0, count = 0;
	while(scanf(" %d/%d/%d", &year, &month, &day) == 3)
	{
		count = day;
		if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			for(i = 0; i < month - 1; i++)
				count += year_r[i];
			printf("%d\n", count);
		}
		else
		{
			for(i = 0; i < month - 1; i++)
				count += year_p[i];
			printf("%d\n", count);
		}
	}
	return 0;
}

