// a menu driven program that depicts the working of a library

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct library {
	char title[30];
	char author[30];
	float price;
	int issued;
	int access;
};

void add_book(struct library *, int *);
void find_name(struct library *, char *, int *);
void find_author(struct library *, char *, int *);
void display(struct library *, int);
int cmpfunc (const void *, const void *);

int main()
{
	struct library book[512];
	struct library sorted[512];
	char buf[100];
	int choice, tmp;
	int total = 0; // total no of books

	while(1) {
		system("clear");

		puts("1. Add book information");
		puts("2. Display book information");
		puts("3. List all books of given author");
		puts("4. List the count of books in the library");
		puts("5. List the books sorted by accession number");
		puts("6. Issue a book");
		puts("7. Receive a issued book");
		puts("8. Exit");

		while(*fgets(buf, sizeof(buf), stdin) == '\n');
		choice = buf[0] - '0';
		
		switch(choice){
		case 1:
			add_book(&book[0], &total);
			break;
		case 2:
			puts("Enter book name");
			while(*fgets(buf, sizeof(buf), stdin) == '\n');
			buf[strcspn(buf, "\n")] = '\0';

			find_name(&book[0], buf, &total);
			break;
		case 3:
			puts("Enter author name");
			while(*fgets(buf, sizeof(buf), stdin) == '\n');
			buf[strcspn(buf, "\n")] = '\0';

			find_author(&book[0], buf, &total);
			break;
		case 4:
			printf("\n%-7s%-20s %-20s %6s %6s %6s\n\n",
				"Sl no.", "Title", "Author", 
				"Price", "Issued", "Access");
			for (int i = 0; i < total; ++i)
				display(&book[i], i);
			break;
		case 5:
			for (int i = 0; i < total; ++i)
				sorted[i] = book[i];

			qsort(sorted, total, sizeof(struct library), cmpfunc);

			printf("\n%-7s%-20s %-20s %6s %6s %6s\n\n",
				"Sl no.", "Title", "Author", 
				"Price", "Issued", "Access");
			for(int i = 0; i < total; ++i)
				display(&sorted[i], i);
			break;
		case 6:
			puts("Enter the serial no of the book");
			do {
				while(*fgets(buf, sizeof(buf), stdin)
					       	== '\n');
			} while (sscanf(buf, "%d", &tmp) == 0);

			if (book[tmp-1].issued) {
				puts("\nBook is not available");
				break;
			}
			printf("\n%-7s%-20s %-20s %6s %6s %6s\n\n",
				"Sl no.", "Title", "Author", 
				"Price", "Issued", "Access");
			display(&book[tmp - 1], tmp - 1);

			puts("confirm ? (y/n)");
			while(*fgets(buf, sizeof(buf), stdin) == '\n');
			if (buf[0] == 'y') 
				book[tmp -1].issued = 1;
			else
				break;

			++book[tmp - 1].access;
			puts("The book is issued");

			break;
		case 7:
			puts("Enter the serial no of the book");
			do {
				while(*fgets(buf, sizeof(buf), stdin) == '\n');
			} while (sscanf(buf, "%d", &tmp) == 0);

			printf("\n%-7s%-20s %-20s %6s %6s %6s\n\n",
				"Sl no.", "Title", "Author", 
				"Price", "Issued", "Access");
			display(&book[tmp - 1], tmp - 1);

			puts("confirm ? (y/n)");
			while(*fgets(buf, sizeof(buf), stdin) == '\n');
			if (buf[0] == 'y') 
				(book[tmp -1].issued = 0);
			else 
				break;		
			puts("The book is received");

			break;
		case 8:
			exit(0);
		}
		getchar();
	}
	return 0;
}

void add_book(struct library *book, int *total)
{
	char buf[50];

	puts("Enter title");
	while(*fgets(buf, sizeof(buf), stdin) == '\n');
	sscanf(buf, "%[^\n]s", book[*total].title);

	puts("Enter author name");
	while(*fgets(buf, sizeof(buf), stdin) == '\n');
	sscanf(buf, "%[^\n]s", book[*total].author);

	puts("Enter the price");
	do {
		while(*fgets(buf, sizeof(buf), stdin) == '\n');
	} while (sscanf(buf, "%f", &book[*total].price) == 0);

	book[*total].issued = 0;
	book[*total].access = 0;

	printf("\n%-7s%-20s %-20s %6s %6s %6s\n\n",
		"Sl no", "Title", "Author", 
		"Price", "Issued", "Access");
	display(&book[*total], *total);

	++*total;
}

void find_name(struct library *book, char *name, int *total)
{
	int found = 0;
	for (int i = 0; i < *total; ++i) {
	printf("=%s=, =%s=", book[i].title, name);
	printf("==%d\t", strcmp(name, book[i].title));
		if (strcmp(name, book[i].title) == 0) {
			printf("\n%-7s%-20s %-20s %6s %6s %6s\n\n",
				"Sl no.", "Title", "Author", 
				"Price", "Issued", "Access");
			display(&book[i], i);
			found = 1;
		}
	}
	(!found) ? puts("Book not found") : 0;
}

void find_author(struct library *book, char *name, int *total)
{
	int found = 0;
	for (int i = 0; i < *total; ++i) {
		if (strcmp(name, book[i].author) == 0) {
			printf("\n%-7s%-20s %-20s %6s %6s %6s\n\n",
				"Sl no.", "Title", "Author", 
				"Price", "Issued", "Access");
			display(&book[i], i);
			found = 1;
		}
	}
	(!found) ? puts("Book not found") : 0;
}

void display(struct library *book, int i)
{
	printf("%-6d %-20s %-20s %7.2f %6d %6d\n",
			i + 1, book->title, book->author, 
			book->price, book->issued, book->access);
}

int cmpfunc (const void *a, const void *b)
{
        struct library *ia = (struct library *)a;
        struct library *ib = (struct library *)b;
        return (int) (ia->access - ib->access) ;
}
