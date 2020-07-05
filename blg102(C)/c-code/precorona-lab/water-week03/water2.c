#include <stdio.h>
#include <stdlib.h>
double turn_to_f(double c){
    return (32 + ((9.0/5) * c));
}
int main()
{
    double degree;
    char degree_type;
    printf("Enter temperature (end with F for Fahrenheit or C for Celsius): ");
    scanf("%lf %c",&degree, &degree_type);
    double altitude;
    printf("Enter altitude in meters: ");
    scanf("%lf",&altitude);

    double c_drop_for_alt = altitude / 300.0;
    double f_drop_for_alt = turn_to_f(c_drop_for_alt);

    if(degree_type == 'F') {
		//statements;
		if(degree < (212 - f_drop_for_alt) && degree > (32 - f_drop_for_alt)) {
			printf("Water is Liquid at %.2lf degrees Fahrenheit\n",degree);
		} else if(degree >= (212 - f_drop_for_alt)) {
			printf("Water is Gas (Vapor) at %.2lf degrees Fahrenheit\n", degree);
		} else 
			printf("Water is Solid (Ice) at %.2lf degrees Fahrenheit\n",degree);
	} 
	else if (degree_type == 'C') {
		//statements;
		if(degree < (100 - c_drop_for_alt) && degree > (0 - c_drop_for_alt)) {
			printf("Water is Liquid at %.2lf degrees Celsius\n",degree);
		} else if(degree >= (100 - c_drop_for_alt)) {
			printf("Water is Gas (Vapor) at %.2lf degrees Celsius\n",degree );
		} else 
			printf("Water is Solid (Ice) at %.2lf  degrees Celsius\n",degree);
	}
	else {
		printf("Please enter temperature unit as either C or F.\n");
		return EXIT_FAILURE;
	}
    return 0;
}