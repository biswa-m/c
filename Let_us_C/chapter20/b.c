/* Using command line argumentm, search for a word in a file 
 * and replace it with the specified word. 
 * The usage of the program is shown below.
 * $ change <old word> <new word> <filename>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("Error: invalid no. of arguments");	
		exit(1);
	}
	FILE *fp, *ftemp;
	fp = fopen(argv[3], "r");
	if (fp == NULL) {
		printf("Error: Inable to read %s", argv[3]);
		exit(2);
	}
	ftemp = fopen("temp.txt", "w+"); 
	if (ftemp == NULL) {
		printf("Error: Unable to write data");
		exit(3);
	}
	int len;
	len = strlen(argv[1]);
	
	char ch, count;
	int i = 0;
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == argv[1][i] && i < len - 1) {
			++i;
		} else if (ch == argv[1][i] && i == len - 1) {
			fputs(argv[2], ftemp);
			i = 0;
			++count;
		} else if (ch != argv[1][i] && i != 0) {
			for (int n = 0; n < i; ++n)		
				fputc(argv[1][n], ftemp);
			fputc(ch, ftemp);
			i = 0;
		} else {
			fputc(ch, ftemp);
		}
	}
	fclose(fp);

	fp = fopen(argv[3], "w");
	if (fp == NULL) {
		printf("Error: Inable to write %s", argv[3]);
		exit(4);
	}
	fseek(ftemp, 0, SEEK_SET);

	while ((ch = fgetc(ftemp)) != EOF)
		fputc(ch, fp);

	fclose(fp);
	fclose(ftemp);

	return 0;	
}
