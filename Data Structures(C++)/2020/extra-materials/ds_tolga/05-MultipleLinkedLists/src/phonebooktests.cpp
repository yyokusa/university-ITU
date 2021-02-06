#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h> /* time */

#include "phonebooktests.h"
#include "number_list.h"
#include "phonebookoperations.h"

void testphonebook()
{
    Phone_List phonelist;
    phonelist.create();
    read_fromfile(phonelist, "test_multilist_phonebook.dat");
    insert_test(phonelist, "Tolga", "123-41234 12312-2313 3432-42342");
    insert_test(phonelist, "Duygu", "231-3123123");
    search_test(phonelist, "Tolga");
    search_test(phonelist, "*");
    search_test(phonelist, "Murat");
    update_test(phonelist, 1, "Murat", "3123-123123 323-312311");
    search_test(phonelist, "*");
    search_test(phonelist, "Murat");
    clear_test(phonelist);
    search_test(phonelist, "*");
    insert_test(phonelist, "Tolga", "123-41234 12312-2313 3432-42342");
    insert_test(phonelist, "Duygu", "231-3123123");
    delete_test(phonelist, 2);
    delete_test(phonelist, 1);
    search_test(phonelist, "*");
    
    srand(clock());
    randomfill(phonelist, 10000);
    multi_read_test(phonelist, 5000);

    write_tofile(phonelist, "test_multilist_phonebook.dat");
    phonelist.clear();
    remove("test_multilist_phonebook.dat");
}

void multi_read_test(Phone_List &phonelist, int trials)
{

    const short namelen = 6;
    char name[namelen];

    clock_t start = clock();
    for (int i = 0; i < trials; i++)
    {
        randstr(name, namelen, 65, 26);
        phonelist.search(name);
    }

    clock_t end = clock();

    cout << "It took " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << " milliseconds to search for " << trials << " records" << endl;

    getchar();
}

void insert_test(Phone_List &phonelist, const char *name, const char *entry)
{
    Phone_Record newrecord;

    newrecord.name = new char[strlen(name) + 1];
    strcpy(newrecord.name, name);

    newrecord.numbers = new Number_List;
    newrecord.numbers->create();
    add_numbers(entry, newrecord.numbers);

    phonelist.insert(newrecord);
    delete[] newrecord.name;
}

void search_test(Phone_List &phonelist, const char *name)
{
    char *searchfor = new char[strlen(name) + 1];
    strcpy(searchfor, name);
    phonelist.search(searchfor);
    delete[] searchfor;
}

void update_test(Phone_List &phonelist, int no, const char *name, const char *entry)
{
    Phone_Record newrecord;

    newrecord.name = new char[strlen(name) + 1];
    strcpy(newrecord.name, name);

    newrecord.numbers = new Number_List;
    newrecord.numbers->create();
    add_numbers(entry, newrecord.numbers);

    phonelist.update(no, newrecord);

    delete[] newrecord.name;
}

void delete_test(Phone_List &phonelist, int no)
{
    phonelist.remove(no);
}

void clear_test(Phone_List &phonelist)
{
    phonelist.clear();
}

void randomfill(Phone_List &phonelist, int numofrecords)
{

    const short namelen = 6;
    char name[namelen];
    Phone_Record newrecord;
    newrecord.name = new char[namelen];

    for (int i = 0; i < numofrecords; i++)
    {
        randstr(name, namelen, 65, 26);

        strcpy(newrecord.name, name);
        newrecord.numbers = new Number_List;
        newrecord.numbers->create();
        add_numbers("123-4567 32-976786", newrecord.numbers);
        phonelist.insert(newrecord);
    }

    delete[] newrecord.name;
}

void randstr(char str[], int len, int start, int end)
{

    for (int i = 0; i < len - 1; i++)
        str[i] = ((char)(start + rand() % end));

    str[len - 1] = '\0';
}
