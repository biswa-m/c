//Use userdefined header file to calculate area and perimeter 

#include <stdio.h>
#include <stdlib.h>
#include "areaperi.h" //use -lm while compiling

int main()
{
 	float area, peri, a, b, c, r, h;
	char check;
	area = sqrt(2.33);

	system("clear");

	while(1)
	{	
		printf("\nChoose from the following options");
		printf("\n1. Circle\n2. Triangle\n3. Square\n\n ");
		printf("Press 'Esc' to terminate the program\n");

		scanf(" %c", &check);
		system("clear");

		switch(check)
		{
			case '1':
				printf("Enter radius of the circle\n");
				scanf("%f", &r);

				area = AREA_C(r);
				peri = PERI_C(r);

				printf("Area of the circle is %f\n", area);				
				printf("Perimeter of the circle is %f\n", peri);				

				break;	

			case '2':
				do
				{
					printf("Need one of the following input\n");
					printf("1. Lengths of three sides\n");
					printf("2. Base and height of the triangle\n");
					printf("0. Mainmenu");
					printf("\nPress 'Esc' to terminate the program\n");
	
					char check;
					scanf(" %c", &check);
	
					if (check == '0')
						break;
					else if (check == '1')
					{
						printf("Enter lengths of the three sides \n");
						scanf("%f %f %f", &a, &b, &c);
	
						area = AREA_T_S(a, b, c);
						peri = PERI_T(a, b, c);

						printf("Area of the triangle is %f\n", area);				
						printf("Perimeter of the triangle is %f\n", peri);				

						break;
					}
					else if (check == '2')
					{
						printf("Enter length of base and heigth respectively\n");
						scanf("%f %f", &b, &h);

						area = AREA_T_BH(b, h);
						
						printf("Area of the triangle is %f %f %f\n", b, h, area);	

						break;
					}
					else if (check == 27)
						return (0);
					else
					{
						printf("Not a valid input\n");
						continue ;
					}
				}while(1);
				break;

			case '3':
				printf("Enter length of a side of the square\n");
				scanf("%f", &a);

				area = AREA_S(a);
				peri = PERI_S(a);

				printf("Area of the square is %f\n", area);
				printf("Perimete of the square is %f\n", peri);

				break;

			case 27 : // press 'Esc' 
				return 0;
			default :
				printf("Not a valid input \n");
		}
	}
	return 1;
}
