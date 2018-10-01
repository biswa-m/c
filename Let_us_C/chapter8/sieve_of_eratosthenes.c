// Generate prime numbers using sieve of Eratosthenes method.

#include <stdio.h>

int main()
{
	int n;
	printf("Generate prime numbers between 0 - ");
	scanf("%d", &n);

	int num[--n];
	for (int i = 2; i <= n; ++i)
		num[i-2] = i;

	int x = 1;
	while (x < n - 1) {
		if (num[x] != 0) {
			for (int i = x + 1; i < n; ++i)
				(num[i] % num[x]) ? 0 : (num[i] = 0);
		}
		++x;
	}
	for (int i = 0; i < n; ++i)
		(num[i] == 0) ? 0 : printf("%d ", num[i]);
	putchar('\n');

	return 0;
}
