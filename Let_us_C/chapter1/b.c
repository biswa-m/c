// distance conversion

#include <stdio.h>

int main()
{
	float km, m, ft, in, cm;

	printf("The distance in Km. =  ");
	scanf("%f",&km);

	/* formulas for conversion */
	m = 1000*km;
	cm = 100000*km;
	ft = 3280.84*km;
	in = 39370.1*km;

	printf("\n \n %.2f meter\n %.2f cm\n %.2f ft \n %.2f in \n", m, cm, ft, in);
	
	return 0;
}
