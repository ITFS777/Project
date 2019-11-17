void insert(char *s1, char *s2, char ch)
{
	int i = 0, start = 0;
	char *p1 = NULL;
	char *p2 = NULL;
	p1 = s1;
	p2 = s2;
	while (*p1 != ch)
	{
		p1++;						/*定位到要插入的字符处*/
		start++;					/*将插入偏移量记为start*/
	}
	p1++;
	start++;
	for (i = strlen(s2);*p1 != '\0';i++, p1++)			/*将要插入的字符后的字符串复制到字符串s2后面*/
	{
		*(s2 + i) = *p1;
	}
	for (;*p2 != '\0';start++, p2++)		/*将字符串s2赋值到要插入的字符后面*/
	{
		*(s1 + start) = *p2;
	}
}