#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	double c_door;
	double w_l_array[1000] = {};
	for (int i = 0; i < 1000; ++i)
	{
		c_door = (rand() % 3);
		if (c_door == 1)
		{
			w_l_array[i] = 1 / 3.0;
		}
		else if (c_door != 1)
		{
			w_l_array[i] = 2 / 3.0;
		}
	}
	double sum_1 = 0;
	double sum_2 = 0;
	for (int i = 0; i < 1000; ++i)
	{
		if (w_l_array[i] == 1 / 3.0)
		{
			sum_1++;
		}
		else if (w_l_array[i] == 1 / 6.0)
		{
			sum_2++;
		}
	}
	printf("%lf\n", sum_2);
	printf("%lf\n", sum_1);
	return 0;
}
