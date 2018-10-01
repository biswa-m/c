// To find the smallest number in an array using pointers

#include <stdio.h>

#define SIZE 10

int smallest(int *, int);

int main()
{
        int array[SIZE], i = 0;
        char buf[1000];

        while (i < SIZE) {
                printf("%d:\t", i + 1);

                if (fgets(buf, sizeof buf, stdin) == NULL)
                        continue;
                char *p = buf;
                int n;
                while (sscanf(p, "%d %n", &array[i], &n) == 1) {
                        i++;
                        p += n;
                }
        }
        for (i = 0; i < SIZE; ++i)
                printf("%d ", array[i]);

	printf("The smallest no is %d\n", smallest(array, SIZE));

	return 0;
}

int smallest(int *p, int size)
{
	int small = *p;
	for (int i = 0; i < size; i++) {
		(small > p[i]) ? (small = p[i]) : 0;
	}
	return small;
}	
