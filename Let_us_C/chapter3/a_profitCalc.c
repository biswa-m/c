// input cost price and selling price and calculate the profit / loss.

#include <stdio.h>

int main()
{
	float cp, sp, profit;

	printf("Enter the cost price \t");
	scanf("%f",&cp);
	printf("Enter the selling price \t");
	scanf("%f",&sp);
	
	profit = sp - cp;

	if(profit < 0)
		printf("The loss incurred is %.2f\n", 0-profit);
	else if(profit > 0)
		printf("The profit incurred is %.2f \n", profit);
	else 
		printf("The selling price and cost price are same. Hence no profit or loss incured\n");

	return 0;
}
