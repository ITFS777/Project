#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main(void)
{
	int n = 0, i = 0, j = 0, tmp = 0, loc = 0, min = 0;
	bool btmp = 0;

	while(scanf(" %d", &n) == 1)
	{
		if(n == 0)
			return 0;

		int* str = ( int*) calloc(n, sizeof(int));
		bool* sym = ( bool*) calloc(n, sizeof(bool));

		if(str == NULL || sym == NULL)
			return 0;

		memset(str, 0, sizeof(int));
		memset(sym, 0, sizeof(bool));

		for(i = 0; i<n; i++)
		{
			scanf(" %d", &tmp);
			if(tmp < 0)
			{
				str[i] = -tmp;
				sym[i] = 1;
			}
			else
				str[i] = tmp;
		}

		for(i = 0, loc = n; i < n; i++, loc--)
		{
			for(j = 0, min = 0; j < loc; j++)
			{
				if(str[j] < str[min])
					min = j;
			}

			tmp = str[min];
			str[min] = str[loc - 1];
			str[loc - 1] = tmp;

			btmp = sym[min];
			sym[min] = sym[loc - 1];
			sym[loc - 1] = btmp;
		}

		for(i = 0; i<n; i++)
		{
			if(i > 0)
				printf(" ");
			if(sym[i] == 1)
				printf("%d", -str[i]);
			else
				printf("%d", str[i]);
		}

		printf("\n");

		free(str);
		free(sym);
	}
	return 0;
}