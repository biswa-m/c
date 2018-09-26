/* Write a program that extracts part of the given string from the
 * specified position. For example, if the sting is "Working with
 * strings is fun", then if from position 4, 4 characters are to be
 * extracted then the program should return string as "king". 
 * Moreover, if the position from where the string is to be extracted 
 * is given and the number of characters to be extracted is 0 then the
 * program should extract entire string from the specified position.
 */

#include <stdio.h>
#include <string.h>

int main()
{
	char str[200], str1[200];
	int pos, len;

	printf("Enter a string\n");
	scanf("%[^\n]s", str);
	printf("Enter character position\n");
	scanf("%d", &pos);
	printf("2.Enter word length (0 for all characters)\n");
	scanf("%d", &len);

	strncpy(str1, (str + pos - 1), len);
	
	puts(str1);
	puts(str);

	return 0;	
}
