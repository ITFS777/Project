#include <stdio.h>
#include <stdbool.h>
int main(void)
{
	int n = 0, i = 0, m = 0;
	bool flag = 0;
	while(scanf(" %d %d", &n, &m) == 2)
	{
		if(m == 0 && n == 0)
			return 0;
		int* str = ( int*) calloc(n, sizeof(int));
		if(str == NULL)
			return 0;
		memset(str, 0, sizeof(int));
		for(i = 0; i < n; i++)
			scanf(" %d", str + i);
		for(i = 0, flag = 0; i < n; i++)
		{
			if(i > 0)
				printf(" ");
			if(str[i] >= m && flag == 0)
			{
				printf("%d ", m);
				flag = 1;
			}
			printf("%d", str[i]);
			if(i == n - 1 && flag == 0)
				printf(" %d", m);
		}
		printf("\n");
		free(str);
	}
	return 0;
}