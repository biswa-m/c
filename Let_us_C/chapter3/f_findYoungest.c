// input ages of three persons. determine the youngest of them

#include <stdio.h>

int main()
{
	int Ram, Shyam, Ajay;

	printf("Enter ages of Ram Shyam and Ajay respectively\n");
	scanf("%d %d %d", &Ram, &Shyam, &Ajay);

	if (Ram <= Shyam)
	{	
		if (Ram <= Ajay)
			printf("Ram (%d) is youngest\n", Ram);
		else
			printf("Ajay (%d) is youngest\n", Ajay);

	}
	else 
	{
		if (Shyam <= Ajay)
			printf("Shyam (%d) is youngest\n", Shyam);
		else
			printf("Ajay (%d) is youngest\n", Ajay);
	}

	return 0;
}
