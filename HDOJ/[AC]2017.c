#include <stdio.h>
int main(void)
{
	int n = 0, i = 0, count = 0;
	char c = '\0';
	while(scanf(" %d%*c", &n) == 1)
	{
		while(n--)
		{
			for(i = 0; (c = getchar()) != '\n';)
				if(c >= '0' && c <= '9')
					i++;
			printf("%d\n", i);
		}
	}
	return 0;
}