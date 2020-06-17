/**
 * Objective of this program is finding the best parking slot for the car in a parking area.
 *
 * Yasin Abdülkadir Yokuş
 * 150190739
 */
#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

#define MAX_DISTANCE 50 * 50 + 1

//Global Variables
int row_index = 0;
int col_index = 0;

// function prototypes
int get_size();
int get_num_of_cars();

int **init_parking_area(int);
int **init_distances_matrix(int);

void fill_defaults(int **, int);
void fill_max_distances(int **, int);

void calculate_distances(int **, int, int **);
void calculate_indexes(int **, int);
int calc_distance(int, int, int, int);

void freedom(int **, int);

int main()
{
    int size;
    size = get_size();

    int num_of_cars;
    num_of_cars = get_num_of_cars();
    if (num_of_cars >= size * size)
    {
        printf("Best Slot Found In: %d %d\n", 0, 0);
        return EXIT_SUCCESS;
    }
    if (num_of_cars == 0)
    {
        printf("Best Slot Found In: %d %d\n", 1, 1);
        return EXIT_SUCCESS;
    }

    int **parking_area;
    parking_area = init_parking_area(size);
    fill_defaults(parking_area, size);

    // Fill cars into parking space
    int x, y;
    int counter = 0;
    int is_there_any_car_inside = 0;
    while (counter < num_of_cars)
    {
        printf("Locations: ");
        scanf("%d %d", &x, &y);
        if (x > size || x <= 0 || y > size || y <= 0)
        {
            ++counter;
            continue;
        }
        if (parking_area[size - y][x - 1] == 1)
        {
            ++counter;
            continue;
        }
        is_there_any_car_inside = 1;
        parking_area[size - y][x - 1] = 1;
        ++counter;
    }
    if (!(is_there_any_car_inside))
    {
        printf("Best Slot Found In: 1 1\n");
        return EXIT_SUCCESS;
    }

    int **distances_matrix;
    distances_matrix = init_distances_matrix(size);
    fill_max_distances(distances_matrix, size);
    calculate_distances(parking_area, size, distances_matrix);
    calculate_indexes(distances_matrix, size);

    printf("Best Slot Found In: %d %d\n", col_index + 1, size - row_index);

    // Free dynamically allocated memory
    freedom(parking_area, size);
    freedom(distances_matrix, size);
    return EXIT_SUCCESS;
}
/** 
 * Calculates manhattan distances from free slots to closest cars 
 * 
 * @param parking_area 2D matrix representing parking area
 * @param size represents size of the (size x size) matrix 
 * @param distances_matrix represents individual slots' manhattan distances, MAX_DISTANCE in case slot is occupied 
 * @return Null
 */
void calculate_distances(int **parking_area, int size, int **distances_matrix)
{

    int curr_distance = 0;
    for (int row = 0; row < size; row++) // Y
    {
        for (int col = 0; col < size; col++) // X
        {
            if (parking_area[row][col] != 1)
            {
                for (int i = 0; i < size; i++)
                { // i is row
                    for (int j = 0; j < size; j++)
                    { // j is column
                        if (parking_area[i][j] == 1)
                        {
                            curr_distance = calc_distance(row, i, col, j);
                            if (curr_distance < distances_matrix[row][col])
                            {
                                distances_matrix[row][col] = curr_distance;
                            }
                        }
                    }
                }
            }
        }
    }
}

/** 
 * Calculates row_index and col_index according to problem description,
 * which are the most suitable slot coordinates.
 * 
 * @param distances_matrix represents individual slots' manhattan distances, MAX_DISTANCE in case slot is occupied 
 * @param size represents size of the (size x size) matrix 
 * @return Null
 */
void calculate_indexes(int **distances_matrix, int size)
{
    int max_element = -1;
    for (int row = 0; row < size; row++) // Y
    {
        for (int col = size - 1; col >= 0; col--) // X
        {
            if (distances_matrix[row][col] != MAX_DISTANCE && distances_matrix[row][col] > max_element)
            {
                row_index = row;
                col_index = col;
                max_element = distances_matrix[row][col];
            }
            else if (distances_matrix[row][col] != MAX_DISTANCE && distances_matrix[row][col] == max_element)
            {
                if (col_index > col)
                {
                    row_index = row;
                    col_index = col;
                    max_element = distances_matrix[row][col];
                }
                else if (col_index == col)
                {
                    if (row_index < row)
                    {
                        row_index = row;
                        col_index = col;
                        max_element = distances_matrix[row][col];
                    }
                }
            }
        }
    }
}
/** 
 * Fills every index of distances_matrix with MAX_DISTANCE variable value
 * 
 * @param distances_matrix represents individual slots' manhattan distances, MAX_DISTANCE in case slot is occupied 
 * @param size represents size of the (size x size) matrix 
 * @return Null
 */
void fill_max_distances(int **distances_matrix, int size)
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            distances_matrix[row][col] = MAX_DISTANCE;
        }
    }
}
/** 
 * Initialize distances_matrix with dynamic memory allocation
 * 
 * @param size represents size of the (size x size) matrix 
 * @return distances_matrix
 */
int **init_distances_matrix(int size)
{
    const int ROW = size;
    const int COL = size;
    int **distances_matrix = (int **)malloc(ROW * sizeof(int *));
    for (int i = 0; i < ROW; i++)
        distances_matrix[i] = (int *)malloc(COL * sizeof(int));
    return distances_matrix;
}
/** 
 * Initialize parking_area with dynamic memory allocation
 * 
 * @param size represents size of the (size x size) matrix 
 * @return parking_area
 */
int **init_parking_area(int size)
{
    const int ROW = size;
    const int COL = size;
    int **parking_area = (int **)malloc(ROW * sizeof(int *));
    for (int i = 0; i < ROW; i++)
        parking_area[i] = (int *)malloc(COL * sizeof(int));
    // Note that arr[i][j] is same as *(*(arr+i)+j)
    return parking_area;
}
/** 
 * Fill default value 0 for every index of parking_area which represents free slots
 *
 * @param parking_area 2D matrix representing parking area
 * @param size represents size of the (size x size) matrix 
 * @return Null
 */
void fill_defaults(int **parking_area, int size)
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            parking_area[row][col] = 0;
        }
    }
}

/** 
 * Get the size of the parking area
 * 
 * @return size
 */
int get_size()
{
    int size;
    printf("Size: ");
    scanf("%d", &size);
    if (!(size <= 50 && size > 0))
    {
        printf("Size must be between 50 and 1");
        return get_size();
    }
    return size;
}
/** 
 * Get the number of cars inside parking area
 * 
 * @return num_of_cars
 */
int get_num_of_cars()
{
    int num_of_cars;
    printf("Cars: ");
    scanf("%d", &num_of_cars);
    return num_of_cars;
}

/** 
 * Calculate the Manhattan distance between point A and point B.
 *
 * @param a x coordinate of point A
 * @param b x coordinate of point B
 * @param c y coordinate of point A
 * @param d y coordinate of point B
 * @return res1 + res2 result of the manhattan distance calculation
 */
int calc_distance(int a, int b, int c, int d)
{
    int res1 = (a - b);
    int res2 = (c - d);
    if (res1 < 0)
        res1 = -res1;
    if (res2 < 0)
        res2 = -res2;
    return res1 + res2;
}
/** 
 * Free dynamically allocated memory
 *
 * @param dynamic_memory_to_free memory adress we will free
 * @param size represents size of the (size x size) matrix 
 * @return Null
 */
void freedom(int **dynamic_memory_to_free, int size)
{
    for (int i = 0; i < size; i++)
        free(dynamic_memory_to_free[i]);
    free(dynamic_memory_to_free);
}
