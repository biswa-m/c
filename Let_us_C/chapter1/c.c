// aggregate and percentage mark calculation

#include <stdio.h>

int main()
{
	int sub1, sub2, sub3, sub4, aggr, fmark=100;
	float perc;

	printf("enter the marks obtain in \n");
	
	printf("sub1 = ");
	scanf("%d",&sub1);

	printf("sub2 = ");
	scanf("%d",&sub2);
	
      	printf("sub3 = ");                      
       	scanf("%d",&sub3);
	
      	printf("sub4 = ");                      
	scanf("%d",&sub4);
	
	//formula
	aggr=sub1+sub2+sub3+sub4;
	perc=((float) aggr/(4*fmark))*100;

	printf("\nAggregate mark = %d \n Percentage = %.2f \n", aggr, perc);
}
