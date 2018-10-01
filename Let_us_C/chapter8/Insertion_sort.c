// Insertion Sort

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

	// insertion sort
	int tmp, flag, n;
	for (int i = 1; i < SIZE; ++i) {
		printf("\nIteration %d, checking %d\n",
				i + 1, array[i]);
		flag = 0;
		for (int j = 0; j < i; ++j) {

			if (flag == 0 && (array[i] < array[j])) {
				flag = 1;
				tmp = array[i];
				n = i;
				
				printf("Inserting %d before %d\n",
						array[i], array[j]);
			}
			if (flag == 1)
				array[n--] = array[n - 1];
		} 
		(flag == 1) ? (array[n] = tmp) : 0;

		for (int i = 0; i < SIZE; ++i)
			printf("%d ", array[i]);
		putchar('\n');
		getchar();
	}
	return 0;
}
