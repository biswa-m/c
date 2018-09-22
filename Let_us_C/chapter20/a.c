/* Write a program to carry out the following:
 * (a) Read a text file provided at command prompt
 * (b) Print each word in reverse order
 */

#include <stdio.h>

#define SPCL_CHAR(ch) (\
			  ((ch > 64 && ch < 91)\
			|| (ch > 96 && ch < 123)\
			|| (ch > 47 && ch < 58))\
			? 0\
			: 1)
void rev_str(char *);

int main (int argc, char *argv[])
{
	if (argc < 2){
		printf("\nError: Provide file name as argument\n");
		return 1;
	}
	
	char ch, word[512];
	int n = 0;
	int i = 1;
	int in_word = 0;

	while(i < argc) {
		FILE *fp;

		fp = fopen(argv[i], "r");
		if (fp == NULL)	{
			printf("Error: Can not read %s\n", argv[i]);
			return 2;
		}
		printf("Reversing the words of %s :\n", argv[i]);

		while((ch = fgetc(fp)) != EOF) {
			if (ferror(fp)) {
				perror(argv[i]);
				break;
			}

			if (!SPCL_CHAR(ch)) {
				word[n] = ch;
				in_word = 1;
				++n;
			} else if (SPCL_CHAR(ch) && !in_word) {
				putchar(ch);
			} else if (SPCL_CHAR(ch) && in_word) {
				word[n] = '\0';
				rev_str(word);
				printf("%s", word);
				n = 0;
				putchar(ch);
			}
		}
		++i;
	}
	return 0;
}

void rev_str(char str[])
{
	int i;
	for(i = 0; str[i] != '\0'; ++i);
	
	int len = i;
	char tmp[len];

	for(i = 0; i < len; ++i)
		tmp[i] = str[i];
	
	for(i = 0; i < len; ++i)
		str[i] = tmp[len - i -1];
}
