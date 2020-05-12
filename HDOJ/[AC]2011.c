#include <stdio.h>
#include <math.h>
int main(void)
{
	int i = 0, m = 0, n = 0, count = 0;
	double sub = 0;
	while(scanf(" %d", &m) == 1)
	{
		for(count = 0; count < m; count++)
		{
			sub = 0;
			scanf(" %d", &n);
			for(i = 1; i <= n; i++)
			{
				sub += 1.0/i * pow(-1, i + 1);
			}
			printf("%.2lf\n", sub);
		}
		
	}
	return 0;
}