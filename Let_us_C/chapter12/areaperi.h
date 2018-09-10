// Area and perimeter of triangle square and circle
// Use -lm to link math.h while compiling

#ifndef __math_h
	#include <math.h>
#endif

#define PI 3.1416

#define AREA_T_S(a, b, c) ((float) sqrt(\
			( (a)+(b)+(c) ) / 2 *\
			( (a)/2+(b)/2-(c)/2 ) *\
		       	( (a)/2-(b)/2+(c)/2 ) *\
			( -(a)/2+(b)/2+(c)/2 )\
			))
#define AREA_T_BH(b, h) ( 0.5 * (b) * (h) )

#define AREA_S(a) ( (a) * (a) )

#define AREA_C(r) ( PI * (r) * (r) ) 

#define PERI_T(a, b, c) ( (a) + (b) + (c) ) 

#define PERI_S(a) ( 4 * a )

#define PERI_C(r) ( 2 * PI * r )
