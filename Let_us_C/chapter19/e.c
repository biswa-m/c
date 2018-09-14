/* To copy one file to another. While doing so replace all lowercase 
 * characters to their equivalent uppercase characters.
 */

#include <stdio.h>

#define UPPER_CASE(x) {if (x >= 97 && x <= 122)\
				x -= 32;} 
int main()
{
 	FILE *f_source, *f_target;
        char ch, source[] = "sample_files/sample1.txt",
             target[] = "sample_files/sample2.txt";

        f_source = fopen(source, "r");
        if (f_source == NULL)
        {
                printf("Can not open source file\n");
                return 1;
        }

        f_target = fopen(target, "w");
        if (f_target == NULL)
        {
                printf("Can not open target file\n");
                return 2;
        }
	     
	while ((ch = fgetc(f_source)) != EOF)
        {
		if (ch >= 97 && ch <= 122)
			ch -= 32;
                fputc(ch, f_target);
        }

	printf("The file %s is copied to %s after converting all lower case character to upper\n", source, target);

	return 0;
}
