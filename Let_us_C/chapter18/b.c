#include <stdio.h>

int main()
{
	int i = 2;
	float f = 2.5367;
	char str[ ] = "Life is like that";

	printf("%4d\t%3.3f\t0\t%4s\n", i, f, str);
	printf("%d\t%.3f\t0\t%s\n", i, f, str);
	printf("%-6.3f%4d\t%5s\n", f, i, str);
	printf("%.3f\t%d\t%s\n", f, i, str);

	return 0;
}
