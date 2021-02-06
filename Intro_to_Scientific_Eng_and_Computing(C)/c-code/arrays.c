// Common Algorithms – Copying
int squares[5] = {0, 1, 4, 9, 16};
int lucky_numbers[5];
for (int i = 0; i < 5; i++)
{
    lucky_numbers[i] = squares[i];
}

// ************************************************************
// Common Algorithms – Sum and Average Value
// You have already seen the algorithm
// for computing the sum and average of set of data.
// The algorithm is the same when the data is stored in an array.
double total = 0;
for (int i = 0; i < size of values; i++)
{
    total = total + values[i];
}
// The average is just arithmetic:
double average = total / size of values;

// ************************************************************
// Common Algorithms – Maximum and Minimum
// To compute the largest value in an array, keep a variable
// that stores the largest element that you have encountered,
// and update it when you find a larger one.
double largest = values[0];
for (int i = 1; i < size of values; i++)
{
    if (values[i] > largest)
    {
        largest = values[i];
    }
}

// ************************************************************
// Common Algorithms – Maximum and Minimum
// For the minimum, we just reverse the comparison.
double smallest = values[0];
for (int i = 1; i < size of values; i++)
{
    if (values[i] < smallest)
    {
        smallest = values[i];
    }
}
// These algorithms require that the array
// contain at least one element.

// ************************************************************
// Common Algorithms – Linear Search
// Find the position of a certain value, say 100, in an array:
int pos = 0;
bool found = false;
while (pos < size of values && !found)
{
    if (values[pos] == 100)
    {
        found = true;
    }
    else
    {
        pos++;
    }
}
// Don’t get these tests
//     in the wrong order !

    // ************************************************************
    Common Algorithms – Removing an Element,
    Unordered
        Suppose you want to remove the element at index i.If the elements in the array are not in any particular order,
    that task is easy to accomplish.Simply overwrite the element to be removed with the last
        element of the array,
    then remove the value that was
        copied by shrinking the size of the array.

    Common Algorithms – Removing an Element,
    Unordered
        values[pos] = values[current_size - 1];
current_size--;

************************************************************Common Algorithms – Removing an Element, Ordered The situation is more complex if the order of the elements matters.Then you must move all elements following the element to be removed “down” (to a lower index), and then remove 
the last element by shrinking the size.
for (int i = pos + 1; i < current_size; i++)
{
    values[i - 1] = values[i];
}
current_size--;

************************************************************Common Algorithms – Inserting an Element Ordered 
if (current_size < CAPACITY)
{
    current_size++;
    for (int i = current_size - 1; i > pos; i--)
    {
        values[i] = values[i - 1];
    }
    values[pos] = new_element;
}

************************************************************
Common Algorithms – Swapping Elements 
double temp = values[i];
values[i] = values[j];
values[j] = temp;

Common Algorithms – Reading Input
    If the know how many input values the user will supply,
    you can store them directly into the array : 
double values[NUMBER_OF_INPUTS];
for (i = 0; i < NUMBER_OF_INPUTS; i++)
{
    printf("%lf", &values[i]);
}

************************************************************Common Algorithms – Reading Input
                                                               When there will be an arbitrary number of inputs,
    things get more complicated.Add values to the end of the array until all inputs have been made.Again, the companion variable will have the number of inputs.

double values[CAPACITY];
int current_size = 0;
double input;
scanf("%lf", &input);
while (input > 0)
{
    if (current_size < CAPACITY)
    {
        values[current_size] = input;
        current_size++;
    }
    scanf("%lf", &input);
}
************************************************************Arrays as Parameters in Functions
Recall that when we work with arrays
we use a companion variable.The same concept applies when using arrays as parameters : You must pass the size to the function
so it will know how many elements to work with.
************************************************************
Here is the sum function with an array parameter : Notice that to pass one array,
    it takes two parameters.
    
    
double sum(double data[], int size)
{
    double total = 0;
    for (int i = 0; i < size; i++)
    {
        total = total + data[i];
    }
    return total;
}
************************************************************
Arrays as Parameters in Functions
When you call the function,
supply both the name of the array and the size :

double NUMBER_OF_SCORES = 10;
double scores[NUMBER_OF_SCORES] = {32, 54, 67.5, 29, 34.5, 80, 115, 44.5, 100, 65};

double total_score = sum(scores, NUMBER_OF_SCORES);

************************************************************You can pass an array into a function but you cannot return an array.

* ***********************************************************Arrays as Parameters in Functions
If you cannot return an array,
how can the caller get the data ?

Arrays as Parameters in Functions
The caller must provide an array to be used:
void squares(int n, int result[])
{
    for (int i = 0; i < n; i++)
    {
        result[i] = i * i;
    }
}
************************************************************
Arrays as Parameters in Functions
A function can change the size of an array.It should let the caller know of any change
by returning the new size.

int read_inputs(double inputs[], int capacity)
{
    int current_size = 0;
    double input;
    scanf("%lf", &input);
    while (input > 0)
    {
        if (current_size < capacity)
        {
            inputs[current_size] = input;
            current_size++;
        }
        scanf("%lf", &input);
    }
    return current_size;
}
************************************************************
Arrays as Parameters in Functions
The following program uses the preceding functions to read
values from standard input,
double them, and print the result.
• The read_inputs function fills an array with the input values.It returns the number of elements that were read.
• The multiply function modifies the contents of the array that it receives, demonstrating that arrays can be 
changed inside the function to which they are passed.
• The print function does not modify the contents of the array that it receives.

* ***********************************************************
Two - Dimensional Arrays

An arrangement consisting of tabular data : rows and
columns of values is called : a two - dimensional array,
or a matrix.

************************************************************
Defining Two -
Dimensional Arrays

C uses an array with two subscripts to store a two -
dimensional array.

const int COUNTRIES = 7;
const int MEDALS = 3;
int counts[COUNTRIES][MEDALS];

An array with 7 rows and 3 columns
is suitable for storing our medal count data.


************************************************************
Defining Two-Dimensional Arrays – Unchangeable Size

Just as with one-dimensional arrays,
you cannot change the size of
a two-dimensional array once it has been defined.


But you can initialize a 2-D array:
int counts[COUNTRIES][MEDALS] =
{
{ 1, 0, 1 },
{ 1, 1, 0 },
{ 0, 0, 1 },
{ 1, 0, 0 },
{ 0, 1, 1 },
{ 0, 1, 1 },
{ 1, 1, 0 }
};
************************************************************
Two - Dimensional Array Parameters
When passing a two - dimensional array to a function,
you must specify the number of columns
as a constant when you write the parameter type.table[][COLUMNS] *
***********************************************************
This function computes the total of a given row.

const int COLUMNS = 3;
int row_total(int table[][COLUMNS], int row)
{
    int total = 0;
    for (int j = 0; j < COLUMNS; j++)
    {
        total = total + table[row][j];
    }
    return total;
}

************************************************************
int row_total(int table[][COLUMNS], int row)

In this function, to find the element table[row][j]
the compiler generates code
by computing the offset

(row * COLUMNS) + j

Leaving out the columns value is a very common error.
int row_total(int table[][], int row)
...
The compiler doesn’t know how “long” each row is!
************************************************************
Putting a value for the rows is not an error.

int row_total(int table[17][COLUMNS], int row)
...

The compiler just ignores whatever you place there.
************************************************************

The size of an array cannot be changed after it is created.
You have to get the size right – before you define an array.
The compiler has to know the size to build it.
and a function must be told about the number
elements and possibly the capacity.
It cannot hold more than it’s initial capacity.

************************************************************

When passing a two-dimensional array to a function,
you must specify the number of columns
as a ***************constant******************* when you write the parameter type.
table[][COLUMNS]
************************************************************
