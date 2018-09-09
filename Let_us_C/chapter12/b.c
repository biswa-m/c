// Macro definations for some basic character operations

#include <stdio.h>

#define IS_SMALL_CASE(x) ((x) >= 97 && (x)  <= 122)
#define IS_UPPER_CASE(x) ((x) >= 65 && (x) <= 90)
#define IS_ALPHABET(x) (( IS_SMALL_CASE(x) || IS_UPPER_CASE(x) ))
#define BIGGER_OF(x, y, big) {if (x > y) \
					big = x; \
			  	else  \
					big = y; \
				}
int main()
{
	char a;
	float big, n, m;

	printf("Enter an alphabet\n");
	scanf("%c", &a);
	fflush(stdin);

	if (IS_ALPHABET(a))
	{
		printf("You have entered an alphabate\n");
		
		if (IS_SMALL_CASE(a))
		printf("You have entered a small case letter\n");
	
		if (IS_UPPER_CASE(a)) //'if' is used instead to check the argument is working or not 
		printf("You have entered a upper case letter\n");
	}	
	else
		printf("Wish you know what alphabet means !\n");

	printf("Now, enter two number\n");
	scanf("%f", &n);
	fflush(stdin);
	scanf("%f", &m);
	
	if (n == m)
		printf("Both numbers are equal\n");
	else	
	{
		BIGGER_OF(n, m, big);
		printf("%.2f is bigger\n", big);
	}

}
