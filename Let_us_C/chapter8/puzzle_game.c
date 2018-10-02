#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void suffle(int *);
void display(int *, int);
int rearrange(int *, int, int *);
void swap(int *, int, int);

int main()
{
	int array[16], result[15], ptr = 15;
	for (int i = 1; i <= 15; ++i) {
		result[i - 1] = array[i - 1] = i;
	}
	array[15] = 0;

	suffle(array);

	char ch = '0', s[50];
	int win = 1, move = 0;

	while(ch != 'q' && ch != 'Q') {
		system("clear");
		
		printf("Move %d\n", move);

		display(array, ptr);

		if (win == 0) {
			printf("Congratulations!! It's a WIN!!\n");
			printf("total move = %d\n", move);
			break;
		}

		printf("Use w, s, a, d or h, j, k, l to move\n");
		printf("'Q' to exit\n");
		fgets(s, sizeof(s), stdin);
		ch = s[0];
		
		move += rearrange(array, (int)ch, &ptr);
	
		win = memcmp(result, array, sizeof(result));
		
	}
	return 0;
}

void suffle(int *array)
{
	srand(time(0));
	int r, tmp;
	for (int i = 0; i < 15; ++i) {
		r = (rand() % 15); 
		
		tmp = array[i];
		array[i] = array[r];
		array[r] = tmp;
	}
}

void display(int *array, int ptr)
{
	putchar('\n');
	for (int i = 0; i < 16; ++i) {
		if (i == ptr)
			printf("   ");
		else
			printf("%3d", array[i]);
		((i + 1) % 4 == 0) ? putchar('\n'): 0;
	}
	putchar('\n');
}

int rearrange(int *array, int ch, int *ptr)
{
	int ret = 0;
	switch (ch) {
		case 'w':
		case 'k':
			if (*ptr > 11)
				break;
			swap(array, *ptr, *ptr + 4);
			*ptr += 4;
			ret = 1;
			break;
		case 's':
		case 'j':
			if (*ptr < 4)
				break;
			swap(array, *ptr, *ptr - 4);
			*ptr -= 4;
			ret = 1;
			break;
		case 'a':
		case 'h':
			if ((*ptr + 1) % 4 == 0)
				break;
			swap(array, *ptr, *ptr + 1);
			++*ptr;
			ret = 1;
			break;
		case 'd':
		case 'l':
			if (*ptr % 4 == 0)
				break;
			swap(array, *ptr, *ptr - 1);
			--*ptr;
			ret = 1;
			break;
	}
	return ret;
}

void swap(int *array, int x, int y)
{
	int tmp;
	array[x] = array[y];
	array[y] = 0;
}
