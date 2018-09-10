#include <stdio.h>

#define A_MEAN_2(x, y) ( ((x)+(y)) * 0.5 )

#define _ABS(x) (((x)<0) ? -(x) : (x))

#define _LOWER(x) (\
		((x)>=65 && (x)<=90) ?\
		(x)+32 : x\
		)

#define _BIGGEST_3(a, b, c) (\
		(a>b) ? \
		((a>c) ? a : c) :\
		((b>c) ? b : c) \
		)

#define _FLUSH_STDIN {char ch='0';\
			while(ch != '\n')\
			ch = getchar();\
		    }

int main()
{
	float a, b, c;
	char ch;

	printf("Enter two no.s to calculate arithmatic mean\n");
	scanf("%f %f", &a, &b);
//	_FLUSH_STDIN;
	printf("Arithmatic mean is %.2f\n", A_MEAN_2(a, b));

	printf("Enter a no to find absolute value\n");
	scanf("%f", &a);
	_FLUSH_STDIN;
	printf("Absolute value is %.2f\n", _ABS(a));

	printf("Enter a character to convert it to Lower case\n");
	scanf(" %c", &ch);	
	_FLUSH_STDIN;
	printf("Corresponding lower case letter is '%c'\n", _LOWER(ch));

	printf("Enter three no.s to find out the biggest one\n");
	scanf("%f %f %f", &a, &b, &c);
	_FLUSH_STDIN;
	printf("The biggest among the three is %.2f\n", _BIGGEST_3(a, b, c));

	return 0;
}
