/* replaces two or more consecutive blanks in a string 
 * by a single blank.
 */

#include <stdio.h>

int main()
{
	char s1[200], s2[200];

	printf("Enter a string\n");
	scanf("%[^\n]s", s1);

	int i = 0, j = 0, flag = 0;

	while (s1[i] != '\0') {
		if (s1[i] == ' ' && flag == 1) {
			++i;
			continue;
		} else if (s1[i] == ' ' && flag == 0) {
			flag = 1;
		} else {
			flag = 0;
		}
		s2[j] = s1[i];
		++j;
		++i;
	}
	s2[j] = '\0';

	printf("Consecutive blanks are removed\n%s\n", s2);
	
	return 0;
}
