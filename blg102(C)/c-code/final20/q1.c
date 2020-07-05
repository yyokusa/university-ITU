// passes all calico tests
#include <stdio.h>
//You cannot use the string library 

#define MAX_STRING_SIZE 20

int str_len(char* a);


void append(char* a, char* b)
{
  //fill the function body. Do not change the arguments and the return parameter
	char *ptr = a;
	while (*ptr != '\0')
	{
		ptr++;
	}
	*ptr++ = ' ';
	char *ptr2 = b;
	while (*ptr2 != '\0')
	{
		*ptr = *ptr2;
		ptr++;
		ptr2++;
	}
	*ptr = '\0';
	printf("%s ",a);
  return;
}

int main()
{
	char a[MAX_STRING_SIZE] = {'\0'};
	char b[MAX_STRING_SIZE] = {'\0'};
	scanf("%s",a);
	scanf("%s",b);
	// int asize = sizeof(a) / sizeof(a[0]);
	// int bsize = sizeof(b) / sizeof(b[0]);
	int asize = str_len(a);
	int bsize = str_len(b);
	// printf("%d", asize);
	// printf("%d", bsize);
	if ((MAX_STRING_SIZE - asize) < bsize)
	{
		printf("Error");
		return 0;
	}
	append(a,b);
	return 0;
}


int str_len(char* a)
{
	// puts("in");
	char *ptr = a;
	int len = 0;
	while(*ptr++ != '\0')
	{
		++len;
	}
	// puts("out");
	return len + 1;
}