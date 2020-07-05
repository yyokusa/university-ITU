//this one is ugly, shallow etc..

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 16

struct key
{
    int no;
    int counter;
};

struct record
{
    int no;
    char first_name[25];
    char sec_name[25];
    int g1;
    int g2;
    int g3;
};

typedef struct key Key;
typedef struct record Record;

void read_record(FILE *data_file, Key wantedKey, Record *stored_record);
_Bool search_record(FILE *data_file, Key wantedKey);
void create_latest_records_file(FILE *fxref, FILE *fdata);
void delete_record(FILE *, FILE *, Key);
void update_record(FILE *fxref, FILE *fdata, Key wantedKey);

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("something went wrong!! \n");
        return EXIT_FAILURE;
    }
    FILE *fxref = NULL;
    FILE *fdata = NULL;
    printf("%s \n", argv[1]);
    printf("%s \n", argv[2]);
    if ((fxref = fopen(argv[1], "r+")) == NULL)
    {
        printf("something went wrong while opening xref file!! \n");
        return EXIT_FAILURE;
    }
    if ((fdata = fopen(argv[2], "r+")) == NULL)
    {
        printf("something went wrong while opening data file!! \n");
        return EXIT_FAILURE;
    }
    Key wantedKey = {0, 0};
    Record stored_record = {0, "", 0, 0, 0};
    fscanf(fxref, "%d%d", &wantedKey.no, &wantedKey.counter);
    printf("wanted key no: %d %d\n", wantedKey.no, wantedKey.counter);
    read_record(fdata, wantedKey, &stored_record);
    puts("out of func");
    printf("%d %s %s %d %d %d \n", stored_record.no, stored_record.first_name, stored_record.sec_name, stored_record.g1, stored_record.g2, stored_record.g3);

    rewind(fxref);
    rewind(fdata);
    create_latest_records_file(fxref, fdata);
    // fseek(fdata, 0, SEEK_END);
    // fprintf(fdata, "\nhello world!!!");

    rewind(fxref);
    rewind(fdata);
    delete_record(fxref, fdata, wantedKey);


    rewind(fxref);
    rewind(fdata);
    fscanf(fxref, "%d%d", &wantedKey.no, &wantedKey.counter);
    printf("wanted key no: %d %d\n", wantedKey.no, wantedKey.counter);
    fscanf(fxref, "%d%d", &wantedKey.no, &wantedKey.counter);
    printf("wanted key no: %d %d\n", wantedKey.no, wantedKey.counter);
    fscanf(fxref, "%d%d", &wantedKey.no, &wantedKey.counter);
    printf("wanted key no: %d %d\n", wantedKey.no, wantedKey.counter);
    update_record(fxref, fdata, wantedKey);

    fclose(fxref);
    fclose(fdata);
    return 0;
}

// determine if file includes a specified record
_Bool search_record(FILE *data_file, Key wantedKey)
{
    int counter = 1;
    FILE *fptr = data_file;
    Record dummy_record = {0, "", 0, 0, 0};

    while ((fscanf(fptr, "%d %s %s %d %d %d ", &dummy_record.no, dummy_record.first_name, dummy_record.sec_name, &dummy_record.g1, &dummy_record.g2, &dummy_record.g3)) != EOF)
    {
        if (dummy_record.no == wantedKey.no && counter == wantedKey.counter)
        {
            printf("%d %s %s %d %d %d \n", dummy_record.no, dummy_record.first_name, dummy_record.sec_name, dummy_record.g1, dummy_record.g2, dummy_record.g3);
            return true;
        }
        else if (dummy_record.no == wantedKey.no && counter != wantedKey.counter)
        {
            printf("incrementing counter %d\n", counter);
            ++counter;
        }
    }
    return false;
}

// read a specified record and store in the given address
void read_record(FILE *data_file, Key wantedKey, Record *stored_record)
{
    int counter = 1;
    int flag = -1;
    FILE *fptr = data_file;
    Record dummy_record = {0, "", 0, 0, 0};

    while ((fscanf(fptr, "%d %s %s %d %d %d ", &dummy_record.no, dummy_record.first_name, dummy_record.sec_name, &dummy_record.g1, &dummy_record.g2, &dummy_record.g3)) != EOF)
    {
        // fscanf(fptr,"%d %s %s %d %d %d ", &dummy_record.no, dummy_record.first_name, dummy_record.sec_name, &dummy_record.g1, &dummy_record.g2, &dummy_record.g3);
        // printf("counter: %d\n", counter);
        // printf("wanted key counter: %d\n", wantedKey.counter);
        if (dummy_record.no == wantedKey.no && counter == wantedKey.counter)
        {
            // printf("dummy record no: %d\n", dummy_record.no);
            flag = 1;
            stored_record->no = dummy_record.no;
            strcpy(stored_record->first_name, dummy_record.first_name);
            strcpy(stored_record->sec_name, dummy_record.sec_name);
            stored_record->g1 = dummy_record.g1;
            stored_record->g2 = dummy_record.g2;
            stored_record->g3 = dummy_record.g3;
            // printf("%d %s %s %d %d %d \n", dummy_record.no, dummy_record.first_name, dummy_record.sec_name, dummy_record.g1, dummy_record.g2, dummy_record.g3);
            // printf("%d %s %s %d %d %d \n", stored_record->no, stored_record->first_name, stored_record->sec_name, stored_record->g1, stored_record->g2, stored_record->g3);
            break;
        }
        else if (dummy_record.no == wantedKey.no && counter != wantedKey.counter)
        {
            printf("incrementing counter %d\n", counter);
            ++counter;
        }
    }
}

// create a file from every students last records
void create_latest_records_file(FILE *fxref, FILE *fdata)
{
    FILE *new_file = NULL;
    if ((new_file = fopen("latest_records.txt", "w")) == NULL)
    {
        puts("something went wrong!!");
        exit(1);
    }

    Key wantedKey;
    while ((fscanf(fxref, "%d%d", &(wantedKey.no), &(wantedKey.counter))) != EOF)
    {
        rewind(fdata);
        printf("%d %d\n", wantedKey.no, wantedKey.counter);
        Record new_record;
        read_record(fdata, wantedKey, &new_record);
        // printf("%d %s %s %d %d %d\n", new_record.no, new_record.first_name, new_record.sec_name, new_record.g1, new_record.g2, new_record.g3);
        fprintf(new_file, "%d %s %s %d %d %d\n", new_record.no, new_record.first_name, new_record.sec_name, new_record.g1, new_record.g2, new_record.g3);
    }
    fclose(new_file);
}

// realize a delete functionality by creating new file without the specified record (rename it with the old file name)
void delete_record(FILE *fxref, FILE *fdata, Key wantedKey)
{
    FILE *new_file = NULL;
    int counter = 1;
    if ((new_file = fopen("new.txt", "w")) == NULL)
    {
        puts("something went wrong!!");
        exit(1);
    }

    Record new_record;
    rewind(fdata);
    while ((fscanf(fdata, "%d %s %s %d %d %d\n", &(new_record.no), (new_record.first_name), (new_record.sec_name), &(new_record.g1), &(new_record.g2), &(new_record.g3))) != EOF)
    {
        // printf("%d %s %s %d %d %d\n", new_record.no, new_record.first_name, new_record.sec_name, new_record.g1, new_record.g2, new_record.g3);
        if (new_record.no == wantedKey.no && wantedKey.counter == counter)
        {
            continue;
        }
        else if (new_record.no == wantedKey.no && wantedKey.counter != counter)
        {
            ++counter;
        }
        fprintf(new_file, "%d %s %s %d %d %d\n", new_record.no, new_record.first_name, new_record.sec_name, new_record.g1, new_record.g2, new_record.g3);
    }

    rename("new.txt", "data2.txt");
    fclose(new_file);
}

void update_record(FILE *fxref, FILE *fdata, Key wantedKey)
{
    FILE *new_file = NULL;
    int counter = 1;
    int line_counter = 1;
    int line = 1;
    int flag = 1;
    if ((new_file = fopen("updated.txt", "w")) == NULL)
    {
        puts("something went wrong!!");
        exit(1);
    }

    Record new_record;
    rewind(fdata);
    while ((fscanf(fdata, "%d %s %s %d %d %d\n", &(new_record.no), (new_record.first_name), (new_record.sec_name), &(new_record.g1), &(new_record.g2), &(new_record.g3))) != EOF)
    {
        // printf("%d %s %s %d %d %d\n", new_record.no, new_record.first_name, new_record.sec_name, new_record.g1, new_record.g2, new_record.g3);
        if (new_record.no == wantedKey.no && wantedKey.counter == counter)
        {
            flag = 0;
            break;
        }
        else if (new_record.no == wantedKey.no && wantedKey.counter != counter)
        {
            ++counter;
            if (flag){
                ++line;
                puts("updating lines");
            }
        }
        else
        {
            if (flag){
                ++line;
                puts("updating lines");
            }
        }
        fprintf(new_file, "%d %s %s %d %d %d\n", new_record.no, new_record.first_name, new_record.sec_name, new_record.g1, new_record.g2, new_record.g3);
    }
    
    
    Record cool_record;
    // printf("enter record: \n");
    char c;
    while((c = getchar()) == '\n');// there is still chars in buffer, fix it
    scanf("%d %s %s %d %d %d\n", &(cool_record.no), (cool_record.first_name), (cool_record.sec_name), &(cool_record.g1), &(cool_record.g2), &(cool_record.g3));
    fprintf(new_file, "%d %s %s %d %d %d\n", (cool_record.no), (cool_record.first_name), (cool_record.sec_name), (cool_record.g1), (cool_record.g2), (cool_record.g3));

    while ((fscanf(fdata, "%d %s %s %d %d %d\n", &(new_record.no), (new_record.first_name), (new_record.sec_name), &(new_record.g1), &(new_record.g2), &(new_record.g3))) != EOF)
    {
        fprintf(new_file, "%d %s %s %d %d %d\n", new_record.no, new_record.first_name, new_record.sec_name, new_record.g1, new_record.g2, new_record.g3);
    }

    rename("updated.txt", "data3.txt");
    fclose(new_file);
}
