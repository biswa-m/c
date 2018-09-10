// Use user defined header file interest.h
// Calculate simple interest

#include <stdio.h>
#include "interest.h"

int main()
{
	float P, n, r;

	printf("Enter the following to calculate simple interest\nPrincipal amount = ");
	scanf("%f", &P);
	printf("No of years = ");
	scanf("%f", &n);
	printf("Rate of interest (in percentage) = ");
	scanf("%f", &r);

	printf("Simple interest = %.2f\n", _SI(P, n, r));
	printf("Total amount = %.2f\n", _SI_AMT(P, n, r));
	
	return 0;
}
