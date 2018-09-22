/* Calculating utility. The usage of the program is shown below.
 * calc <n> <switch> <m>
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

double str_to_double(char *);
double operate(double, char *, double, int *);

int main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("Invalid no of arguements\n");
		printf("Rquired syntex :\n./<filename> <operand 1>");
		printf(" <operator> <operand 2>\n");
		printf("Example :\n./a.out 23.53 + 5\n");
		exit(1);
	}
	
	double x = 0;
	double y = 0;

	x = str_to_double(argv[1]);
	y = str_to_double(argv[3]);
	
	double result;
	int flag = 0;
	result = operate(x, argv[2], y, &flag);

	if (flag == 1) {
		(result == 0)
			? printf("False\n")
			: printf("True\n");
	} else {
	printf("%lf\n", result);
	}
	
	return 0;
}

double str_to_double(char* str)
{
	int len, dec;
	double x = 0;
	
	len = strlen(str);
	for (dec = 0; str[dec] != '\0'; ++dec) {
		if (str[dec] == '.')
			break;
	}
	
	int n = 0;
	for (int i = 0; i < len; ++i) {
		if (i == dec){
			n = 1;
			continue;	
		}
		x += ((str[i] - '0') 
				* pow(10.0, (dec - i - 1 + n)));
	}

	return x;
}

double operate(double x, char op[], double y, int *flag)
{
	double result;

	if (strcmp(op, "+") == 0) {
		result = x + y;
	} else if (strcmp(op, "-") == 0) {
		result = x - y;
	} else if (strcmp(op, "x") == 0) {
		result = x * y;
	} else if (strcmp(op, "/") == 0) {
		result = x / y;
	} else if (strcmp(op, "%") == 0) {
		result = (int)x % (int)y;
	} else if (strcmp(op, "pow") == 0) {
		result = pow(x, y);
	} else if (strcmp(op, "\>") == 0) {
		result = (x > y);
		*flag = 1;
	} else if (strcmp(op, "\<") == 0) {
		result = (x < y);
		*flag = 1;
	} else if (strcmp(op, "==") == 0) {
		result = (x == y);
		*flag = 1;
	} else if (strcmp(op, "\<=") == 0) {
		result = (x <= y);
		*flag = 1;
	} else if (strcmp(op, "\>=") == 0) {
		result = (x >= y);
		*flag = 1;
	} else {
		printf("Enter one of the following operator\n");
		printf("+, -, x, /, %%, pow, .>, .<, .==, .<=, .>=");
		putchar('\n');
		exit(1);
	}

	return result;
}

