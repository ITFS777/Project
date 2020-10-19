#include <stdio.h>
int main(void)
{
	int m = 0, n = 0, tmp = 0, sub = 0, digit = 0, count = 0;
	while(scanf(" %d %d", &m, &n) == 2)
	{
		for(count = 0; m <= n; m++)
		{
			tmp = m;
			sub = 0;
			digit = 0;
			if(tmp < 10)
			{
				if(count > 0)
					printf(" ");
				printf("%d", tmp);
				count++;
				continue;
			}
			while(tmp != 0)
			{
				digit = tmp % 10;
				sub += digit * digit * digit;
				tmp /= 10;
			}
			if(sub == m)
			{
				if(count > 0)
					printf(" ");
				printf("%d", m);
				count++;
			}
		}
		if(count == 0)
			printf("no\n");
		else
			printf("\n");
	}
	return 0;
}