#include <stdio.h>
#include <math.h>
int main(void)
{
	float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	while(scanf(" %f %f %f %f", &x1, &y1, &x2, &y2) == 4)
		printf("%.2f\n", sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
	return 0;
}