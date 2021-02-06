#include <stdio.h>
#include <math.h>

double discriminant(double,double,double);

int main() {
	
	double disc = 0;
	double x1 = 0;
	double x2 = 0;
	double a = 0;
	double b = 0;
	double c = 0;
	
	printf("enter a\n");
	scanf("%lf",&a);
	printf("enter b\n");
	scanf("%lf",&b);
	printf("enter c\n");
	scanf("%lf",&c);
	
	disc = discriminant(a,b,c);
	
	x1 = ( (-b) + sqrt(disc) ) / (2 * a);
	x2 = ( (-b) - sqrt(disc) ) / (2 * a);
	
	printf("x1: %lf \n", x1);
	printf("x2: %lf \n", x2);
	
	return 0;	
}

double discriminant(double num1,double num2,double num3){
	return pow(num2,2) - 4 * (num1* num3);
}