#include <stdio.h>
#include <stdlib.h>
int main(void)
{

	int n = 0, i = 0, min = 0, tmp = 0;
	while(scanf(" %d", &n) == 1)
	{
		if(n == 0)
			return 0;
		int* str = ( int*) calloc(n, sizeof(int));
		if(str == NULL)
			return 0;
		memset(str, 0, sizeof(int));
		for(i = 0; i < n; i++)
			scanf(" %d", str + i);
		for(i = 1, min = 0; i < n; i++)
			if(str[i] < str[min])
				min = i;
		tmp = str[min];
		str[min] = str[0];
		str[0] = tmp;
		for(i = 0; i < n; i++)
		{
			if(i > 0)
				printf(" ");
			printf("%d", str[i]);
		}
		printf("\n");
		free(str);
	}
	return 0;
}

