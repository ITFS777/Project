#include <stdio.h>
int main(void)
{
	int t = 0;
	while(scanf(" %d", &t) == 1)
	{
		if(t >= 0 && t < 60)
			printf("E\n");
		else if(t >= 60 && t < 70)
			printf("D\n");
		else if(t >= 70 && t < 80)
			printf("C\n");
		else if(t >= 80 && t < 90)
			printf("B\n");
		else if(t >= 90 && t <= 100)
			printf("A\n");
		else
			printf("Score is error!\n");
	}
	return 0;
}