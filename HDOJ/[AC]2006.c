#include <stdio.h>
int main(void)
{
	int count = 0, tmp = 0, pro = 1, i = 0;
	while(scanf("%d", &count) == 1)
	{
		for(i = 0; i < count; i++)
		{
			scanf(" %d", &tmp);
			if(tmp % 2 == 1)
				pro *= tmp;
		}
		printf("%d\n", pro);
		pro = 1;
	}
	return 0;
}