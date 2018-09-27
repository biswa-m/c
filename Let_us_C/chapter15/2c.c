/* to reverse the strings stored in a array of pointers to strings
 * using user defined function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* xstrrev(char *);

int main()
{
	char *s[ ] = {
		"To err is human...",
		"But to really mess things up...",
		"One needs to know C!!"
	};
	int len;
	len = sizeof(s) / sizeof(*s);

	for (int i = 0; i < len; ++i){ 
		s[i] = xstrrev(s[i]);
	}
	for (int i = 0; i < len; ++i)
		printf("==%s\n", s[i]);

	char ls[5] = "123";

	return 0;
}

char* xstrrev(char *x) {
	int len = strlen(x);	
	char *buf;
	buf = malloc(len + 1);

	for (int i = 0; i < len; ++i) {
		buf[i] = x[len - i -1];
	}
	buf[len] = '\0';
	return buf;
}
