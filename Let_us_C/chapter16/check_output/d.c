#include <stdio.h>

struct s {
	int i;
	struct s *p;
};

int main()
{
	struct s var1, var2;

	var1.i = 100;
	var2.i = 200;
	var1.p = &var2;
	var2.p = &var1;

	printf("\n%d %d", var1.p->i, var2.p->i);
}
