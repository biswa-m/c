// To convert string to number.
// Example "12345.12" to float 12345.12

#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
	char str[50];
	printf("Enter a any no. \nThis will be read as string\n");
	scanf("%s", str);

	long double x = 0;
	int len;
         
        len = strlen(str);

	int dec; // to store the position of decimal point
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
	printf("The string is converted to number\n%Lf\n", x);
	return 0;
}
