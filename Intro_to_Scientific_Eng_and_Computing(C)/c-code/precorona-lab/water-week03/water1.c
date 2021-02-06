#include <stdio.h>
#include <stdlib.h>

int main() {
	
	double degree_val;
	char degree_type;
	printf("Enter temperature (end with F for Fahrenheit or C for Celsius): ");
	scanf("%lf %c",&degree_val,&degree_type);
	
	if(degree_type == 'F') {
		//statements;
		if(degree_val < 212 && degree_val > 32) {
			printf("Water is Liquid at %.2lf degrees Fahrenheit\n",degree_val );
		} else if(degree_val >= 212) {
			printf("Water is Gas (Vapor) at %.2lf degrees Fahrenheit\n", degree_val);
		} else 
			printf("Water is Solid (Ice) at %.2lf degrees Fahrenheit\n",degree_val);
	} 
	else if (degree_type == 'C') {
		//statements;
		if(degree_val < 100 && degree_val > 0) {
			printf("Water is Liquid at %.2lf degrees Celsius\n",degree_val);
		} else if(degree_val >= 100) {
			printf("Water is Gas (Vapor) at %.2lf degrees Celsius\n",degree_val );
		} else 
			printf("Water is Solid (Ice) at %.2lf  degrees Celsius\n",degree_val);
	}
	else {
		printf("Please enter temperature unit as either C or F.\n");
		return EXIT_FAILURE;
	}
	return 0;
}