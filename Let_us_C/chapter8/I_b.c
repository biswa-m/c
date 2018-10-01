// Check if the array is pelindrom

#include <stdio.h>

#define SIZE 6

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

	int pel = 1;
	for (i = 0; i < (SIZE / 2); ++i) {
		if (array[i] == array[SIZE - i - 1]) {
			continue;
		} else {
			pel = 0;
			break;
		}
	}
	pel ? printf("\nPelindrom\n"): printf("\nNot Pelindrom\n");

	return 0;
}
