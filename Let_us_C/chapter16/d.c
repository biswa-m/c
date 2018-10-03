/* A record contains name of cricketer, his age, number of test
 * matches that he has played and the average runs that he has
 * scored in each test match. Create an array of structure to hold
 * records of 20 such cricketer and then write a program to read
 * these records and arrange them in ascending order by average
 * runs. Use the qusort( ) standard library function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct player {
	char name[50];
	int age;
	int match;
	float average;
};

int cmpfunc (const void *, const void *);
void random_data(struct player *, int);
void display(struct player *, int);

int main()
{
	int size = 20;
	struct player cricket[20];

	random_data(&cricket[0], size);
	display(&cricket[0], size);

	qsort(cricket, size, sizeof(struct player), cmpfunc);

	puts("\nAfter sorting by average runs");
	display(&cricket[0], size);
}

int cmpfunc (const void *a, const void *b)
{
	struct player *ia = (struct player *)a;
	struct player *ib = (struct player *)b;
	return (int) (100.0f * ia->average - (100.0f) * ib->average) ;
}

void random_data(struct player *cr, int lim)
{
	int len;
	for (int i = 0; i < lim; ++i) {
		len = (rand() % 16) + 5;
		char ch[len + 1];
		for (int j = 0; j < len; ++j)
			ch[j] =	(rand() % ('Z' - 'A' + 1)) + 'A';
		ch[(rand() % (len - len/4 +1)) + len/4] = ' ';
		ch[len] = '\0';
		strcpy(cr[i].name, ch);

		cr[i].age = (rand() % (40 - 15 +1)) + 15;
		
		cr[i].match = rand() % 100;

		cr[i].average = (rand() % 12000) / 100.0;
	}
}
void display(struct player *cr, int size)
{
	printf("%-20s %5s %7s %5s\n",
			"Name", "Age", "Matches", "Average");
	printf("------------------------------------------------\n");
	for (int i = 0; i < size; ++i) {
		printf("%-20s%5d%6d%10.2f\n",
				cr[i].name,
				cr[i].age,
				cr[i].match,
				cr[i].average);	
	}
}

