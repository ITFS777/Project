#include <stdio.h>
int main(void)
{
	double num = 0;
	while(scanf(" %lf", &num) == 1)
	{
		if(num < 0)
			printf("%.2f\n", -num);
		else
			printf("%.2f\n", num);
	}
	return 0;
}