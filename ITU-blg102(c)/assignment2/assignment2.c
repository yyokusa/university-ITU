/**
 * Objective of this program is tracking the game score of a dart player.
 *
 * Yasin Abdülkadir Yokuş
 * 150190739
 */
#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS EXIT_FAILURE

// global variable
int target = 0;

// function prototypes
int point_value_of_the_throw(int, char);
int get_rem_after_throw(int, int, char);

int main() {
    int current_score = 0;
    int segment = 0;
    char ring;
    printf("Target: ");
    scanf("%d",&target);
    current_score = target;

    do{
        printf("Throw: ");
        scanf("%d %c", &segment, &ring);
        current_score = get_rem_after_throw(current_score, segment, ring);
        printf("Points: %d\n", current_score);
    }while (current_score != 0);

    return EXIT_SUCCESS;
}
/** 
 * Returns the remaining number by subtracting point value of a throw
 * from the current score
 * 
 * @param current_score current score of the player
 * @param segment dart board segment represented by a number
 * @param ring is one of the rings of the dart board
 * @return new score as an integer value
 */
int get_rem_after_throw(int current_score, int segment, char ring) {
    int new_score = 0;
    int point_value = 0;
    
    //short circuit eval.
    if (current_score == target && ring != 'D') {
        return current_score;
    }

    point_value = point_value_of_the_throw(segment, ring);
    new_score = current_score - point_value;
    
    if ((new_score == 1) || (new_score < 0)) {
        new_score += point_value;
        return new_score;
    }

    if(new_score == 0) {
        if (ring == 'D') {
            return 0;
        } else{
            new_score += point_value;
            return new_score;
        }
    } 
    return new_score;
}
/** 
 * Calculate the achieved score point by throwing a dart with specified
 * segment and ring
 * 
 * @param segment dart board segment represented by a number
 * @param ring is one of the rings of the dart board
 * @return achieved score as an integer value
 */
int point_value_of_the_throw(int segment,char ring) {
    int point_value = 0;
    switch (ring) {
    case 'S':
        point_value = segment;
        break;
    case 'D':
        point_value = 2 * segment;
        break;
    case 'T':
        point_value = 3 * segment;
        break;
    case 'O':
        point_value = 25;
        break;
    case 'I':
        point_value = 50;
        break;
    default:
        break;
    }
    return point_value;
}