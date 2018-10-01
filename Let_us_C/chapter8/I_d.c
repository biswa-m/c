/* To perform the following tasks
 * 	- initialize an integer array of 10 elements in main( )
 * 	- pass the entire array to a function modify( )
 * 	- in modify( ) multiply each element of array by 3
 * 	- return the control to main( ) and print the new array
 * 	elements in main( )
 */

#include <stdio.h>

void modify(int *, int);

int main()
{
	int array[10] = {2, 1, 5, 0, 12, 4, 23, 5, 23, 5};
	
	modify(array, 10);

	for (int i = 0; i < 10; ++i)
		printf("%d ", array[i]);
	putchar('\n');
}

void modify(int *p, int size)
{
	for (int i = 0; i < size; ++i)
		p[i] *= 3;
	return;
}
