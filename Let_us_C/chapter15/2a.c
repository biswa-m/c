/* Write a program that uses an array of pointers to strings str[ ].
 * Receive two strings str1 and str2 and check if str1 is
 * embedded in any of the strings in str[ ]. If str1 is found, then
 * replace it with str2.
 * char *str[ ] = {
 * 			"We will teach you how to...",
 * 			"Move a mountain",
 * 			"Level a building",
 * 			"Erase the past",
 * 			"Make a million",
 * 			"...all through C!"
 * 			} ;
 * For example if str1 contains "mountain" and str2 contains"car",
 * then the second string in str should get changed to "Move a car".
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char *str[] = { 
		"We will teach you how to...",
		"Move a mountain",
		"Level a building",
		"Erase the past",
		"Make a million",
		"!...all through C! ",
		"this is to test this program to find 'this' "
	};
	char str1[50], str2[50];

	printf("Enter the string to be replaced\n");
	scanf(" %[^\n]s",str1);
	printf("%s will be replaced with ..\n", str1);
	scanf(" %[^\n]s",str2);

	int len1;
	len1 = strlen(str1);	

	int row; //lengnth of array pointer to string
	row = sizeof(str) / sizeof(*str);

	int i = 0, l;
	char *p = str[i];
	char *ptr, *t, buf[200] = "";

	while (i < row) {
		ptr = strstr(p, str1);
			
		if(ptr == NULL) {
			strcat(buf, p);
		
			// since str[i] is a pointer not string
			l = strlen(buf);
			t = malloc(l + 1);
			strcpy(t, buf);
			str[i] = t;

			++i;
			p = str[i];
			buf[0] = '\0';
			continue;
		} else {
			strncat(buf, p, (ptr - p));
			p = ptr + len1;
			strcat(buf, str2);	
		}
	}

	for(int i = 0; i < row; ++i)
		printf("%s\n", str[i]);
	
	return 0;
}
