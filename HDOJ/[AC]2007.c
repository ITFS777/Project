#include <stdio.h>
int main(void)
{
	int m = 0, n = 0, x = 0, y = 0, i = 0;
	while(scanf(" %d %d", &m, &n) == 2)
	{
		x = 0;
		y = 0;
		if(m > n)
		{
			m ^= n;
			n ^= m;
			m ^= n;
		}
		for(i = m; i <= n; i++)
		{
			if((i & 1) == 0)
				x += i * i;
			else
				y += i * i * i;
		}
		printf("%d %d\n",x,y);
	}
	return 0;
}

