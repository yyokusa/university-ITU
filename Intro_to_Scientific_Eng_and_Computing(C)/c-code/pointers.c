POINTERS I
************************************************************
C string functions

-strlen(s)
-strcpy(t, s) copies characters from s into t
-strncpy(t, s, n) copies at most n characters from s into t
-strcat(t, s) Appends the characters from s after the end of the characters in t
-strncat(t, s, n) Appends at most n characters from s after the end of the characters in t
-strcmp(str1, str2) Returns 0 if str1 and str2 have the same contents, a negative if str1 comes before str2 in lexicographic order, a positive integer otherwise

************************************************************
1. Every call to malloc must be matched
by exactly one call to free.
2. Use free to delete dynamically allocated memory.
And always assign NULL to the pointer after that.
3. Don’t access a memory block
after it has been deleted.
If you don’t follow these rules, your program can
crash or run unpredictably.

************************************************************
DANGLING
Dangling pointers are when you use a pointer that
has already been deleted or was never initialized.

The value in an uninitialized or
deleted pointer might point somewhere
in the program you have
no right to be accessing.
You can create real damage by
writing to the location to which it points.
Even just reading from that location
can crash your program.



Always initialize pointer variables.
• If you can’t initialize them with the return value
of new or the & operator, then set them to NULL.
• Never use a pointer that has been deleted.
************************************************************
LEAKS
A memory leak is when you alolocate dynamic
memory but you fail to free it when you are done.


Remember Rule #1.
1. Every call to malloc must be matched
by exactly one call to free.
And after freeing, set it to NULL so
that it can be tested for danger later.

int* values = malloc(n * sizeof(int));
// Process values
free(values);
values = NULL;
...
if (values == NULL) ...
