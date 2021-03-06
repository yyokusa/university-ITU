#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
   char *str;

   /* Initial memory allocation */
   str = (char *) malloc(15);
   str = "tutorialspoint"; //error, realloc needs allocated ptr
   //scanf("%s", str); //works fine
   //gets(str);       //works fine
   //strcpy(str, "tutorialspoint"); //works fine
   printf("String = %s,  Address = %p\n", str, str);

   /* Reallocating memory */
   str = (char *) realloc(str, 25);
   strcat(str, ".com");
   printf("String = %s,  Address = %p\n", str, str);

   free(str);
   
   return(0);
}