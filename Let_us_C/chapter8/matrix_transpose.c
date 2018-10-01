// Transpose Matrix

#include <stdio.h>

void transpose(int *, int);
int main()
{
	int row = 6, col = 6;
	int i = 0;
        char buf[1000];

	int array[row][col];
	printf("Enter elements of %dx%d matrix", row, col);
        while (i < (row * col)) {
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
	for (i = 0; i < row; ++i) {
        	for (int j = 0; j < col; ++j)
                	printf("%3d ", array[i][j]);
		putchar('\n');
	}
	
	if (row != col)
		return 1;
	transpose(*array, row);

	puts("The transposed matrix is");
        for (i = 0; i < row; ++i) {
        	for (int j = 0; j < col; ++j)
                	printf("%3d ", array[i][j]);
		putchar('\n');
	}
	
	return 0;
}
void transpose(int *ptr, int n)
{
	int tmp;
	for (int i = 0; i < n - 1; ++i)
		for (int j = i+1; j < n; ++j) {
			tmp = *(ptr + (n * i) + j);
			*(ptr + (n * i) + j) = *(ptr + (n * j) + i);
			*(ptr + (n * j) + i) = tmp;
		}

}
