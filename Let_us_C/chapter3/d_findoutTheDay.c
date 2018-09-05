// 01/01/01 is monday. find out the day on 1st january of an input year. 

#include <stdio.h>

int main()
{
	int n, lyCount, day;
	
	printf("Enter a year\t");
	scanf("%d", &n);
	
	/* Week consist of 7 days. a non leap year has 1 extra day. A leap year has 2 extra days */
	n = n-1; //leap year count before 1st january of the input year. leap year comes on feb 29th  
	lyCount = n/4 - n/100 + n/400;
	day = (n + lyCount) % 7; // total extra days 

	//	printf("%d", day);
	
	if(day==1)
		printf("Monday");
	else if(day == 2)
		printf("tuesday");
	else if(day == 3)
		printf("wednessday");
	else if(day==4)
                printf("thursday");
        else if(day == 5) 
                printf("friday");
        else if(day == 6)
                printf("saturday");
        else
                printf("sunday");
	printf("\n");
	return 0; 
}
