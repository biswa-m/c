// Gross salary calculation

#include <stdio.h>

int main()
{
	float basic, dearness, house_rent, gross_salary;

	dearness = 0.40;
	house_rent = 0.20;

	printf("Enter basic salary\n");
	scanf("%f", &basic);

	gross_salary = basic + basic*dearness + basic*house_rent;
	
	printf("Gross salary is %0.2f \n", gross_salary);

	return 0;
}
