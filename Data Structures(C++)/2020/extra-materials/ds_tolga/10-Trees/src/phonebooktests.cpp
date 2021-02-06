#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h> /* time */

#include "phonebooktests.h"

void testphonebook()
{
    Phone_Tree phonetree;
    phonetree.create();
    read_fromfile(phonetree, "test_phonebook.dat");
    insert_test(phonetree, "Tolga", "12341234");
    insert_test(phonetree, "Duygu", "9879878");
    search_test(phonetree, "Tolga");
    search_test(phonetree, "*");
    search_test(phonetree, "Murat");
    update_test(phonetree, "Tolga"," Murat", "000000");
    search_test(phonetree, "*");
    search_test(phonetree, "Murat");
    delete_test(phonetree, "Murat");
    delete_test(phonetree, "Duygu");
    search_test(phonetree, "*");
    insert_test(phonetree, "Ozge", "93944");
    insert_test(phonetree, "Savas", "334114");
    clear_test(phonetree);
    search_test(phonetree, "*");

    srand(clock());
    randomfill(phonetree, 10000);
    multi_read_test(phonetree, 5000);

    write_tofile(phonetree, "test_phonebook.dat");
    phonetree.clear();
    remove("test_phonebook.dat");
}

void multi_read_test(Phone_Tree &phonetree, int trials)
{

    const short namelen = 6;
    char name[namelen];

    clock_t start = clock();
    for (int i = 0; i < trials; i++)
    {
        randstr(name, namelen, 65, 26);
        phonetree.search(name);
    }

    clock_t end = clock();

    cout << "Read time for " << trials <<" records: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << " milliseconds" << endl;

    getchar();
}

void insert_test(Phone_Tree &phonetree, const char *name, const char *number)
{
    Phone_Record newrecord;

    newrecord.name = new char[strlen(name) + 1];
    strcpy(newrecord.name, name);

    newrecord.phonenum = new char[strlen(number) + 1];
    strcpy(newrecord.phonenum, number);

    phonetree.insert(newrecord);
    delete[] newrecord.name;
    delete[] newrecord.phonenum;
}

void search_test(Phone_Tree &phonetree, const char *name)
{
    char* searchfor = new char[strlen(name)+1];
    strcpy(searchfor, name);
    phonetree.search(searchfor);
    delete[] searchfor;
}

void update_test(Phone_Tree &phonetree, const char *rem_name, const char *name, const char *number)
{
    Phone_Record newrecord;

    newrecord.name = new char[strlen(name)+1];
    strcpy(newrecord.name, name);

    newrecord.phonenum = new char[strlen(number) + 1];
    strcpy(newrecord.phonenum, number);

    phonetree.update(rem_name, newrecord);

    delete[] newrecord.name;
    delete[] newrecord.phonenum;
}

void delete_test(Phone_Tree &phonetree, const char *rem_name)
{
    phonetree.remove(rem_name);
}

void clear_test(Phone_Tree &phonetree)
{
    phonetree.clear();
}

void randomfill(Phone_Tree &phonetree, int numofrecords)
{

    const short namelen = 6;
    char name[namelen];
    const short phonelen = 8;
    char phone[phonelen];
    Phone_Record newrecord;
    newrecord.name = new char[namelen];
    newrecord.phonenum = new char[phonelen];

    clock_t start = clock();

    for (int i = 0; i < numofrecords; i++)
    {
        randstr(name, namelen, 65, 26);
        randstr(phone, phonelen, 48, 10);

        strcpy(newrecord.name, name);
        strcpy(newrecord.phonenum, phone);
        phonetree.insert(newrecord);
    }
    clock_t end = clock();

    cout << "Write time for " << numofrecords <<" records: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << " milliseconds" << endl;

    delete[] newrecord.name;
    delete[] newrecord.phonenum;
}

void randstr(char str[], int len, int start, int end)
{

    for (int i = 0; i < len - 1; i++)
        str[i] = ((char)(start + rand() % end));

    str[len - 1] = '\0';
}
