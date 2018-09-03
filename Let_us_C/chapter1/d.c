// temperature conversion

#include <stdio.h>

int main()
{
	float c, f;

	printf("Enter temperature reading in farenheit\n");
	scanf("%f", &f);

	//formula
	c = (f - 32)/1.8;

	printf("The temperature in centigrade is %.2f. \n", c);

	return 0;
}
