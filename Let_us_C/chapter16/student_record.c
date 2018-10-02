#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
		int roll;
		char name[100];
		char dept[50];
		char course[50];
		int year;
	};
void display_student(struct student *);
int find_year(struct student *, int, int);
int find_roll(struct student *, int, int);

int main()
{
	struct student s[450];

	char buf[255], ch;
	int i;
	for (i = 0; i < 450; ++i) {
		system("clear");

		printf("\nEntry %d\n", i + 1);
		
		// Read data and data validation 
		do { 
			printf("Enter Roll no:\t");
			
			while(*fgets(buf, sizeof(buf), stdin)
				== '\n'); //get non empty string
		} while (!sscanf(buf, " %d", &s[i].roll));

		printf("Enter Name:\t");
		//get input, untill non empty string obtain
		while (*fgets(s[i].name, sizeof(s[i].name), stdin)
				== '\n');
		//remove trailling '\n'
		strcpy(s[i].name, strtok(s[i].name, "\n"));

		printf("Enter Department:\t");
		while (*fgets(s[i].dept, sizeof(s[i].dept), stdin)
				== '\n');
		strcpy(s[i].dept, strtok(s[i].dept, "\n"));

		printf("Enter Course:\t");
		while (*fgets(s[i].course, sizeof(s[i].course), stdin)
				== '\n');
		strcpy(s[i].course, strtok(s[i].course, "\n"));

		do { 
			printf("Enter year of adimission:\t");
			while (*fgets(buf, sizeof(buf), stdin)
				== '\n');
		} while (!sscanf(buf, " %d", &s[i].year));
		
		// Show input struct
		display_student(&s[i]);

		// Receive control command
		printf("\n'N' next entry\t");
		printf("'E' Edit entry %d\t'Q' Exit\t", i+1);
		do {
			fgets(buf, sizeof(buf), stdin);
			ch = buf[0];
		} while (ch != 'E' && ch != 'e' 
				&& ch != 'n' && ch != 'N'
				&& ch != 'q' && ch != 'Q');
		if (ch == 'q' || ch == 'q') 
			break;
		else if (ch == 'e' || ch == 'E')
			--i;
	}
	system("clear");

	int size = ++i;
	for (i = 0; i < size; ++i ) {
		printf("\n%d.", i);
		display_student(&s[i]);
	}

	// search by year
	int yr;
	printf("Enter a year to search records \t");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, " %d", &yr);
		
	int n = find_year(&s[0], yr, size);
	(n == 0) ? printf("No match found\n"): 0;

	// search by roll no 
	int roll;
	printf("Enter roll no to get detail \t");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, " %d", &roll);
		
	n = find_roll(&s[0], roll, size);
	(n == 0) ? printf("No match found\n"): 0;

	return 0;
}

void display_student(struct student *s)
{
	printf("\nRoll no: %d\n", s->roll);
	printf("Name: %s\n", s->name);
	printf("Department: %s\n", s->dept);
	printf("Course: %s\n", s->course);
	printf("Year of Joining: %d\n", s->year);
}

int find_year(struct student *p, int yr, int size)
{
	int n = 0;
	for (int i = 0; i < size; ++i) {
		if (p[i].year == yr) {
			++n;
			printf("%d. %s\n", n, p[i].name);
		}
	}
	return n;
}

int find_roll(struct student *p, int roll, int size)
{
	int n = 0;
	for (int i = 0; i < size; ++i) {
		if (p[i].roll == roll) {
			++n;
			display_student(&p[i]);
		}
	}
	return n;
}
