#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
	// for (int i = 0; i < argc; ++i){
	// 	printf("%s\n", argv[i]);
	// }

	// char* myargs[3] = {"some", "random", "strings"};
	// for (int i = 0; i<3;++i)
	// 	printf("%s", myargs[i]);

	char** myargs = (char**) malloc(4 * sizeof(char*));
	for (int i = 0; i<4;++i)
		myargs[i] = (char*) malloc(10 * sizeof(char));
	
	// int **parking_area = (int **)malloc(ROW * sizeof(int *));
    // for (int i = 0; i < ROW; i++)
    //     parking_area[i] = (int *)malloc(COL * sizeof(int));

	for (int i = 0; i<4;++i){
		scanf("%s", myargs[i]);	
		printf("%s\n", myargs[i]);	
	}
	
	for (int i = 0; i<4;++i)
		free(myargs[i]);
	free(myargs);

	return 0;
}

