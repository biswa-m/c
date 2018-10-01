//Bubble Sort

#include <stdio.h>

#define SIZE 5 

int main()
{
        printf("Enter %d no.s\n", SIZE); 
 
        int array[SIZE], i = 0; 
        char buf[512]; 
 
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
	printf("\nArray before sorting\n");
	for (int i = 0; i < SIZE; ++i)
		printf("%d ", array[i]);
	putchar('\n');

	// Bubble sort
	int tmp;
	for (int i = 0; i < SIZE - 1; ++i) {
		for (int j = 0; j < SIZE - i -1; ++j) {
			printf("\nIteration %d, checking %d and %d\n",
				i + 1, array[j], array[j + 1]);

			if (array[j] > array[j + 1]) {
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			for (int i = 0; i < SIZE; ++i)
				printf("%d ", array[i]);
			putchar('\n');
			getchar();
		} 
	}
	return 0;
}
