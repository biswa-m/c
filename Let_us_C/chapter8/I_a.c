// Copy contents of an array in reverse order

#include <stdio.h>

#define SIZE 10

int main()
{
	int array[SIZE], i = 0; 
        char buf[1000]; 
 
        while (i < SIZE) { 
                printf("%d:\t", i + 1); 
         
                if (fgets(buf, sizeof(buf), stdin) == NULL) 
                        continue; 
                char *p = buf; 
                int n; 
                while (sscanf(p, "%d %n", &array[i], &n) == 1) { 
                        i++; 
                        p += n; 
                }        
        } 
	puts("The array is ");
	for (i = 0; i < SIZE; ++i)
		printf("%d ", array[i]);

	int len = sizeof(array) / sizeof(*array);
	int rev[len];
	for (i = 0; i < len; ++i)
		rev[i] = array[len - i - 1];

	putchar('\n');
	puts("The reversed array is ");
	for (i = 0; i < len; ++i)
		printf("%d ", rev[i]);
	putchar('\n');

	return 0;
}
