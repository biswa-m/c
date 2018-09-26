// To convert all lowercase characters in a given string to uppercase

#include <stdio.h>
#include <ctype.h>

int main()
{
	char str[100], str1[100];
	
	scanf("%[^\n]s", str);

	int i = 0;
	while(str[i] != '\0') {
		str1[i] = toupper(str[i]);
		++i;
	}

	printf("%s\n", str1);

	return 0;
}
