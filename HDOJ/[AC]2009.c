#include <stdio.h>
#include <math.h>
int main(void)
{
	int n = 0, i = 0;
	float a1 = 0, sum = 0;
	while(scanf(" %f %d", &a1, &n) == 2)
	{
		sum = 0;
		for(i = 0; i < n; i++)
		{
			sum += a1;
			a1 = sqrt(a1);
		}
		printf("%.2f\n", sum);
	}
	return 0;
}