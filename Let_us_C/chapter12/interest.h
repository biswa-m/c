//Create macro for simple interest calculation

/* P = Principal amount, n = no. of year
 * r = rate of interest in percentage */

#define _SI(P, n, r) (P * n * r / 100.0 ) //Simple Interest

#define _SI_AMT(P, n, r) (P + _SI(P, n, r)) //Simple Interest Amount
