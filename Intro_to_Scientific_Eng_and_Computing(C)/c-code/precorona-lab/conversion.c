#include <stdio.h>

double conversion(double);

int main() {
	
	double fahre = 0;
	double result = 0;
	printf("enter fahrenheit\n");
	scanf("%lf",&fahre);
	result = conversion(fahre);
	printf("result: %lf \n", result);
	return 0;	
}

double conversion(double fahre){
	return (fahre - 32) * ((double)5 / (double)9);;
}


