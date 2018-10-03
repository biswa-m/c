#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bank {
	int ac_no;
	char name[50];
	float balance;
};

void random_data(struct bank *, int, int);
void find_min_bal(struct bank *, int, int);
void transaction(struct bank *, int);

int main()
{
	struct bank account[200];

	// Generate random data customer with balance less than 100
	// random_data(struct *, size of struct array, max balance)
	random_data(&account[0], 200, 10000);

	int lim;
	char buf[50];
	printf("\nFind accounts with balance less than:\t");
	do {
 		//get non empty string
		while(*fgets(buf, 50, stdin) == '\n');
	} while (!sscanf(buf, " %d", &lim));

	find_min_bal(&account[0], 200, lim);

	while (1) {
		printf("'N' new transaction\t");	
		printf("'Q' to exit\n");
		fgets(buf, 50, stdin);
		if (buf[0] == 'q' || buf[0] == 'Q')
			exit(0);

		transaction(&account[0], 200);
	}
}

void random_data(struct bank *ac, int size, int max)
{
	printf("A/c no  %30s  %8s\n", "Customer Name", "Balance");
	printf("------------------------------------------------\n");
	int  len;
	int strt = 555000;
	for (int i = 0; i < size; ++i) {
		ac[i].ac_no = i + strt;
		printf("%d\t", ac[i].ac_no);

		len = (rand() % 16) + 5;
		char ch[len + 1];
		for (int j = 0; j < len; ++j)
			ch[j] =	(rand() % ('Z' - 'A' + 1)) + 'A';
		ch[(rand() % len - len/4 +1) + len/4] = ' ';
		ch[len] = '\0';
		strcpy(ac[i].name, ch);
		printf("%30s ", ac[i].name);
		
		ac[i].balance = ((rand() % (max * 100)) / 100.0);
		printf("%7.2f\n", ac[i].balance);
	}
}

void find_min_bal(struct bank *ac, int size, int lim)
{
	printf("A/c no  %30s  %8s\n", "Customer Name", "Balance");
	printf("------------------------------------------------\n");
	for (int i = 0; i < size; ++i) {
		if (ac[i].balance < lim){
			printf("%d\t", ac[i].ac_no);
			printf("%30s ", ac[i].name);
			printf("%7.2f\n", ac[i].balance);
		}
	}
}

void transaction(struct bank *ac, int size)
{
	char buf[50];
	int n;
	printf("Enter account no. \t");
	do {
 		//get non empty string
		while(*fgets(buf, 50, stdin) == '\n');
	} while (!sscanf(buf, " %d", &n));
	
	int found = 0;
	int i;
	for (i = 0; i < size; ++i) {
		if (ac[i].ac_no == n) {
			found = 1;
			break;
		}
	}
	if (!found) {
		puts("Transaction failed: Account no does not exist");
		return;
	}

	float amt;
	printf("Enter amount \t");
	do {
		//get non empty string
		while(*fgets(buf, 50, stdin) == '\n');
	} while (!sscanf(buf, " %f", &amt));
	
	int mode;
	char *modes[2] = {"withdrawal", "deposit"};
	printf("Enter transaction mode,\n");
	printf("0 for withdrawal, 1 for deposit\n");
	do {
		mode = *fgets(buf, 50, stdin);
	} while (mode != '0' && mode != '1');
	mode = mode - '0';

	printf("\nAccount no:%d\t", ac[i].ac_no);
	printf("Name: %s\n", ac[i].name);
	printf("Amount: %.2f", amt);
	printf("\tmode: %s\n", modes[mode]);

	printf("Confirm ? (y/n)");	
	char ch;
	do {
		ch = *fgets(buf, 50, stdin);
	} while (ch != 'y' && ch != 'n');

	if (ch == 'n') 
		return;
	if (mode == 0) {
		(ac[i].balance >= amt)
			? (ac[i].balance -= amt)
			: puts("\nInsufficiant balance!");
	} else if (mode ==1) {
		ac[i].balance += amt;
	}
		printf("\nAccount no:%d\n", ac[i].ac_no);
		printf("Name: %s\n", ac[i].name);
		printf("Balance: %.2f\n", ac[i].balance);
}
