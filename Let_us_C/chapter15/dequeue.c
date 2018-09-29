/* A dequeue is an ordered set of elements in which elements
 * may be inserted or retrieved from either end. Using an array
 * simulate a dequeue of characters and the operations retrieve
 * left, retrieve right, insert left, insert right. Exceptional
 * conditions such as dequeue full or empty should be indicated.
 * Two pointers (namely, left and right) are needed in this 
 * simulation.
 */

#include <stdio.h>

#define LEN 10

int main()
{
	char dequeue[LEN];
	char *left, *right;
	right = dequeue + (LEN / 2);
	left = right - 1;

	char s[20];
	int choice, ch;

	while(1) {
		printf("\n\n1. insert left\n");
		printf("2. insert right\n");
		printf("3. Retrive left\n");
		printf("4. Retrive right\n");
		printf("Q. Quit\n");
		scanf(" %s", s);
		choice = (int) s[0];
		
		switch (choice) {
		case '1':
			if (left < dequeue) {
				printf("Queue Full \n");
			} else {
				printf("insert left: \t");
				printf("Enter a char\n");
				scanf(" %c", left);
				--left;
			}
			break;
		case '2':
			if (right >= (dequeue + LEN)) {
				printf("Queue Full \n");
			} else {
				printf("insert right: \t");
				printf("Enter a char\n");
				scanf(" %c", right);
				++right;
			}
			break;
		case '3':
			if (left == right -1) {
				printf("Queue Empty\n");
				continue;
			} else {
				ch = *(++left);
				printf("\nleft retrived = %c\n", ch);
			}
			break;
		case '4':
			if (left == right -1) {
				printf("Queue Empty\n");
				continue;
			} else {
				ch = *(--right);
				printf("\nright retrived = %c\n", ch);
			}
			break;
		case 'Q':
		case 'q':
			return 0;
		default:
			printf("Invalid Input\n");
			continue;
		}

		if (right - left != 1) {
			printf("Updated Dequeue\n");
			for (int i = 1; i < (right -left); ++i)
				printf("%c ", *(left + i));
		} else {
		printf("Queue is now empty\n");
		}
		printf("\nPress Enter to continue\n");
		getchar();
		getchar();
	}
	return 0;
}
