#include <stdio.h>
#include <math.h>

float find_distance(float, float);
void find_case(float*, float*);

int main(int argc, char const *argv[])
{
    float num_1;
    float num_2;
    printf("Enter num_1:\n");
    scanf("%f",&num_1);
    printf("Enter num2:\n");
    scanf("%f",&num_2);
    
    find_case(&num_1, &num_2);

    return 0;
}

float find_distance(float num_1, float num_2) {
    printf("num1: %.2f\n",num_1);
    printf("num2: %.2f\n",num_2);
    return sqrt( (num_1 * num_1) + (num_2 * num_2) );               // sqrt()  from <math.h> header
}
void find_case(float* num_1, float* num_2){
    float distance;
    distance = find_distance(*num_1, *num_2);
    printf("distance from origin: %.2f\n",distance);
    if (distance < 0.5)
    {
        printf("case a\n");
    } else if (0.5 == distance)
    {
        printf("case b\n");
    } else if (distance > 0.5)
    {
        printf("case c\n");
    }
}