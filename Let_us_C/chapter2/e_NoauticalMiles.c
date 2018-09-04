// input co-ordinates of two places and calculate nautical miles

#include <stdio.h>
#include <math.h>

int main()
{
	float L1, L2, G1, G2, Nmile;

	printf("For Place 1 enter lattitude and longitude respecively\n");
	scanf("%f %f", &L1, &G1);
	printf("For place 2 enter lattitude and longitude respectively\n");
	scanf("%f %f", &L2, &G2);

	//formula for nautical miles
	Nmile = 3963 * acos( sin(L1)*sin(L2) + cos(L1)*cos(L2)*cos(G2-G1) );

	printf("The distance between two places are %.2f nautical mile\n", Nmile);

	return 0;
}
