#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	short int n = 0, i = 0, max = 0, min = 100, maxp = 0, minp = 0, sub = 0;
	while(scanf(" %hd", &n) == 1 || n <= 2)
	{
		short int* str = ( short int*) calloc(n, sizeof(short int));
		if(str == NULL)
			return 0;
		memset(str, ( short int) 0, sizeof(short int));
		for(i = 0, max = 0, min = 100, sub = 0; i < n; i++)
		{
			scanf(" %hd", str + i);
			if(max <= *(str + i))
			{
				max = *(str + i);
				maxp = i;
			}
			if(*(str + i) <= min)
			{
				min = *(str + i);
				minp = i;
			}
			sub += *(str + i);
		}
		sub -= *(str + maxp);
		sub -= *(str + minp);
		printf("%.2f\n", sub / (n - 2.0));
		free(str);
	}
	return 0;
}