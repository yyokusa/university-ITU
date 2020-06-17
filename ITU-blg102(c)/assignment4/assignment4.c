/**
 * Objective of this program is finding the secret message from a book by following instructions.
 *
 * Yasin Abdülkadir Yokuş
 * 150190739
 */

#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <string.h>
#include <ctype.h> // ispunct

#define LINES 10000
#define CHARS 200

struct instruction_s
{
    int step;
    int index;
};
typedef struct instruction_s Instructions;

Instructions *allocate_mem_for_instruction_arr();
int read_instructions_into_array(FILE *fptr_instructions, Instructions *instructions_arr);
char **allocate_mem_for_book();
void read_book_into_array(FILE *alice, char **book);
void clear_text(char *str);
void get_sentence(char **lines, Instructions *instructions, int n_instructions, char *sentence);
char *get_word(char *line, int index, char *word);
void freedom(char **dynamic_memory_to_free);

int main(int argc, char **argv)
{

    if (argc != 3)
    {
        puts("something wrong!");
        return EXIT_FAILURE;
    }

    char **book = allocate_mem_for_book(); //free this
    FILE *alice = NULL;
    if ((alice = fopen(argv[1], "r")) == NULL)
    {
        puts("Could not open alice file");
        return EXIT_FAILURE;
    }
    else
    {
        read_book_into_array(alice, book);
        fclose(alice);
    } //end else

    FILE *fptr_instructions = NULL;
    int i = 0;
    Instructions *instructions_arr = allocate_mem_for_instruction_arr(); //free this
    if ((fptr_instructions = fopen(argv[2], "r")) == NULL)
    {
        puts("Could not open instructions file");
        return EXIT_FAILURE;
    }
    else
    {
        i = read_instructions_into_array(fptr_instructions, instructions_arr);
        fclose(fptr_instructions);
    } //end else

    //this will be the final super secret full message
    char sentence[CHARS] = {'\0'};

    // put secret thing inside sentence
    get_sentence(book, instructions_arr, i, sentence);

    // print the final super secret full message
    printf("%s\n", sentence);

    //free dynamically allocated mem
    freedom(book);
    free(instructions_arr);

    return EXIT_SUCCESS;
}

/** 
 * Fills the book lines into an 2D array
 * 
 * @param alice file pointer which holds a pointer to the book alice
 * @param book represents the 2D array we will fill with the book lines
 * @return Null
 */
void read_book_into_array(FILE *alice, char **book)
{
    int i = 0;
    while (fgets(book[i], CHARS, alice) != NULL)
    {                                          //this func puts '\0' at the end of line itself...
        clear_text(book[i]); // send a line and fix it book[i] is a line from the book[][] array of strings
        i++;
    }
}

/** 
 * Create a Dynamically allocated memory block for a 2D array
 * 
 * @return dynamically allocated memory block
 */
char **allocate_mem_for_book()
{
    char **book = (char **)malloc(LINES * sizeof(char *));
    for (int i = 0; i < LINES; i++)
        book[i] = (char *)malloc(CHARS * sizeof(char));
    return book;
}

/** 
 * Stores instructions into an array of Instructions structs
 * 
 * @param fptr_instructions file pointer which holds a pointer to the instructions text file
 * @param instructions_arr array we store instructions
 * @return number of instructions
 */
int read_instructions_into_array(FILE *fptr_instructions, Instructions *instructions_arr)
{
    int i = 0;
    while (fscanf(fptr_instructions, "%d %d", &instructions_arr[i].step, &instructions_arr[i].index) == 2)
    {
        ++i;
    }
    return i;
}

/** 
 * Dynamically Allocates memory for instruction array
 * 
 * @return address of the dynamically allocated memory for array of Instruction structs
 */
Instructions *allocate_mem_for_instruction_arr()
{
    Instructions *instructions_arr = (Instructions *)malloc(sizeof(Instructions) * LINES);
    return instructions_arr;
}

/**
 *  Removes all punctuation marks attached to the words and convert all upper case letters to lower case.
 *
 * @param str String which represents a line to be evaluated.
 * @return NULL
 */
void clear_text(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] >= 'a' && str[i] <= 'z'))
        {
            continue;
        }
        else if ((str[i] >= 'A' && str[i] <= 'Z'))
        {
            str[i] = str[i] + ('a' - 'A');
            continue;
        }
        else if (isdigit(str[i]))
        {
            continue;
        }
        else if (ispunct(str[i]))
        {
            str[i] = 'X';
        }
        else
        {
            str[i] = ' ';
        }
    }

    int left = 0;
    int right = 0;
    while (str[right] != '\0')
    {
        if (str[right] != 'X')
        {
            str[left] = str[right];
            ++left;
        }
        ++right;
    }
    str[left] = '\0';
}

/**
 *  Detect the word by using the line and index number from the given instructions
 *
 *  @param line adress of the line.
 *  @param index index of the word wanted.
 *  @param word an array of chars to store the wanted word.
 *  @return wanted secret word.
 */
char *get_word(char *line, int index, char *word)
{
    int word_counter = 0;
    int word_index = 0;

    int i = 0;
    while (word_counter != index && i < strlen(line))
    {
        if (line[i] == ' ')
        {
            ++i;
            continue;
        }
        else
        {
            word_index = i;
            ++word_counter;
            while (line[i] != ' ')
            {
                ++i;
            }
        }
    }
    // now we're at the 0th index of the word we want
    int k = word_index;
    int a = 0;
    while (line[k] != ' ')
    {
        word[a++] = line[k++];
    }
    word[a] = '\0';
    return word;
}

/**
  *  Create the sentence by using the given instructions
  *
  *  @param book 2D Array represents addresses of strings
  *  @param instructions array of Instructions struct.
  *  @param n_instructions number of instructions.
  *  @return sentence wanted secret sentence.
  */
void get_sentence(char **book, Instructions *instructions, int n_instructions, char *sentence)
{
    int line = -1;
    for (int i = 0; i < n_instructions; i++)
    {
        //below line initiliazes char array full of '\0' --> not sure check this
        char word[CHARS] = {'\0'};
        line += instructions[i].step;
        strcat(sentence, get_word(book[line], instructions[i].index, word)); //Appending the requested word to the sentence
        strcat(sentence, " ");
    }
}

/**
 *  Return the memory taken from heap
 *
 *  @param dynamic_memory_to_free dynamic memory to be free
 *  @return NULL
 */
void freedom(char **dynamic_memory_to_free)
{
    for (int i = 0; i < LINES; i++)
        free(dynamic_memory_to_free[i]);
    free(dynamic_memory_to_free);
}