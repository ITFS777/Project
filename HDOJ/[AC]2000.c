#include <stdio.h>
#include <string.h>
int main(void)
{
	char a = '0', b = '0', c = '0';
	while (scanf(" %c%c%c", &a, &b, &c) == 3)
	{
		if(a < b && a < c)
		{
			if(b < c)
				printf("%c %c %c\n", a, b, c);
			else
				printf("%c %c %c\n", a, c, b);
		}
		else if(b < a && b < c)
		{
			if(a < c)
				printf("%c %c %c\n", b, a, c);
			else
				printf("%c %c %c\n", b, c, a);
		}
		else
		{
			if(a < b)
				printf("%c %c %c\n", c, a, b);
			else
				printf("%c %c %c\n", c, b, a);
		}
	}
	return 0;
}