/* Twenty-five numbers are entered from the keyboard into anarray. 
 * The number to be searched is entered through the keyboard by the 
 * user. Write a program to find if the number to be searched is 
 * present in the array and if it is present, display the number of 
 * times it appears in the array.
 */

#include <stdio.h>

#define SIZE 25

int main()
{       
	printf("Enter %d no.s\n", SIZE); 
 
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

	int find, n = 0;
	printf("Enter a no. to check it's no. of appearance\n");
	scanf(" %d", &find);

	for (int i = 0; i < 25; ++i) 
		(array[i] == find) ? ++n : 1;

	if (n != 0)
		printf("The no %d occured %d times\n", find, n);
	else
		printf("The no %d is not present\n", find);

	return 0;	
}
