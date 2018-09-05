// Determine the grade of steel from input hardness, carbon content and tensile strength.

#include <stdio.h>

int main()
{
	int hard, ten, grd, h, t, c;
	float carb;

	printf("Recomanded values of \nhardness > 50, Carbon Content < 0.7, Tensile strength > 5600");
	printf("Enter the values of \nHardness = ");
	scanf("%d", &hard);
	printf("Carbon Content (0-1) = \n");
	scanf("%f", &carb);
	printf("Tensile Strength\n");
	scanf("%d", &ten);
	
	h=(hard>50)?1:0;
	c=(carb<0.7)?1:0;
	t=(ten>5600)?1:0;

	if(h+t+c ==3)
		grd = 10;
	else if(h+t+c == 2)
	{
		if(t==0)
			grd = 9;
		else if(h==0)
			grd = 8;
		else
			grd = 7;
	}
	else if(h+t+c == 1)
		grd = 6;
	else
		grd = 5;
	
	printf("The grade is %d\n", grd);

	return 0;
}
