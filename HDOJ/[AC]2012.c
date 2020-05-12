#include <stdio.h>
#include <math.h>
int main(void)
{
	int x = 0, y = 0, num = 0, i = 0;
	while(scanf(" %d %d", &x, &y) == 2)
	{
		if(x == 0 && y == 0)
			return 0;
		for(; x <= y; x++)
		{
			num = (x * x + x + 41);
			if(num == 2 || num == 3)
				continue;
			if(num % 6 != 1 && num % 6 != 5)
				goto _sorry;
			for(i = 2; i <= sqrt(num); i++)
				if(num % i == 0)
					goto _sorry;
		}
		printf("OK\n");
		continue;
_sorry:
		printf("Sorry\n");
		continue;
	}
	return 0;
}