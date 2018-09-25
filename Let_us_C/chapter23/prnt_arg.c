// To print comand line arguements that it receives

#include <stdio.h>

int main(int argc, char *argv[])
{
	for (int i = 0; i < argc; ++i)
		printf("%s ", argv[i]);
	putchar('\n');

	return 0;
}
