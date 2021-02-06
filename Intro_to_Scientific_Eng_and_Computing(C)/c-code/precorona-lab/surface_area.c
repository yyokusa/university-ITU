#include <stdio.h>
#include <math.h>

double calc_bsa(double,double);

int main() {
	
	double bsa = 0;
	double h = 0;
	double w = 0;
	double c = 0;
	
	printf("enter height\n");
	scanf("%lf",&h);
	printf("enter weight\n");
	scanf("%lf",&w);
	
	bsa = calc_bsa(h, w);
	
	printf("x1: %lf \n", bsa);
	
	return 0;	
}

double calc_bsa(double h,double w){
	return 0.0003207 * pow(h,0.3) * pow(w, (0.7285 - (0.0188 * log(w))) );
}