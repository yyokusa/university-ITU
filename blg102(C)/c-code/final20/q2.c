#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MOVIES 10
#define MAX_TITLE 100

//add your functions and struct definition here.
typedef struct Movie
{
    char title[MAX_TITLE];
    int purchase;
    double rating;
} Movie;

int get_purchases(Movie *movies, char *movie_title);
int add_movie(Movie *movies, char *movie_title, double movie_rating);
int compute_rating(Movie *movies, char *movie_title, double movie_rating);


int main()
{
	//there are initially two elements in the array. 
    Movie movies[N_MOVIES] = { {"Spartacus", 9, 4.0}, {"Ben Hur", 5, 1.8}};
    
	char movie_title[MAX_TITLE];
    int movie_rating, menu_selection, result;
    char input;

    for (int i = 2; i < N_MOVIES; i++)
        movies[i].purchase = -1;

    printf("Welcome to the movie database.\n");
    do {
        printf("Enter your request (1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit):");
        scanf("%d", &menu_selection);

        if (menu_selection == 1) {
            printf("Enter the movie title:");
            scanf(" %[^\n]s", movie_title);

            result = get_purchases(movies, movie_title);
            if (result != -1) {
                printf("The movie %s has been purchased %d times.\n", movie_title, result);
            } else {
                printf("The movie %s could not be found in the database.\n", movie_title);
            }
        }

        else if (menu_selection == 2) {
            printf("Enter the movie title:");
            scanf(" %[^\n]s", movie_title);

            printf("Enter the movie rating (out of 5):");
            scanf("%d", &movie_rating);

            while (movie_rating < 0 || movie_rating > 5) {
                printf("Enter the movie rating (out of 5):");
                scanf("%d", &movie_rating);
            }

            result = compute_rating(movies, movie_title, movie_rating);
            if (result == 0) {
                printf("The movie %s could not be found in the database. Would you like to add this movie (Y/N):", movie_title);
                scanf(" %c", &input);

                while (input != 'Y' && input != 'N') {
                    printf("Please enter a valid input (Y/N):");
                    scanf(" %c", &input);
                }

                if (input == 'Y') {
                    result = add_movie(movies, movie_title, movie_rating);
                    if (result == 1) {
                        printf("The movie %s is added to the database with a rating of %d.\n", movie_title, movie_rating);
                    } else {
                        printf("The movie %s could not be added to the database.\n", movie_title);
                    }
                }
            }
        }
    } while (menu_selection != 3);

    return EXIT_SUCCESS;
}


int get_purchases(Movie *movies, char *movie_title)
{
    for (size_t i = 0; i < N_MOVIES; i++)
    {
        if (strncmp((*(movies + i)).title, movie_title, MAX_TITLE) == 0)
        {
            return (*(movies + i)).purchase;
        }
    }
    return -1;
}


int compute_rating(Movie *movies, char *movie_title, double movie_rating)
{
    double new_rating = 0;
    double old_rating = 0;
    int number_of_purchases = get_purchases(movies, movie_title);
    if (number_of_purchases == -1)
    {
        return 0;
    }
    for (size_t i = 0; i < N_MOVIES; i++)
    {
        if (strncmp((*(movies + i)).title, movie_title, MAX_TITLE) == 0)
        {
            old_rating = (*(movies + i)).rating;
            double old_sum = old_rating * number_of_purchases;
            new_rating = (old_sum + movie_rating) / (number_of_purchases + 1);
            (*(movies + i)).rating = new_rating;
            (*(movies + i)).purchase = ((*(movies + i)).purchase) + 1;
            printf("The movie %s is updated.\r\n", (*(movies + i)).title);
            // printf("The number of purchases is %d.\r", (*(movies + i)).purchase);
            // printf("The rating is updated to %lf.\r", (*(movies + i)).rating);
            return (*(movies + i)).rating;
        }
    }    
    return 0;
}

int add_movie(Movie *movies, char *movie_title, double movie_rating)
{
    int counter = 0;
    int i = 0;
    while (strncmp((*(movies + i)).title, "", MAX_TITLE) != 0)
    {
        ++counter;
        ++i;
    }
    if (i == N_MOVIES - 1)
    {
        return 0;
    }
    strcpy((*(movies + i)).title, movie_title);
    (*(movies + i)).purchase = 1;
    (*(movies + i)).rating = movie_rating;
    return 1;
}
