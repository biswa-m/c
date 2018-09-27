// to sort a set of names stored in an array in alphabetical order.

#include <stdio.h>
#include <string.h>

int main()
{
	char *str[] = {
		"Kjkjksd lsjdfk",
		"adfj  lugojd",
		"dsfmli dflj",
		"Ikjd kjks",
		"kjKljf ksjdf",
		"kjkikjas lsk"
	};
	int len, cmp;
	char *tmp;

	len = sizeof(str)/sizeof(*str);

	for (int i =0; i < len - 1; ++i){
		for (int j = 0; j < len - i - 1; ++j) {
			cmp = strcasecmp(str[j], str[j + 1]);
			if (cmp > 0) {
				tmp = str[j];	
				str[j] = str[j + 1];
				str[j + 1] = tmp;
			}	
		}
	}
	for (int i = 0; i < len; ++i)
		printf("%s\n", str[i]);
	
	return 0;
}
