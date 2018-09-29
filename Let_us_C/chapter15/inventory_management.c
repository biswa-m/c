/* A factory has 3 division and stocks 4 categories of products.
 * An inventory table is updated for each division and for each
 * product as they are received. There are three independent
 * suppliers of products to the factory:
 *     (a) Design a data format to represent each transaction.
 *     (b) Write a program to take a transaction and update inventory.
 *     (c) If the cost per item is also given write a program to
 *     calculate the total inventory values.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int prod = 4; // Total no of product categories
const int divsn = 3; // Total no of divisions
const int sup = 3; // Total no of supplier
FILE *f_log;
char fname[] = "transection_log.log";
const char *divisions[] = {
	"Division 1",
	"Division 2",
	"Division 3"
};
const char *products[] = {
	"Product A",
	"Product B",
	"Product C",
	"Product D"
};
const char *supplier_names[] = {
	"Supplier_X",
	"Supplier_Y",
	"Supplier_Z"
};
const float product_values[] = {12.23, 10.00, 5.50, 2.00};


void load_log(float *, float *, float *, int);
void update_log(int *);
int transection(float *, float *, float * );
void update_inv_val(float *, float *);
void display_inv(float *, int);
void display_inv_val(float *);
void supplier_detail(float *, int);
void display_suppliers(float *);

int main()
{
	float inventory[divsn][prod];
	float inventory_values[divsn][prod];
	float suppliers[sup][divsn][prod];
	int transec[3];

	memset(inventory, 0, 
			divsn*prod*sizeof(inventory[0][0]));
	memset(inventory_values, 0, 
			divsn*prod*sizeof(inventory[0][0]));
	memset(suppliers, 0, 
			sup*divsn*prod*sizeof(suppliers[0][0][0]));
	memset(transec, 0, 
			3*sizeof(transec[0]));
	
	load_log(inventory, suppliers, inventory_values, 0);

	char in[50];
	int choice, ret = 0;
	while(1) {
		system("clear");

		printf("1. Perform a transaction\n");
		printf("2. View inventory\n");
		printf("3. View inventory values\n");
		printf("4. View suppliers record\n");
		printf("5. View all transection logs\n");
		printf("Q. Exit\n");

		scanf(" %s", in);
		choice = (int)in[0];
		
		switch (choice) {	
		case '1':
			ret = transection(inventory,
					suppliers, 
					inventory_values);
			if (ret == 1) {
				printf("Transection cancelled !!\n");
				break;
			}
			printf("\nCurrent Inventory\n");
			display_inv(inventory, 0);
			
			printf("\nCurrent Inventory Value in Rs.\n");
			display_inv(inventory_values, 1);
			break;
		case '2':
			printf("\nCurrent Inventory\n");
			display_inv(inventory, 0);
			break;
		case '3':
			printf("\nCurrent Inventory Value in Rs.\n");
			display_inv(inventory_values, 1);
			break;
		case '4':
			printf("\nSuppliers list\n");
			display_suppliers(suppliers);
			
			printf("\nEnter record no for details\n");
			printf("Any other key for mainmenu\n");
			scanf(" %s", in);
			int n = sscanf(in," %d", &choice);
			if (n != 1 || choice < 0 || choice > sup) {
				continue;
			}
			--choice;
			supplier_detail(suppliers, choice);
			break;
		case '5':
			load_log(inventory, suppliers, 
					inventory_values, 1);
			break;
		case 'q':
		case 'Q':
			exit(0);

		default:
			printf("Invalid Input\n");
			break;
		}
		getchar();
		printf("Press Enter to continue\n");
		getchar();

	}
	return 0;
}

void load_log(float *inventory, float *suppliers, float *values, 
		int print)
{
	int a, b, c, d, ret;
	f_log = fopen(fname, "a+");
	if (f_log == NULL)
	{
		printf("Can not acess log file\n");
		exit(1);
	}
	fseek(f_log, 0, SEEK_SET);
	while(fscanf(f_log, "%d%d%d%d", &a, &b, &c, &d) == 4) {
		if (print) {
			printf("%s, %s, %s,\tNo. of product = %d\n", 
				supplier_names[a],
				divisions[b],
				products[c],
				d);
		} else {
			float *p;
			p = (inventory + (b * prod) + c);
			*p = *p + d; // update inventory 

			update_inv_val(inventory, values);

			p = suppliers + (a * divsn * prod);
			p = p + (b * prod) + c; 
			*p = *p + d; // update supplier's record
		}
	}
	fclose(f_log);
}

int transection(float *inventory, float *suppliers, float *values)
{
	int transec[4]; // [0]Supplier, [1]dividion, 
			// [2]product_name, [4]no of product
	int len[] = {sup, divsn, prod};

	system("clear");

	//Show lists of Suppliers, Divisions and products
	for (int i = 0; i < sup || i < divsn || i < prod; ++i ) {
		for (int j = 0; j < 3; ++j) {
			if (i >= len[j])
			      printf("%25c", ' ');
			else if (j == 0)
			      printf("%3d. %-20s", i + 1, supplier_names[i]);
			else if (j == 1) 
			      printf("%3d. %-20s", i + 1, divisions[i]);
			else if (j == 2)
			      printf("%3d. %-20s", i + 1, products[i]);
		}
		putchar('\n');
	}
	
	printf("Enter supplier's no, Division's no and product's no");
	printf(" respectively\nEnter any other key to cancel\n");
	for (int i = 0; i < 3; ++i) {
		scanf(" %d", &transec[i]);
		if ((transec[i] > len[i]) || transec[i] < 1)
			return 1;
		--transec[i];
	}
	printf("Enter no of products\n");
	scanf(" %d", &transec[3]);

	printf("%s, %s, %s,\tNo. of product = %d\nConfirm ? (y/n)\n", 
				supplier_names[transec[0]],
				divisions[transec[1]],
				products[transec[2]],
				transec[3]);
	char ch;
	while (1) {
		scanf(" %c", &ch);
		if (ch == 'y' || ch == 'Y')
			break;
		else if (ch == 'n' || ch == 'N')	
			return 1;
	}
	update_log(transec);

	float *p;
	p = (inventory + (transec[1] * prod) + transec[2]);
	*p = *p + transec[3]; // update inventory 
	
	update_inv_val(inventory, values);

	p = suppliers + (transec[0] * divsn * prod);
	p = p + (transec[1] * prod) + transec[2]; 
	*p = *p + transec[3]; // update supplier's record
	printf("inventory updated\n");
	return 0;
}

void update_inv_val(float *inv, float *val)
{
	float *p, *v;
	for (int i = 0; i < divsn; ++i)
		for(int j = 0; j < prod; ++j) {
			p = inv + (i * prod) + j;
			v = val + (i * prod) + j;
			*v = *p * product_values[j];
		}
}

void display_inv(float *inv, int type)
{
	/* To display product details of all the devision
	 * arg 1 is pointer to a float array[divsn][prod]
	 * arg 2 == 0, display as integer value
	 * arg 2 != 1, display 2 digit after decimal
	 */

	char *str;
	(type != 0) 
		? (str = "%12.2f ")  
		: (str = "%12.0f "); 

	float total_div = 0, GT = 0, *p;
	float total_prod[prod];
	memset(total_prod, 0, prod*sizeof(total_prod[0]));
	
	// row 1, product name
	printf("\n%13c", ' ');	
	for (int i = 0; i < prod; ++i)
		printf("%12.11s ", products[i]);
	printf("|%12s\n", "Total");
	for (int i = 0; i < prod + 2; ++i)
		printf("%13s", "-------");
	putchar('\n');

	// from row 2 display values
	for (int i = 0; i < divsn; ++i) {
		printf("%11.11s |", divisions[i]);
		for (int j = 0; j < prod; ++j) {
			p = inv + (i * prod) + j;

			total_div += *p;
			total_prod[j] += *p;

			printf(str, *p);
		}
		putchar('|');
		printf(str, total_div);
		putchar('\n');

		GT = GT + total_div;
		total_div = 0;
	}
	for (int i = 0; i < prod + 2; ++i)
		printf("%13s", "-------");
	putchar('\n');
	
	// last row, display totals
	printf("%11s |", "Total");
	for (int j = 0; j < prod; ++j)
		printf(str, total_prod[j]);
	putchar('|');
	printf(str, GT);
	putchar('\n');
}

void supplier_detail(float *suppliers, int i)
{
	printf("\n%s\n", supplier_names[i]);
	display_inv((suppliers + (i * divsn * prod)), 1);	
}

void display_suppliers(float *suppliers)
{
	float total, *p, *ptr;
	for(int n = 0; n < sup; ++n) {
		ptr = suppliers + (n * divsn * prod);

		for (int i = 0; i < divsn; ++i) {
			for (int j = 0; j < prod; ++j) {
				p = ptr + (i * prod) + j;
				total += *p;
			}
		}
		printf("%d. %s\t %.0f Products\n", 
				n+1, supplier_names[n], total);
		total = 0;
	}
}

void update_log(int *transec) 
{
	f_log = fopen(fname, "a");
	fprintf(f_log, "%d %d %d %d\n", transec[0], transec[1], transec[2], transec[3]);
	printf("%d %d %d %d\n", transec[0], transec[1], transec[2], transec[3]);
	fclose(f_log);
}
