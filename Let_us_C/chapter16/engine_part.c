/* An automobile company has serial number for engine parts
 * starting from AA0 to FF9. The other characteristics of parts to
 * be specified in a structure are: Year of manufacture, material
 * and quantity manufactured.
 * 	(a) Specify a structure to store information corresponding to
 * 	    a part.
 * 	(b) Write a program to retrieve information on parts with
 * 	    serial numbers between BB1 and CC6.
 */

#include <stdio.h>
#include <stdlib.h>

struct engine {
	char serial[4];
	int year;
	char material;
	int quantity;
};

void encode(char *, int);
int decode(char *);
void random_data(struct engine *, int);
void display(struct engine *, char *, char *);

int main()
{
	int lim = decode("FF9") + 1;
	struct engine parts[lim];

	random_data(&parts[0], lim); //take random value to process

	display(&parts[0], "BB0", "CC6");

	return 0;
}

int decode(char *code)
{
	int n = (code[2] - '0') 
		+ ((code[1] - 'A') * 10)
		+ ((code[0] - 'A') * 10 * 26);
	return n;
}

void encode(char *code, int n)
{
	code[3] = '\0';
	code[2] = (n % 10) + '0'; 
	code[1] = ((n /10) % 26) + 'A';
	code[0] = (n /260) + 'A';
}

void random_data(struct engine *parts, int lim)
{
	for (int i = 0; i < lim; ++i) {
		encode(parts[i].serial, i);
		parts[i].year 
			= (rand() % (2018 - 1975 + 1)) + 1975;
		parts[i].material = (rand() % ('Z' - 'A' + 1)) + 'A';
		parts[i].quantity = rand() % 100;
	}
}

void display(struct engine *parts, char *start, char *end)
{
	printf("Serial No   Year   Material   Quantity\n");
	printf("------------------------------------------------\n");
	for (int i = decode(start); i < decode(end); ++i) {
		printf("%6s%10d%8c%11d\n",
				parts[i].serial,
				parts[i].year,
				parts[i].material,
				parts[i].quantity);	
	}
}
