// To pick up the largest number from any 5 row by 5 column matrix.

#include <stdio.h>

int largest(int *, int);

int main()
{
        int array[5][5]; 
	int i = 0;
        char buf[1000];

	printf("Enter elements of 5x5 matrix");
        while (i < 25) {
                printf("%d:\t", i + 1);

                if (fgets(buf, sizeof buf, stdin) == NULL)
                        continue;
                char *p = buf;
                int n;
                while (sscanf(p, "%d %n", *array + i, &n) == 1) {
                        i++;
                        p += n;
                }
        }
        for (i = 0; i < 5; ++i) {
        	for (int j = 0; j < 5; ++j)
                	printf("%d ", array[i][j]);
		putchar('\n');
	}

	printf("The largest no is %d\n", largest(&array[0][0], 25));

	return 0;
}

int largest(int *p, int size)
{
	int large = *p;
	for (int i = 0; i < size; i++) {
		(large < p[i]) ? (large = p[i]) : 0;
	}
	return large;
}
